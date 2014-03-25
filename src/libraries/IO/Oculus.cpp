#include "Oculus.h"

Oculus::Oculus() 
	: ovrManager(NULL) 
	, ovrHMD(NULL) 
	, ovrSensor(NULL) 
	, sensorFusion() 
	, HMDInfo() 
	, stereoConfig()
	, windowWidth(0)
	, windowHeight(0)
	
	, fboWidth(0)
	, fboHeight(0)
	, progRiftDistortion(0)
	, progPresFbo(0)

    , YawInitial(3.141592f)
    , LastSensorYaw(0)
    , EyeYaw(YawInitial)
    , EyePitch(0)
    , EyeRoll(0)
{ 
}

 Oculus::~Oculus()
 {
 	// Clear variables first
   	ovrSensor.Clear();
   	ovrManager.Clear();
   	// No OVR functions involving memory are allowed after this
   	OVR::System::Destroy();
 }

 /// We need an active GL context for this
void Oculus::CreateShaders()
{
    progPresFbo = ShaderTools::makeShaderProgram(PresentFboVertSrc, PresentFboFragSrc);
    progRiftDistortion = ShaderTools::makeShaderProgram(PostProcessVertexShaderSrc, PostProcessFragShaderSrc);
}

/// We need an active GL context for this
void Oculus::CreateRenderBuffer(float bufferScaleUp)
{
    fboWidth = (int)((bufferScaleUp) * (float)windowWidth );
    fboHeight = (int)((bufferScaleUp) * (float)windowHeight );
    renderBuffer.resize(fboWidth, fboHeight);
}

void Oculus::BindRenderBuffer() 
{
    renderBuffer.bindFBO();
}

void Oculus::UnBindRenderBuffer() 
{
    renderBuffer.unbindFBO();
}

void Oculus::PresentFbo_NoDistortion()
{
    glUseProgram(progPresFbo);
    {
        OVR::Matrix4f ortho = OVR::Matrix4f::Ortho2D((float)fboWidth, (float)fboHeight);
        glUniformMatrix4fv(glGetUniformLocation(progPresFbo, "prmtx"), 1, false, &ortho.Transposed().M[0][0]);

        const float verts[] = {
            0                ,  0,
            (float)fboWidth,  0,
            (float)fboWidth, (float)fboHeight,
            0                , (float)fboHeight,
        };
        const float texs[] = {
            0,1,
            1,1,
            1,0,
            0,0,
        };
        const unsigned int tris[] = {
            0,1,2, 0,3,2, // ccw
        };

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texs);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderBuffer.getColorTextureHandle());
        glUniform1i(glGetUniformLocation(progPresFbo, "fboTex"), 0);

        glDrawElements(GL_TRIANGLES,
                       6,
                       GL_UNSIGNED_INT,
                       &tris[0]);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    glUseProgram(0);
}

