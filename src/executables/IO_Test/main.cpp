#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicWorldSimulationListener.h"



/*
*	This executable tests various Input/Output related functionalities
*/	


Kinect*			kinect;
Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;
VirtualObject*  cowObject;
PlayerCamera*   playercam;



void configureTestingApplication(){
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
	
	testingApp->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));
	playercam = new PlayerCamera();
	testingState->setCamera(playercam);
}

void configureVirtualObjects(){
	cowObject = testingState->createVirtualObject(RESOURCES_PATH "/cow.obj", VirtualObjectFactory::OTHER, 5.0f);	// to have something in the scene
	cowObject->translate(glm::vec3(0.0f,4.0f,0.0f));
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cowObject));
	
	VirtualObject* groundObject = testingState->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER);

	VirtualObject* wallObject1 = testingState->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", VirtualObjectFactory::OTHER);	// to have something in the scene
	VirtualObject* wallObject2 = testingState->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", VirtualObjectFactory::OTHER);	// to have something in the scene
	VirtualObject* cubeObject2 = testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::OTHER, 10.0f);	// to have something in the scene
	cubeObject2->translate(glm::vec3(0.0f,2.0f,0.0f));
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cubeObject2));
	
}

void configurePhysics(){
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	//create an invisible ground plane
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));
    	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
   	 	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);

	btRigidBody* camBody = playercam->getRigidBody();
	playercam->setPosition(0.0f,2.0f,5.0f);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);

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

	testingInputHandler->attachListenerOnKeyPress(new PrintValueListener( IOManager::getInstance()->getDeltaTimePointer(), "d_t : "), GLFW_KEY_T );
	testingInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( testingState->getCamera()), GLFW_KEY_I );
	testingInputHandler->attachListenerOnKeyPress(new ApplyLinearImpulseOnRigidBody(playercam->getRigidBody(), glm::vec3(0.0f,5.0f,0.0f)), GLFW_KEY_SPACE );
	testingInputHandler->attachListenerOnKeyPress(new SetCameraPositionListener(playercam, glm::vec3(0.0f,5.0f,0.0f)), GLFW_KEY_R );


	SelectionHandler* sh = testingInputHandler->getSelectionHandler();
	testingInputHandler->attachListenerOnMouseButtonPress(new ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(sh, testingState->getCamera(),50.0f), GLFW_MOUSE_BUTTON_RIGHT);
	testingApp->attachListenerOnRenderManagerFrameLoop(new ApplyForceOnCameraListener(playercam ,kinect, kinect->force) );
}

void configureRendering(){
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test_Textures/phong.vert", SHADERS_PATH "/Phong_Test_Textures/phong.frag")));
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

int main() {
	
	


//directionForce=&direction;
	
	kinect->initKinect();
//	kinect->force=&(kinect->forceDirection);
//	kinect->forceOldp=&(kinect->forceOld);
	//kinect->forceNewp=&(kinect->forceNew);

	configureApplication();	// 1 do some customization

	testingApp->run();		// 2 run application
	
	return 0;				// 3 end :)
}

