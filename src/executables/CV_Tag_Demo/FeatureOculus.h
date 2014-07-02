#ifndef FEATUREOCULUS_H
#define FEATUREOCULUS_H

#include "IO/Oculus.h"
#include "IO/OculusCamera.h"
#include "IO/OculusListeners.h"
#include "IO/OculusPostProcessingRenderPass.h"

#include "PlaceHolderListeners.h"

namespace OculusFeature
{

/**
 * OBJECT INSTANCES
 */
	Oculus* 		oculus;
	OculusCamera* 	oculusCam;
	OculusPostProcessingRenderPass* oculusPostProcessing;	// post processing renderpass, default output : window


// TODO methods to initialize Oculus, create and set Oculus Camera, attach Stereo Rendering Listeners to a RenderPass etc.
// see OculusVR_Test/main.cpp for inspiration

/**
 * creates and configures an Oculus instance
 * - initializes Oculus system etc.
 * - creates an OculusCamera instance and sets as active Camera of target state
 * - resizes window
 * - creates an OculusPostProcessing renderpass
 */
void initializeAndConfigureOculus( ApplicationState* target ){
	std::cout<< "_______ OCULUS CONFIGRATION ________" << std::endl;

	std::cout<< "Initializing Oculus System..." << std::endl;
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));	// init System first, or there will be a crash
	std::cout<< "Initializing Oculus Instance..." << std::endl;
	oculus = new Oculus();
	oculus->InitOculus();

	oculus->CreateShaders();			// Create Post Processing Shaders
	oculus->CreateRenderBuffer(1.0f);	// Create RenderBuffer

	oculus->UpdateEyeParams();

	// create oculus camera
	oculusCam = new OculusCamera(oculus);

	target->setCamera(oculusCam);

	// resize Window
	IOManager::getInstance()->setWindowSize(oculus->getRenderBuffer()->getWidth(),  oculus->getRenderBuffer()->getHeight());
	//glfwSetWindowSize( RenderManager::getInstance()->getWindow(), oculus->getRenderBuffer()->getWidth(), oculus->getRenderBuffer()->getHeight() );
	std::cout<< "Resized Window to Oculus Resolution: " << oculus->getRenderBuffer()->getWidth()<< ", " << oculus->getRenderBuffer()->getHeight()<<std::endl;

	// create renderpass
	oculusPostProcessing = new OculusPostProcessingRenderPass(oculus, 0);

	std::cout<< "Initializing Oculus Instance complete!" << std::endl;
}

/**
 * will alter RenderPass in a way that makes it render twice when called by renderloop
 * - the render settings will be set for left eye
 * - at the end of the render pass, it is called again with settings for right eye
 * - will use only use half view ports per eye
 * - will apply according view matrix
 * - will apply according projection matrix
 *
 * @param renderPass
 * 		to be set up to render twice - for each eye once
 * @param oculus to be used to query stereo settings from
 * @param oculusCam that is assumed to be used during this render pass
 */
void makeStereoRenderPass(RenderPass* renderPass, Oculus* oculus, OculusCamera* oculusCam)
{
	// left eye settings
	renderPass->attachListenerOnActivation(
			new StereoRenderPassActivateRenderEyeSettingsListener(renderPass,
					oculus, oculusCam, OVR::Util::Render::StereoEye_Left,
					true)
	);

	// right eye settings
	renderPass->attachListenerOnActivation(
			new StereoRenderPassActivateRenderEyeSettingsListener(renderPass,
					oculus, oculusCam, OVR::Util::Render::StereoEye_Right,
					false)
	);

	// trigger second render pass iteration
	renderPass->attachListenerOnDeactivation(
			new StereoRenderPassRenderAgainListener(renderPass)
	);

}

} // NAMESPACE OculusFeature
#endif
