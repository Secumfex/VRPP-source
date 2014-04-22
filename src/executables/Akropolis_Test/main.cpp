#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"

#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/Frustum.h"

#include "Tools/UtilityListeners.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"
#include "Physics/PhysicWorld.h"

#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"

#include "SomeListeners.h"


 // until missing functionality is added

Application* 	myApp;
PlayerCamera*   myPlayercam;
VRState* 		myState;
IOHandler*   	myInputHandler;
Frustum*		myFrustum;

	/*How to build your own custom Application*/

void configureTestingApplication(){
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

	myApp->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));
	myPlayercam = new PlayerCamera();
	myState->setCamera(myPlayercam);
	myFrustum = new Frustum(myPlayercam);
}


void configureVirtualObjects(){

	/*	load model of akropolis as virtual object*/
	VirtualObject* 	akropolis = myState->createVirtualObject(RESOURCES_PATH "/Akropolis/Akropol_woGarbage.obj", VirtualObjectFactory::MESH);
	akropolis->translate(glm::vec3(-20.0, -50.0, 0.0));
}

void configurePhysics(){

	btRigidBody* camBody = myPlayercam->getRigidBody();
	myPlayercam->setPosition(0.0f,2.0f,5.0f);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);

}

void configureInputHandler(){
	/* customization of input handling */

	myInputHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), GLFW_KEY_ESCAPE);

	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 myState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_LEFT );	// pressing '<-'   : turn camera to the left  by 0.1 radians
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 				GLFW_KEY_LEFT );
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 myState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_RIGHT);	// pressing '->'   : turn camera to the right by 0.1 radians
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 				GLFW_KEY_RIGHT);
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 myState->getCamera(), 0.0f, 0.1f),	GLFW_KEY_UP   );	// pressing 'up'   : turn camera up by 0.1 radians
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 				GLFW_KEY_UP   );
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(		 myState->getCamera(), 0.0f, -0.1f),	GLFW_KEY_DOWN );	// pressing 'down' : turn camera down by 0.1 radiens
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 				GLFW_KEY_DOWN );

	myInputHandler->attachListenerOnKeyPress(new PrintValueListener( IOManager::getInstance()->getDeltaTimePointer(), "d_t : "), GLFW_KEY_T );
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), GLFW_KEY_I );
	myInputHandler->attachListenerOnKeyPress(new ApplyLinearImpulseOnRigidBody(myPlayercam->getRigidBody(), btVector3(0.0f,5.0f,0.0f)), GLFW_KEY_SPACE );
	myInputHandler->attachListenerOnKeyPress(new SetCameraPositionListener(myPlayercam, glm::vec3(0.0f,5.0f,0.0f)), GLFW_KEY_R );


	SelectionHandler* sh = myInputHandler->getSelectionHandler();
	myInputHandler->attachListenerOnMouseButtonPress(new ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(sh, myState->getCamera(),50.0f), GLFW_MOUSE_BUTTON_RIGHT);

}

void configureRendering(){
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	myApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test_Textures/phong.vert", SHADERS_PATH "/Phong_Test_Textures/phong.frag")));
	myApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());
	myApp->attachListenerOnProgramInitialization(	new SetClearColorListener(1.0f,1.0f,1.0f));	// white background
}

void configureOtherStuff(){
}

void configureApplication(){
	/* create  minimal Application with one state */
	myApp  			= 	Application::getInstance();
	myApp 			->	setLabel("Feature akropolis under water");
	myState 		= 	new VRState("TESTING FRAMEWORK");
	myApp 			->	addState(myState);
	myInputHandler 	= myState->getIOHandler();

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();
	configurePhysics();
	configureInputHandler();
	configureRendering();
	configureOtherStuff();
}

int main() {

	configureApplication();	// 1 do some customization

	myApp->run();		// 2 run application

	return 0;				// 3 end :)
}
