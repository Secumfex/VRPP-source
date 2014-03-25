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

Application* testingApp;
VRState* testingState;
IOHandler* testingInputHandler;

void configureTestingApplication() {
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(
			new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(
			new PrintMessageListener(string("Application is terminating")));

}

void configureVirtualObjects() {
	/* creation and customization of Virtual Objects */
	/* use testingState->createVirtualObject() to create a Virtual Object */

	testingState->createVirtualObject( RESOURCES_PATH "/aqua02.3ds",
			VirtualObjectFactory::OTHER);
}

void configurePhysics() {
	/* customization of Bullet / Physicsworld */

}

void configureInputHandler() {
	/* customization of input handling */
	/* use listener interfaces for: what should happen when a specific key is pressed, etc. */
	testingInputHandler->attachListenerOnKeyPress(
			new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

}

void configureRendering() {
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	/* use listener interfaces for: what should happen everytime a frame is drawn */

	/*comment in to use placeholders for Renderloop, rendering every VO of the testingState; change Shader paths to use a different shader*/
//	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag")));
//	testingApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());
	testingApp->attachListenerOnProgramInitialization(
			new SetDefaultShaderListener(
					new Shader(SHADERS_PATH "/Phong_Test/phong.vert",
							SHADERS_PATH "/Phong_Test/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(
			new RenderloopPlaceHolderListener());
}

void configureOtherStuff() {
	/* customization for other stuff */

}

void configureApplication() {
	/* create  minimal Application with one state */
	testingApp = Application::getInstance();
	testingApp->setLabel("PROJEKT PRAKTIKUM");
	testingState = new VRState("TESTING FRAMEWORK");
	testingApp->addState(testingState);
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
