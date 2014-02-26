<<<<<<< HEAD
/*#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

int main(){
	// Initialize GFLW
	if( !glfwInit() )
	{
	    fprintf( stderr, "Failed to initialize GLFW\n" );
	    return -1;
	}

	glfwWindowHint(GLFW_STEREO, 4); // 4x antialiasing

	if( !glfwCreateWindow(1024,768,"Test",0,0))
	{
	    fprintf( stderr, "Failed to open GLFW window\n" );
	    glfwTerminate();
	    return -1;
	}

	// Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}
=======
#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "IO/IOManager.h"
>>>>>>> origin/master

/*
*	This executable tests various Input/Output related functionalities
*/	

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;
VirtualObject*  cubeObject;

void configureTestingApplication(){
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
}

void configureVirtualObjects(){
	cubeObject = testingState->createVirtualObject(RESOURCES_PATH "/cube.obj");	// to have something in the scene
}

void configurePhysics(){

}

void configureInputHandler(){
	/* customization of input handling */
	testingInputHandler->attachListenerOnKeyPress(new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

	testingInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 testingState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_LEFT );	// pressing '<-'   : turn camera to the left  by 0.1 radians
	testingInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( testingState->getCamera()), 				GLFW_KEY_LEFT );
	testingInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 testingState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_RIGHT);	// pressing '->'   : turn camera to the right by 0.1 radians
	testingInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( testingState->getCamera()), 				GLFW_KEY_RIGHT);	
	testingInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 testingState->getCamera(), 0.0f, 0.1f),	GLFW_KEY_UP   );	// pressing 'up'   : turn camera up by 0.1 radians
	testingInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( testingState->getCamera()), 				GLFW_KEY_UP   );
	testingInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 testingState->getCamera(), 0.0f, -0.1f),	GLFW_KEY_DOWN );	// pressing 'down' : turn camera down by 0.1 radiens
	testingInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( testingState->getCamera()), 				GLFW_KEY_DOWN );

	testingInputHandler->attachListenerOnKeyPress(new PrintValueListener( IOManager::getInstance()->getDeltaTimePointer(), "d_t : "), GLFW_KEY_SPACE );

}

void configureRendering(){
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());

	testingApp->attachListenerOnProgramInitialization(	new SetClearColorListener(1.0f,1.0f,1.0f));	// white background
}

void configureOtherStuff(){	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("TESTING FRAMEWORK");
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
<<<<<<< HEAD
*/
=======

int main() {

	configureApplication();	// 1 do some customization

	testingApp->run();		// 2 run application

	return 0;				// 3 end :)
}

>>>>>>> origin/master
