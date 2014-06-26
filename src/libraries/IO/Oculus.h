#ifndef OCULUS_H
#define OCULUS_H

#include <OVR.h>
#include "Tools/ShaderTools.h"
#include "Oculus_Shaders.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/Shader.h"

#include <iostream>

struct RiftDistortionParams
{
    float lensOff;
    float LensCenterX;
    float LensCenterY;
    float ScreenCenterX;
    float ScreenCenterY;
    float ScaleX;
    float ScaleY;
    float ScaleInX;
    float ScaleInY;
    float DistScale;

    RiftDistortionParams()
        : lensOff(0.287994f - 0.25f) // this value ripped from the TinyRoom demo at runtime
        , LensCenterX(0.25f)
        , LensCenterY(0.50f)
        , ScreenCenterX(0.25f)
        , ScreenCenterY(0.5f)
        , ScaleX(0.145806f)
        , ScaleY(0.233290f)
        , ScaleInX(4.0f)
        , ScaleInY(2.5f)
        , DistScale(1.0f)
    {}
};

class Oculus {

protected:
	// *** Oculus HMD Variables
	OVR::Ptr<OVR::DeviceManager>  ovrManager;
  	OVR::Ptr<OVR::SensorDevice>   ovrSensor;
  	OVR::Ptr<OVR::HMDDevice> 	  ovrHMD;
	OVR::SensorFusion             sensorFusion;
	OVR::HMDInfo 				  HMDInfo;

	OVR::Util::Render::StereoEyeParams lEyeParams;
    OVR::Util::Render::StereoEyeParams rEyeParams;
    OVR::Util::Render::StereoConfig    stereoConfig;

   	// Render buffer for OVR distortion correction shader
    int fboWidth;
    int fboHeight;

    GLuint progRiftDistortion;
    GLuint progPresFbo;

    Shader* RiftDistortion;
    Shader* PresFbo;
	
	int windowWidth, windowHeight;

    FrameBufferObject* renderBuffer;

    const float  YawInitial;
    float LastSensorYaw;
    float EyeYaw;
    float EyePitch;
    float EyeRoll;

public: 
    // Stereo viewing parameters
    enum PostProcessType
    {
        PostProcess_None,
        PostProcess_Distortion
    };

	Oculus();
	~Oculus();
	void InitOculus();

    bool       SensorActive() const { return ovrSensor != NULL; }
    OVR::Quatf GetOrientation() const { return sensorFusion.GetOrientation(); }
    bool       GetStereoMode() const { return stereoConfig.GetStereoMode() == OVR::Util::Render::Stereo_LeftRight_Multipass; }
    const OVR::HMDInfo& GetHMD() const { return HMDInfo; }
    OVR::Util::Render::StereoConfig getStereoConfig() const { return stereoConfig; }
    
	void CreateShaders();
    void CreateRenderBuffer(float bufferScaleUp);
    void UpdateEyeParams();
    void BindRenderBuffer();
    void UnBindRenderBuffer();

    void PresentFbo(
        PostProcessType post,
        const RiftDistortionParams& distParams);
    void PresentFbo_NoDistortion();
    void PresentFbo_PostProcessDistortion(
        const OVR::Util::Render::StereoEyeParams& eyeParams,
        const RiftDistortionParams& distParams);
    bool getSensorOrientation(float mult = 1.0f);

    enum DisplayMode
    {
        SingleEye,
        Stereo,
        StereoWithDistortion
    };

    void SetDisplayMode(DisplayMode);
	
	inline void getDk1HmdValues(OVR::HMDInfo & hmdInfo){
		hmdInfo.HResolution = 1280;
		hmdInfo.VResolution = 800;
		hmdInfo.HScreenSize = 0.14976f;
		hmdInfo.VScreenSize = 0.09360f;
		hmdInfo.VScreenCenter = 0.04680f;
		hmdInfo.EyeToScreenDistance = 0.04100f;
		hmdInfo.LensSeparationDistance = 0.06350f;
		hmdInfo.InterpupillaryDistance = 0.06400f;
		hmdInfo.DistortionK[0] = 1;
		hmdInfo.DistortionK[1] = 0.22f;
		hmdInfo.DistortionK[2] = 0.24f;
		hmdInfo.DistortionK[3] = 0;
		hmdInfo.DesktopX = 100;
		hmdInfo.DesktopY = 100;
		hmdInfo.ChromaAbCorrection[0] = 0.99600f;
		hmdInfo.ChromaAbCorrection[1] = -0.00400f;
		hmdInfo.ChromaAbCorrection[2] = 1.01400f;
		hmdInfo.ChromaAbCorrection[3] = 0;
	}	

	/*Getter*/
	float getEyeYaw();
	float getEyePitch();
	float getEyeRoll();

	FrameBufferObject* getRenderBuffer();
};

#endif
