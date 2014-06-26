#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/PhysicWorldSimulationListener.h"
#include "IO/IOManager.h"
#include "PlaceHolderListeners.h"
#include "IO/Oculus.h"
#include "IO/OculusCamera.h"
#include "IO/OculusListeners.h"

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;
Oculus*			oculus;
OculusCamera* 	oculusCam;

void configureOtherStuff(){
	std::cout<< "_______ OCULUS CONFIGRATION ________" << std::endl;

	std::cout<< "Initializing Oculus System..." << std::endl;
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));	// init System first, or there will be a crash
	std::cout<< "Initializing Oculus Instance..." << std::endl;
	oculus = new Oculus();
	oculus->InitOculus();

	oculus->CreateShaders();			// Create Post Processing Shaders
	oculus->CreateRenderBuffer(1.0f);	// Create RenderBuffer

	oculus->UpdateEyeParams();

	oculusCam = new OculusCamera(oculus);

	testingState->setCamera(oculusCam);

	// resize Window
	glfwSetWindowSize( RenderManager::getInstance()->getWindow(), oculus->getRenderBuffer()->getWidth(), oculus->getRenderBuffer()->getHeight() );
	std::cout<< "Resized Window to Oculus Resolution: " << oculus->getRenderBuffer()->getWidth()<< ", " << oculus->getRenderBuffer()->getHeight()<<std::endl;

	std::cout<< "Initializing Oculus Instance complete!" << std::endl;
}

void configureTestingApplication(){
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
}

void configureVirtualObjects(){
	std::cout<< "_______ STATE CONFIGRATION  ________" << std::endl;
	testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::OTHER, 0.0f, 8, false);

	VirtualObject* cubeObject2 = testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 10.0f, 8);	// to have something in the scene

	cubeObject2->translate(glm::vec3(0.0f,7.0f,0.0f));

}

void configureInputHandler(){
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress(		new PrintOculusOrientationListener(oculus), GLFW_KEY_SPACE);
}

void configureRendering(){

	Shader* phong_shader = new Shader(SHADERS_PATH "/Phong_Test_Textures/phong.vert", SHADERS_PATH "/Phong_Test_Textures/phong.frag");

	/******************************
	 * LEFT EYE
	 *******************************/
	// render left eye
	RenderPass* default_renderpass_left_eye = new RenderPass( phong_shader, oculus->getRenderBuffer());
	default_renderpass_left_eye->setInitialGraphicsComponentList(testingState->getRenderQueue()->getGraphicsComponentList());	// render all graphics components
	default_renderpass_left_eye->setCustomClearColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
	default_renderpass_left_eye->setClearColorBufferBit(true);

	// set view matrix offset for right eye before proceeding to rendering
	default_renderpass_left_eye->attachListenerOnActivation( new SetOculusCameraEyeListener( oculusCam, OVR::Util::Render::StereoEye_Left ) );

	// set viewport for left eye before proceeding to rendering
	default_renderpass_left_eye->attachListenerOnActivation( new SetStereoViewportListener( oculus, OVR::Util::Render::StereoEye_Left ) );

	// set perspective matrix for left eye
	default_renderpass_left_eye->attachListenerOnActivation( new SetStereoPerspectiveListener( oculus , OVR::Util::Render::StereoEye_Left) );

	/******************************
	* RIGHT EYE
	*******************************/

	// render right eye
	RenderPass* default_renderpass_right_eye= new RenderPass(phong_shader, oculus->getRenderBuffer());
	default_renderpass_right_eye->setInitialGraphicsComponentList(testingState->getRenderQueue()->getGraphicsComponentList());	// render all graphics components
	default_renderpass_right_eye->setClearColorBufferBit(false);

	// set view matrix offset for right eye before proceeding to rendering
	default_renderpass_right_eye->attachListenerOnActivation( new SetOculusCameraEyeListener( oculusCam, OVR::Util::Render::StereoEye_Right  ) );

	// set viewport for right eye before proceeding to rendering
	default_renderpass_right_eye->attachListenerOnActivation( new SetStereoViewportListener( oculus, OVR::Util::Render::StereoEye_Right ) );

	// set perspective matrix for right eye
	default_renderpass_right_eye->attachListenerOnActivation( new SetStereoPerspectiveListener( oculus , OVR::Util::Render::StereoEye_Right) );

	/*****************************
	 * PRESENTATION
	 *****************************/
	// present image when finished whith this render pass
	default_renderpass_right_eye->attachListenerOnDeactivation( new OculusPostProcessingRenderpass(oculus));

	// actual registration in renderloop
	testingState->getRenderLoop()->addRenderPass(default_renderpass_left_eye);
	testingState->getRenderLoop()->addRenderPass(default_renderpass_right_eye);

	}

void configurePhysics()
{
	testingState->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));
}

void configureApplication(){
	std::cout<< "_______ APPLICATION INITIALZATION __" << std::endl;
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("TESTING FRAMEWORK");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureOtherStuff();
	configureTestingApplication();
	configureVirtualObjects();
	configureInputHandler();
	configureRendering();
	configurePhysics();
}

int main() {
	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;					// 3 end :)
}
