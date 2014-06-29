#include <IO/OculusListeners.h>
#include <Visuals/RenderManager.h>
#include <glm/gtx/transform.hpp>

SetStereoViewportListener::SetStereoViewportListener(Oculus* oculus, OVR::Util::Render::StereoEye eye)
{
	this->oculus = oculus;
	this->eye = eye;
}

void SetStereoViewportListener::update()
{
	OVR::Util::Render::StereoConfig stereoConfig = oculus->getStereoConfig();

	OVR::Util::Render::Viewport vp = stereoConfig.GetEyeRenderParams( eye ).VP;

	glViewport(vp.x, vp.y, vp.w, vp.h);
}


SetStereoPerspectiveListener::SetStereoPerspectiveListener(Oculus* oculus, OVR::Util::Render::StereoEye eye)
{
	this->oculus = oculus;
	this->eye = eye;
}

void SetStereoPerspectiveListener::update()
{
	OVR::Util::Render::StereoConfig stereoConfig = oculus->getStereoConfig();

	// "center eye" perspective matrix
	float fovy = stereoConfig.GetYFOVDegrees();
	float aspect = stereoConfig.GetAspect();
	float nearValue = 0.1f;
	float farValue = 250.0f;

	// offset to corresponding eye
	float offset = (eye == OVR::Util::Render::StereoEye_Left) ? stereoConfig.GetProjectionCenterOffset() : - stereoConfig.GetProjectionCenterOffset();
	glm::mat4 offsetMatrix = glm::translate(glm::vec3( offset, 0.0f, 0.0f) );

	// overwrite old perspective matrix
	RenderManager::getInstance()->setPerspectiveMatrix(fovy, aspect, nearValue, farValue);
	RenderManager::getInstance()->getCurrentFrustum()->setPerspectiveMatrix( offsetMatrix * RenderManager::getInstance()->getCurrentFrustum()->getPerspectiveMatrix() );
}

SetOculusCameraEyeListener::SetOculusCameraEyeListener(OculusCamera* cam,
		OVR::Util::Render::StereoEye eye) {
	this->cam = cam;
	this->eye = eye;
}

void SetOculusCameraEyeListener::update() {
	if ( cam != 0)
	{
		cam->setEye( eye );
	}
}

OculusPostProcessingRenderpassListener::OculusPostProcessingRenderpassListener(Oculus* oculus)
{
	this->oculus = oculus;
}

void OculusPostProcessingRenderpassListener::update()
{
	if (oculus)
	{
		glViewport( 0, 0, oculus->getRenderBuffer()->getWidth(), oculus->getRenderBuffer()->getHeight() );

		// just draw this on the active FBO
		oculus->PresentFbo(Oculus::PostProcess_Distortion, RiftDistortionParams());

	//	oculus->PresentFbo_NoDistortion();
	}
}


