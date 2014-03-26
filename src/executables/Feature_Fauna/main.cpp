#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "IO/IOManager.h"

#include "SomeListeners.h" // until missing functionality is added

#include "IO/PlayerCamera.h"
#include "Physics/PhysicWorld.h"

Application* myApp;
	/*How to build your own custom Application*/
void configureMyApp(){
	/*	customize application a little bit*/
	myApp = 		Application::getInstance();	//create an Application labeled PROJEKT PRAKTIKUM
	myApp->			setLabel("PROJEKT PRAKTIKUM");



	/*   create some states to work with */
	MenuState* myMenu = 		new MenuState("MAINMENU");	//create a MenuState labeled MAINMENU
	/*
		Button* myButton = new Button("START_BUTTON");	//create a Button labeled START_BUTTON
		myButton->addListenerOnButtonPress(new SetStateListener(myApp, "LOADING_SCREEN")); //add a state changing listener to be notified upon a button press
		myMenu->addButton(myButton);	//add Button to Main Menu
	*/


	/*	customize myLoadingScreen */
	MenuState* myLoadingMenu = 	new MenuState("LOADING_SCREEN");	// create a MenuState labeled LOADING_SCREEN

	VirtualObject* myLoadingBarrel = 	myLoadingMenu->		createVirtualObject(RESOURCES_PATH "/barrel.obj", VirtualObjectFactory::OTHER); 		// create and add virtual object to loading menu state
	myLoadingBarrel->setModelMatrix(	glm::scale(			glm::mat4(1.0f), glm::vec3(1.0,0.125,1.0)));
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateSinusModelMatrixListener(myLoadingBarrel));	// animated loading barrel
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateClearColorListener());						// animated pseudo Loading_screen

	/*	customize myVRState*/
	VRState* myVRState = 	new VRState("VRSTATE"); // create a VRState labeled VRSTATE
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));
	myVRState->		attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(				IOManager::getInstance()->getDeltaTimePointer()));

	PlayerCamera* playercam = new PlayerCamera();
	myVRState->setCamera(playercam);

	/*	load some virtual objects into vr state scene*/

	VirtualObject* 	myCowObject1 = 		myVRState->			createVirtualObject(RESOURCES_PATH "/cow.obj", VirtualObjectFactory::OTHER);	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically
	myCowObject1->	setPhysicsComponent(0.5,0.5,7.5,0.5,0.5);
	PhysicsComponent* myCowObject1PhysicsComponent = 		myCowObject1->getPhysicsComponent();					// get PhysicsComponent pointer
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdatePhysicsComponentListener(			myCowObject1));	// update PhysicsComponent on every program cycle iteration
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdateVirtualObjectModelMatrixListener(	myCowObject1));	// update VirtualObject Model Matrix on every program cycle iteration


	VirtualObject* 	myCowObject2 = 		myVRState->			createVirtualObject(RESOURCES_PATH "/cow.obj", VirtualObjectFactory::OTHER);	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically
	myCowObject2->	setPhysicsComponent(0.5,0.75,15.0,0.75,0.5);
	PhysicsComponent* myCowObject2PhysicsComponent = 		myCowObject2->getPhysicsComponent();					// get PhysicsComponent pointer
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdatePhysicsComponentListener(			myCowObject2));	// update PhysicsComponent on every program cycle iteration
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdateVirtualObjectModelMatrixListener(	myCowObject2));	// update VirtualObject Model Matrix on every program cycle iteration


		btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
		//create an invisible ground plane
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));
    	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
   	 	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);

	btRigidBody* camBody = playercam->getRigidBody();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);



	IOHandler* myVRStateIOHandler = myVRState-> getIOHandler();
	// attach some listeners to keyboard key presses
	myVRStateIOHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), 	GLFW_KEY_ESCAPE);	// Terminate Application by pressing Escape
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.0,0.0,0.0),	GLFW_KEY_1);		// pressing '1' : black background
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(1.0,1.0,1.0), 	GLFW_KEY_2);		// pressing '2' : white background
	myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.44,0.5,0.56), 	GLFW_KEY_3);		// pressing '3' : default greyish-blue background
	myVRStateIOHandler->attachListenerOnKeyPress(new SetCameraDirectionListener(myVRState->getCamera(), glm::vec3(-1.0f,0.0f,-1.0f)), 	GLFW_KEY_LEFT);		// pressing '<-' : view direction at an angle to the left
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_LEFT);
	myVRStateIOHandler->attachListenerOnKeyPress(new SetCameraDirectionListener(myVRState->getCamera(), glm::vec3(1.0f,0.0f,-1.0f)), 	GLFW_KEY_RIGHT);	// pressing '->' : view direction at an angle to the right
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_RIGHT);
	myVRStateIOHandler->attachListenerOnKeyPress(new SetCameraDirectionListener(myVRState->getCamera(), glm::vec3(0.0f,0.0f,-1.0f)), 	GLFW_KEY_UP);		// pressing '<-' : view direction straight ahead
	myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_UP);

	myVRStateIOHandler->attachListenerOnKeyPress(new CreateVirtualObjectListener(RESOURCES_PATH "/Fauna/aqua04.3ds", glm::vec3(5.0,20.0,5.0), 	myVRState, 	2.0f), GLFW_KEY_M); // create a cow in da sky
	myVRStateIOHandler->attachListenerOnKeyPress(new CreateVirtualObjectListener(RESOURCES_PATH "/Fauna/aqua05.3ds", glm::vec3(2.5,10.0,10.0), 	myVRState, 	2.0f), GLFW_KEY_SPACE); // create a cube in da sky

	/*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
	myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );

	myApp->attachListenerOnBeginningProgramCycle(	new TimedTriggerListener(		new SetStateListener(myApp, "LOADING_SCREEN"), 	2500.0)); //	Use Listeners to change states
	myApp->attachListenerOnBeginningProgramCycle(	new TimedTriggerListener(		new SetStateListener(myApp, "VRSTATE"), 		5000.0));

	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());


	/*	add customized states to application state pool*/
	myApp->addState(	myMenu);		//add the Main Menu to Application
	myApp->addState(	myLoadingMenu);	//add the Loading Screen to Application
	myApp->addState(	myVRState);		//add the VR State to Application

	myApp->setState(	"MAINMENU"); 	//set initial state to the state labeled MAINMENU
}

int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
}
