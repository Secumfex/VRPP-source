#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "Physics/PhysicWorld.h"
#include "IO/IOManager.h"

#include "SomeListeners.h" // until missing functionality is added

Application* myApp;
	/*How to build your own custom Application*/
void configureMyApp(){
	/*	customize application a little bit*/
	myApp = 		Application::getInstance();	//create an Application labeled PROJEKT PRAKTIKUM
	myApp->			setLabel("PROJEKT PRAKTIKUM");

	/*	customize myVRState*/
	VRState* myVRState = 	new VRState("VRSTATE"); // create a VRState labeled VRSTATE
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));

	/*	customize virtual objects*/
	VirtualObject* 	myCubeObject1 = 	VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/cube.obj");	// create a Virtual Object by using the VirtualObject-Factory and add it to VRState manually
	myVRState->		addVirtualObject(	myCubeObject1);		// add to VRState manually
	//VirtualObject* 	myCubeObject2 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");	// create another Virtual Object from the same geometry

	VirtualObject* 	cube1 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube2 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube3 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube4 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube5 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube6 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube7 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube8 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube9 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube10 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube11 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube12 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube13 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube14 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube15 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube16 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube17 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube18 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube19 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");
	VirtualObject* 	cube20 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");

	glm::mat4		cube1M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 3.0f, 0.0f));
	cube1->getPhysicsComponent()->~PhysicsComponent();
	cube1-> setModelMatrix(		cube1M); 	// override default Model Matrix
	cube1->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -2.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube1));

	glm::mat4		cube2M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 3.0f, 0.0f));
	cube2->getPhysicsComponent()->~PhysicsComponent();
	cube2-> setModelMatrix(		cube2M); 	// override default Model Matrix
	cube2->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -1.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube2));

	glm::mat4		cube3M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 3.0f, 0.0f));
	cube3->getPhysicsComponent()->~PhysicsComponent();
	cube3-> setModelMatrix(		cube3M); 	// override default Model Matrix
	cube3->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -0.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube3));

	glm::mat4		cube4M = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 3.0f, 0.0f));
	cube4->getPhysicsComponent()->~PhysicsComponent();
	cube4-> setModelMatrix(		cube4M); 	// override default Model Matrix
	cube4->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 0.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube4));

	////////////////////////////////////////////////////////////////////////////////////////

	glm::mat4		cube5M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 0.0f, 0.0f));
	cube5->getPhysicsComponent()->~PhysicsComponent();
	cube5-> setModelMatrix(		cube5M); 	// override default Model Matrix
	cube5->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -2.5f, 0.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube5));

	glm::mat4		cube6M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
	cube6->getPhysicsComponent()->~PhysicsComponent();
	cube6-> setModelMatrix(		cube6M); 	// override default Model Matrix
	cube6->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -1.5f, 0.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube6));

	glm::mat4		cube7M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
	cube7->getPhysicsComponent()->~PhysicsComponent();
	cube7-> setModelMatrix(		cube7M); 	// override default Model Matrix
	cube7->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -0.5f, 0.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube7));

	glm::mat4		cube8M = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	cube8->getPhysicsComponent()->~PhysicsComponent();
	cube8-> setModelMatrix(		cube8M); 	// override default Model Matrix
	cube8->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube8));

	/////////////////////////////////////////////////////////////////////////////////////////

	glm::mat4		cube9M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 1.0f, 0.0f));
	cube9->getPhysicsComponent()->~PhysicsComponent();
	cube9-> setModelMatrix(		cube9M); 	// override default Model Matrix
	cube9->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -2.5f, 1.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube9));

	glm::mat4		cube10M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 1.0f, 0.0f));
	cube10->getPhysicsComponent()->~PhysicsComponent();
	cube10-> setModelMatrix(		cube10M); 	// override default Model Matrix
	cube10->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -1.5f, 1.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube10));

	glm::mat4		cube11M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 1.0f, 0.0f));
	cube11->getPhysicsComponent()->~PhysicsComponent();
	cube11-> setModelMatrix(		cube11M); 	// override default Model Matrix
	cube11->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -0.5f, 1.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube11));

	glm::mat4		cube12M = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	cube12->getPhysicsComponent()->~PhysicsComponent();
	cube12-> setModelMatrix(		cube12M); 	// override default Model Matrix
	cube12->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube12));

	/////////////////////////////////////////////////////////////////////////////////////////

	glm::mat4		cube13M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 2.0f, 0.0f));
	cube13->getPhysicsComponent()->~PhysicsComponent();
	cube13-> setModelMatrix(		cube13M); 	// override default Model Matrix
	cube13->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -2.5f, 2.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube13));

	glm::mat4		cube14M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 2.0f, 0.0f));
	cube14->getPhysicsComponent()->~PhysicsComponent();
	cube14-> setModelMatrix(		cube14M); 	// override default Model Matrix
	cube14->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -1.5f, 2.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube14));

	glm::mat4		cube15M = 	glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 2.0f, 0.0f));
	cube15->getPhysicsComponent()->~PhysicsComponent();
	cube15-> setModelMatrix(		cube15M); 	// override default Model Matrix
	cube15->	setPhysicsComponent(1.0f, 1.0f, 1.0f, -0.5f, 2.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube15));

	glm::mat4		cube16M = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 2.0f, 0.0f));
	cube16->getPhysicsComponent()->~PhysicsComponent();
	cube16-> setModelMatrix(		cube16M); 	// override default Model Matrix
	cube16->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube16));

	/////////////////////////////////////////////////////////////////////////////////////////

	glm::mat4		cube17M = 	glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
	cube17->getPhysicsComponent()->~PhysicsComponent();
	cube17-> setModelMatrix(		cube17M); 	// override default Model Matrix
	cube17->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 1.5f, 0.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube17));

	glm::mat4		cube18M = 	glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.0f, 0.0f));
	cube18->getPhysicsComponent()->~PhysicsComponent();
	cube18-> setModelMatrix(		cube18M); 	// override default Model Matrix
	cube18->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube18));

	glm::mat4		cube19M = 	glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 2.0f, 0.0f));
	cube19->getPhysicsComponent()->~PhysicsComponent();
	cube19-> setModelMatrix(		cube19M); 	// override default Model Matrix
	cube19->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 1.5f, 2.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube19));

	glm::mat4		cube20M = 	glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 3.0f, 0.0f));
	cube20->getPhysicsComponent()->~PhysicsComponent();
	cube20-> setModelMatrix(		cube20M); 	// override default Model Matrix
	cube20->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 1.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube20));

	glm::mat4		myModelMatrix1 = 	glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	myCubeObject1->getPhysicsComponent()->~PhysicsComponent();
	myCubeObject1-> setModelMatrix(		myModelMatrix1); 	// override default Model Matrix
	myCubeObject1->	setPhysicsComponent(5.0f, 0.2f, 5.0f, 0.0f, -1.0f, 0.0f, 0.0f);


	/*
	glm::mat4 myModelMatrix2 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f)), glm::vec3(5.0f, 5.0f, 0.2f));	// wall
	myCubeObject2->getPhysicsComponent()->~PhysicsComponent();
	myCubeObject2-> setModelMatrix(		myModelMatrix2);	// override default Model Matrix
	myCubeObject2-> setPhysicsComponent(5.0f,5.0f, 0.2f, 0.0f, 0.0f, -2.5f, 0.0f);
	 */

	/*	load some virtual objects into vr state scene*/	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically
	//PhysicsComponent* myCowObject1PhysicsComponent = 		myCowObject1->getPhysicsComponent();					// get PhysicsComponent pointer
	//myVRState->		attachListenerOnBeginningProgramCycle( 	new UpdatePhysicsWorldListener());
	//myVRState->		attachListenerOnBeginningProgramCycle(  new UpdateVirtualObjectModelMatrixListener(	cube1));	// update VirtualObject Model Matrix on every program cycle iteration
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

	/*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
	myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );

	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());

	std::cout << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	/*	add customized states to application state pool*/
	myApp->addState(	myVRState);		//add the VR State to Application

	myApp->setState(	"VRSTATE"); 	//set initial state to the state labeled MAINMENU
}

int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
}
