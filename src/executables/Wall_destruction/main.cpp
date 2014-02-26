#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

<<<<<<< HEAD
#include "Physics/PhysicWorld.h"

=======
>>>>>>> adf3d90506fc6c446b43bc75a556f5a78fc86de4
#include "SomeListeners.h" // until missing functionality is added

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

	VirtualObject* myLoadingBarrel = 	myLoadingMenu->		createVirtualObject(RESOURCES_PATH "/barrel.obj"); 		// create and add virtual object to loading menu state
	myLoadingBarrel->setModelMatrix(	glm::scale(			glm::mat4(1.0f), glm::vec3(1.0,0.125,1.0)));
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateSinusModelMatrixListener(myLoadingBarrel));	// animated loading barrel
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateClearColorListener());						// animated pseudo Loading_screen

	/*	customize myVRState*/
	VRState* myVRState = 	new VRState("VRSTATE"); // create a VRState labeled VRSTATE
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));

	/*	customize virtual objects*/
	VirtualObject* cube1 = myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj");

	VirtualObject* 	myCubeObject1 = 	VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/cube.obj");	// create a Virtual Object by using the VirtualObject-Factory and add it to VRState manually
	myVRState->		addVirtualObject(	myCubeObject1);		// add to VRState manually
	VirtualObject* 	myCubeObject2 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");	// create another Virtual Object from the same geometry


	glm::mat4 		cube1Matrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.5f, 1.0f)), glm::vec3(0.2f, 0.2f, 0.2f));
	cube1->			setModelMatrix( 	cube1Matrix);
	/*float *fm1 = glm::value_ptr(cube1);
		float width1 = fm1[0];
		float height1 = fm1[5];
		float depth1 = fm1[10];
		float x1 = fm1[0];
		float y1 = fm1[5];
		float z1 = fm1[10]; */
	cube1->			setPhysicsComponent(0.2f, 0.2f, 0.2f, 1.0f, 1.5f, 1.0f, 1.0f);

	glm::mat4		myModelMatrix1 = 	glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(2.5f, 0.2f, 2.5f));	//floor
	myCubeObject1-> setModelMatrix(		myModelMatrix1); 	// override default Model Matrix
	//myCubeObject1->	setPhysicsComponent(2.5f, 0.2f, 2.5f, 0.0f, -1.0f, 0.0f, 0.0f);

	glm::mat4 myModelMatrix2 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f)), glm::vec3(2.5f, 2.5f, 0.2f));	// wall
	myCubeObject2-> setModelMatrix(		myModelMatrix2);	// override default Model Matrix
	//myCubeObject2-> setPhysicsComponent(2.5f, 2.5f, 0.2f, 0.0f, 0.0f, -2.5f, 0.0f);

	/*	load some virtual objects into vr state scene*/	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically
	//PhysicsComponent* myCowObject1PhysicsComponent = 		myCowObject1->getPhysicsComponent();					// get PhysicsComponent pointer
	//myVRState->		attachListenerOnBeginningProgramCycle( 	new UpdatePhysicsWorldListener());
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdatePhysicsComponentListener(			cube1->getPhysicsComponent()));	// update PhysicsComponent on every program cycle iteration
	myVRState->		attachListenerOnBeginningProgramCycle(  new UpdateVirtualObjectModelMatrixListener(	cube1));	// update VirtualObject Model Matrix on every program cycle iteration
	myVRState->		attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener); 					// updates physics simulation

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

	std::cout << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects();

	/*	add customized states to application state pool*/
	myApp->addState(	myMenu);		//add the Main Menu to Applicationä
	myApp->addState(	myLoadingMenu);	//add the Loading Screen to Application
	myApp->addState(	myVRState);		//add the VR State to Application

	myApp->setState(	"MAINMENU"); 	//set initial state to the state labeled MAINMENU
}

int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
}
