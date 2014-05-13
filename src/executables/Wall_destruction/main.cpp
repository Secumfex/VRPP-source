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
	VirtualObject* 	floor = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 0.0, 1);
	glm::mat4		myModelMatrix1 = 	glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	floor-> setModelMatrix(		myModelMatrix1); 	// override default Model Matrix
	floor->	setPhysicsComponent(10.0f, 0.4f, 10.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1);

	VirtualObject* 	cube1 = 	myVRState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube1));

	VirtualObject* 	cube2 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	cube2->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube2));

	VirtualObject* 	cube4 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	cube4->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube4));

//////

	VirtualObject* 	cube5 = 	myVRState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	cube5->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube5));

	VirtualObject* 	cube6 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	cube6->translate(glm::vec3(2.0f, 2.0f, 0.0f));
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube6));

	VirtualObject* 	cube8 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
	cube8->translate(glm::vec3(-2.0f, 2.0f, 0.0f));
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube8));

	//////

		VirtualObject* 	cube9 = 	myVRState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
		cube9->translate(glm::vec3(0.0f, 4.0f, 0.0f));
		myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube9));

		VirtualObject* 	cube10 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
		cube10->translate(glm::vec3(2.0f, 4.0f, 0.0f));
		myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube10));

		VirtualObject* 	cube12 = 	myVRState-> createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 1.0, 8);
		cube12->translate(glm::vec3(-2.0f, 4.0f, 0.0f));
		myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube12));


	/*
	glm::mat4		myModelMatrix1 = 	glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(5.0f, 0.2f, 5.0f));	//floor
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
//	myVRStateIOHandler->attachListenerOnMouseButtonPress(new PickRayListener(myVRState->getCamera()), GLFW_MOUSE_BUTTON_2);		//
	myVRStateIOHandler->attachListenerOnMouseButtonPress(new ShootSphereListener(myVRState->getCamera(), myVRState), GLFW_MOUSE_BUTTON_LEFT);

	SelectionHandler* sh = myVRStateIOHandler->getSelectionHandler();
	myVRStateIOHandler->attachListenerOnMouseButtonPress(new ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(sh, myVRState->getCamera(),50.0f), GLFW_MOUSE_BUTTON_RIGHT);


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
