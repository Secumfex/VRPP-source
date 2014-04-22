//test class for heightfield physics component

#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "Physics/PhysicWorld.h"
#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"

#include "SomeListeners.h" // until missing functionality is added

Application* myApp;
PlayerCamera*   playercam;


void configureMyApp(){
	/*	customize application a little bit*/
	myApp = 		Application::getInstance();	//create an Application labeled PROJEKT PRAKTIKUM
	myApp->			setLabel("PP:HeightmapPhysicsTest");

	/*	customize myVRState*/
	VRState* myVRState = 	new VRState("VRSTATE"); // create a VRState labeled VRSTATE
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));

	playercam = new PlayerCamera();
	myVRState->setCamera(playercam);


	/*	customize virtual objects*/
	//VirtualObject* groundObject = myVRState->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::PLANE);

	VirtualObject* 	terrain = 	myVRState->	createVirtualObject(RESOURCES_PATH "/Heightfield/terrainTest.obj", VirtualObjectFactory::TERRAIN);
	glm::mat4 myModelMatrix1 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f)), glm::vec3(10.0f, 10.0f, 10.0f));	//floor
	terrain->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
	//terrain->setPhysicsComponent(RESOURCES_PATH"/terrainTest.png", 2048, 2048, 0.0f, 0.0f, 1);
	//myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(terrain));

	btRigidBody* camBody = playercam->getRigidBody();
	playercam->setPosition(0.0f,0.0f,0.0f);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);


	/*	load some virtual objects into vr state scene*/
	myVRState->			attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));				// updates physics simulation

	IOHandler* myVRStateIOHandler = myVRState-> getIOHandler();
	// attach some listeners to keyboard key presses
	myVRStateIOHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), 	GLFW_KEY_ESCAPE);	// Terminate Application by pressing Escape
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.0,0.0,0.0),	GLFW_KEY_1);		// pressing '1' : black background
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(1.0,1.0,1.0), 	GLFW_KEY_2);		// pressing '2' : white background
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.44,0.5,0.56), 	GLFW_KEY_3);		// pressing '3' : default greyish-blue background
	myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_LEFT);		// pressing '<-' : view direction at an angle to the left
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_LEFT);
	myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_RIGHT);	// pressing '->' : view direction at an angle to the right
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_RIGHT);
	myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.0f, 0.1f), 	GLFW_KEY_UP);		// pressing '<-' : view direction straight ahead
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_UP);
	myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.0f, -0.1f), 	GLFW_KEY_DOWN);		// pressing '->' : view direction straight ahead
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_DOWN);
	myVRStateIOHandler->attachListenerOnMouseButtonPress(new PickRayListener(myVRState->getCamera()), GLFW_MOUSE_BUTTON_2);		//
	myVRStateIOHandler->attachListenerOnMouseButtonPress(new ShootSphereListener(myVRState->getCamera(), myVRState), GLFW_MOUSE_BUTTON_LEFT);

	SelectionHandler* sh = myVRStateIOHandler->getSelectionHandler();
	myVRStateIOHandler->attachListenerOnMouseButtonPress(new ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(sh, myVRState->getCamera(),50.0f), GLFW_MOUSE_BUTTON_RIGHT);

	myVRStateIOHandler->attachListenerOnKeyPress(new ApplyLinearImpulseOnRigidBody(playercam->getRigidBody(), btVector3(0.0f,5.0f,0.0f)), GLFW_KEY_SPACE );
	myVRStateIOHandler->attachListenerOnKeyPress(new SetCameraPositionListener(playercam, glm::vec3(0.0f,5.0f,0.0f)), GLFW_KEY_R );


	/*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
	myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );

	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());

	std::cout << "#collObjs: " << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	/*	add customized states to application state pool*/
	myApp->addState(	myVRState);		//add the VR State to Application

	myApp->setState(	"VRSTATE"); 	//set initial state to the state labeled MAINMENU
}

int main() {

	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
};