void Oculus::PresentFbo_PostProcessDistortion(
    const OVR::Util::Render::StereoEyeParams& eyeParams,
    const RiftDistortionParams& distParams)
{
    const OVR::Util::Render::DistortionConfig*  pDistortion = eyeParams.pDistortion;
    if (pDistortion == NULL)
        return;

    glUseProgram(progRiftDistortion);
    {
        // Set uniforms for distortion shader
        OVR::Matrix4f ident;
        glUniformMatrix4fv(glGetUniformLocation(progRiftDistortion, "View"), 1, false, &ident.Transposed().M[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(progRiftDistortion, "Texm"), 1, false, &ident.Transposed().M[0][0]);

        //"uniform vec2 LensCenter;\n"
        //"uniform vec2 ScreenCenter;\n"
        //"uniform vec2 Scale;\n"
        //"uniform vec2 ScaleIn;\n"
        //"uniform vec4 HmdWarpParam;\n"

        // The left screen is centered at (0.25, 0.5)
        glUniform2f(glGetUniformLocation(progRiftDistortion, "LensCenter"),
            distParams.LensCenterX + distParams.lensOff, distParams.LensCenterY);

        glUniform2f(glGetUniformLocation(progRiftDistortion, "ScreenCenter"),
            distParams.ScreenCenterX, distParams.ScreenCenterY);

        // The right screen is centered at (0.75, 0.5)
        if (eyeParams.Eye == OVR::Util::Render::StereoEye_Right)
        {
            glUniform2f(glGetUniformLocation(progRiftDistortion, "LensCenter"),
                1.0f - (distParams.LensCenterX + distParams.lensOff), distParams.LensCenterY);

            glUniform2f(glGetUniformLocation(progRiftDistortion, "ScreenCenter"),
                1.0f - distParams.ScreenCenterX, distParams.ScreenCenterY);
        }
        
        glUniform2f(glGetUniformLocation(progRiftDistortion, "Scale"),
            distParams.ScaleX,  distParams.ScaleY);

        glUniform2f(glGetUniformLocation(progRiftDistortion, "ScaleIn"),
            distParams.ScaleInX, distParams.ScaleInY);

        glUniform4f(glGetUniformLocation(progRiftDistortion, "HmdWarpParam"),
            distParams.DistScale * pDistortion->K[0],
            distParams.DistScale * pDistortion->K[1],
            distParams.DistScale * pDistortion->K[2],
            distParams.DistScale * pDistortion->K[3]
        );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderBuffer.getColorTextureHandle());
        glUniform1i(glGetUniformLocation(progRiftDistortion, "Texture0"), 0);

        float verts[] = { // Left eye coords
            -1.0f, -1.0f,
             0.0f, -1.0f,
             0.0f,  1.0f,
            -1.0f,  1.0f,
        };
        float texs[] = {
            0.0f, 1.0f,
            0.5f, 1.0f,
            0.5f, 0.0f,
            0.0f, 0.0f,
        };

        // Adjust coords for right eye
        if (eyeParams.Eye == OVR::Util::Render::StereoEye_Right)
        {
            verts[2*0  ] += 1.0f;
            verts[2*1  ] += 1.0f;
            verts[2*2  ] += 1.0f;
            verts[2*3  ] += 1.0f;
            
            texs[2*0] += 0.5f;
            texs[2*1] += 0.5f;
            texs[2*2] += 0.5f;
            texs[2*3] += 0.5f;
        }

        const unsigned int tris[] = {
            0,1,2,  0,2,3, // ccw
        };

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texs);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES,
                       6,
                       GL_UNSIGNED_INT,
                       &tris[0]);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    glUseProgram(0);
}

void Oculus::PresentFbo(PostProcessType post, const RiftDistortionParams& distParams)
{
    if (post == PostProcess_Distortion)
    {
        PresentFbo_PostProcessDistortion(lEyeParams, distParams);
        PresentFbo_PostProcessDistortion(rEyeParams, distParams);
    }
    else
    {
        PresentFbo_NoDistortion();
    }
}

void Oculus::UpdateEyeParams()
{
    lEyeParams = stereoConfig.GetEyeRenderParams(OVR::Util::Render::StereoEye_Left);
    rEyeParams = stereoConfig.GetEyeRenderParams(OVR::Util::Render::StereoEye_Right);
}


int Oculus::InitOculus()
{
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));
	// Create DeviceManager
	ovrManager = *OVR::DeviceManager::Create();
	if (!ovrManager) {
    	std::cout << "Unable to create OVR device manager\n";
    }

    // Release Sensor/HMD in case this is a retry.
    ovrSensor.Clear();
    ovrHMD.Clear();

    // Create first available Head-Mounted Display Device from DeviceManager
    ovrHMD  = *ovrManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
    if (ovrHMD)
    {
    	// This will initialize HMDInfo with information about configured inter
        // pupillary distance, screen size and other variables needed for correct 
        // projection. 
      	ovrHMD->GetDeviceInfo(&HMDInfo);

      	// Sensor object is created from the HMD, to ensure that it is on the
		// correct device.
        ovrSensor = *ovrHMD->GetSensor();
    }

    else
    {   
       	// If no OVR Device is present, initialize HMDInfo with standard values  
       	getDk1HmdValues(HMDInfo);       

        // If we didn't detect an HMD, try to create the sensor directly.
        // This is useful for debugging sensor interaction; it is not needed in
        // a shipping app.
        ovrSensor = *ovrManager->EnumerateDevices<OVR::SensorDevice>().CreateDevice();
    }

    // If there was a problem detecting the Rift, display appropriate message.
	const char* detectionMessage;

    if (!ovrHMD && !ovrSensor)
		detectionMessage = "Oculus Rift not detected.";
    else if (!ovrHMD)
        detectionMessage = "Oculus Sensor detected; HMD Display not detected.";
    else if (!ovrSensor)
        detectionMessage = "Oculus HMD Display detected; Sensor not detected.";
    else if (HMDInfo.DisplayDeviceName[0] == '\0')
        detectionMessage = "Oculus Sensor detected; HMD display EDID not detected.";
    else
        detectionMessage = 0;

    if (detectionMessage)
    {
    	std::cout << "Oculus Rift ERROR\n";
        //::MessageBoxA(0, detectionMessage, "Oculus Rift ERROR", MB_OK);
    }

	// The HMDInfo structure contains everything we need for now, so no need to 
    // keep the device handle around
	ovrHMD.Clear();
	    
	if (HMDInfo.HResolution > 0)
	{
	    windowWidth  = HMDInfo.HResolution;
	    windowHeight = HMDInfo.VResolution;
	}
	    
	if (ovrSensor)
	{
	    // We need to attach sensor to SensorFusion object for it to receive 
	    // body frame messages and update orientation. 
	    sensorFusion.AttachToSensor(ovrSensor);
	    //sensorFusion.SetDelegateMessageHandler(this);
	    //sensorFusion.SetGravityEnabled(true);			// per default
		sensorFusion.SetPredictionEnabled(true);
	    //sensorFusion.SetYawCorrectionEnabled(false);	// per default?
	}

	// *** Configure Stereo settings
	stereoConfig.SetHMDInfo(HMDInfo);
	stereoConfig.SetFullViewport(OVR::Util::Render::Viewport(0,0, windowWidth, windowHeight));
	stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_LeftRight_Multipass);

	// Configure proper Distortion Fit.
	// For 7" screen, fit to touch left side of the view, leaving a bit of invisible
	// screen on the top (saves on rendering cost).
	// For smaller screens (5.5"), fit to the top.
	if (HMDInfo.HScreenSize > 0.0f)
	{
	    if (HMDInfo.HScreenSize > 0.140f) // 7"
	        stereoConfig.SetDistortionFitPointVP(-1.0f, 0.0f);
	    else
	        stereoConfig.SetDistortionFitPointVP(0.0f, 1.0f);
	}

	stereoConfig.Set2DAreaFov(OVR::DegreeToRad(85.0f));

	// For OVR distortion correction shader
	const float renderBufferScaleIncrease = stereoConfig.GetDistortionScale();
	fboWidth = (int)((renderBufferScaleIncrease) * (float)windowWidth );
	fboHeight = (int)((renderBufferScaleIncrease) * (float)windowHeight );
 }

