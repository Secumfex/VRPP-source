#ifndef FEATUREOCULUS_H
#define FEATUREOCULUS_H

#include "IO/Oculus.h"
#include "IO/OculusCamera.h"
#include "IO/OculusListeners.h"
#include "IO/OculusPostProcessingRenderPass.h";

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

} // NAMESPACE OculusFeature
#endif
