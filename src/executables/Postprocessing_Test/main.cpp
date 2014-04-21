#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

void configureTestingApplication(){
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

}

void configureVirtualObjects(){
	//setInitialGraphicsComponentList

}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */

}

void configureInputHandler(){
	/* customization of input handling */
	/* use listener interfaces for: what should happen when a specific key is pressed, etc. */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

}

void configureRendering(){

	Shader *postprocessShader = new Shader( 	SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/glow.frag");

	FrameBufferObject *fbo = new FrameBufferObject(800, 600);
	FrameBufferObject *fbo2 = new FrameBufferObject(800, 600);

	Listener* setClearColor 	= new SetClearColorListener 		( 1.0, 1.0, 1.0, 1.0);

	RenderPass* glowRenderPass = new RenderPass(postprocessShader, fbo2);
	glowRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	glowRenderPass->attachListenerOnActivation( setClearColor );// set clear color on activation, before bits are cleared
	//glowRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden


	testingState->getRenderLoop()->addRenderPass(	glowRenderPass );
	

}

void configureOtherStuff(){
	/* customization for other stuff */
	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("POSTPROCESSING");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();
	configurePhysics();
	configureInputHandler();
	configureRendering();
	configureOtherStuff();
}

int main() {

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