void Oculus::SetDisplayMode(DisplayMode mode)
{
    switch(mode)
    {
    default:
    case SingleEye:
        stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_None);
        break;

    case Stereo:
        stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_LeftRight_Multipass);
        break;

    case StereoWithDistortion:
        stereoConfig.SetStereoMode(OVR::Util::Render::Stereo_LeftRight_Multipass);
        break;
    }
}

/// Handle input's influence on orientation variables.
bool Oculus::getSensorOrientation(float mult)
{
    // Handle Sensor motion.
    // We extract Yaw, Pitch, Roll instead of directly using the orientation
    // to allow "additional" yaw manipulation with mouse.
    if (this->SensorActive())
    {
        OVR::Quatf hmdOrient = sensorFusion.GetOrientation();
        float yaw = 0.0f;

        hmdOrient.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(&yaw, &EyePitch, &EyeRoll);

        EyeYaw += (yaw - LastSensorYaw);
        LastSensorYaw = yaw;
        return true;
    } 

    else 
    {
    	return false;
    }
    

    /*
    // Gamepad rotation.
    EyeYaw -= GamepadRotate.x * mult;

    if (!this.SensorActive())
    {
        // Allow gamepad to look up/down, but only if there is no Rift sensor.
        EyePitch -= GamepadRotate.y * mult;
        EyePitch -= MouseRotate.y * mult;
        EyeYaw   -= MouseRotate.x * mult;

        const float maxPitch = ((3.1415f/2)*0.98f);
        if (EyePitch > maxPitch)
            EyePitch = maxPitch;
        if (EyePitch < -maxPitch)
            EyePitch = -maxPitch;
    }

    if (GamepadMove.LengthSq() > 0)
    {
        OVR::Matrix4f yawRotate = OVR::Matrix4f::RotationY(EyeYaw);
        OVR::Vector3f orientationVector = yawRotate.Transform(GamepadMove);
        orientationVector *= MoveSpeed * dt;
        EyePos += orientationVector;
    }

    if (MouseMove.LengthSq() > 0)
    {
        OVR::Matrix4f yawRotate = OVR::Matrix4f::RotationY(EyeYaw);
        OVR::Vector3f orientationVector = yawRotate.Transform(MouseMove);
        orientationVector *= MoveSpeed * dt;
        EyePos += orientationVector;
    }

    if (KeyboardMove.LengthSq() > 0)
    {
        OVR::Matrix4f yawRotate = OVR::Matrix4f::RotationY(EyeYaw);
        OVR::Vector3f orientationVector = yawRotate.Transform(KeyboardMove);
        orientationVector *= MoveSpeed * dt;
        EyePos += orientationVector;
    }
    */
}