#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "IO/PlayerCamera.h"
#include "Physics/PhysicWorld.h"
#include "IO/IOManager.h"

#include "SomeListeners.h" // until missing functionality is added

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

Application*    myApp;
VRState*        myState;
IOHandler*      myInputHandler;

void configureTestingApplication(){
    /*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
    myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );

    
}

void configureScene(ApplicationState* target){
    glm::vec3 lightPosition(0.0f,1000.0f,0.0f);
    VirtualObject* scene_groundObject;
	VirtualObject* scene_sun_Object;
	VirtualObject* scene_chest_Object;
    
	FrameBufferObject* framebuffer_render;
    
    scene_groundObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", 		VirtualObjectFactory::OTHER);
    scene_sun_Object 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", 	VirtualObjectFactory::OTHER);
    scene_chest_Object	= target->createVirtualObject(RESOURCES_PATH "/chest_textured.obj",VirtualObjectFactory::OTHER);
    GraphicsComponent* newgc = scene_chest_Object->getGraphicsComponent()[0];
    newgc->setModelMatrixGc(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,0.0f)));
    //if (scene_sun_Object->getGraphicsComponent().size() > 0){
      //  scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
    //}
    
    /******************* framebuffer objects *****************************************/
    framebuffer_render = new FrameBufferObject(800,600);
    framebuffer_render->bindFBO();
    framebuffer_render->createPositionTexture();
    framebuffer_render->makeDrawBuffers();	// draw color to color attachment 0
    framebuffer_render->unbindFBO();

}


void configureMyApp(){
	/*	customize application a little bit */
	myApp = 		Application::getInstance();	//create an Application labeled CHEST
	myApp->			setLabel("CHEST");

    
	/*	customize myVRState */
	myState = 	new VRState("FEATURE"); // create a VRState labeled FEATURE
	myState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));                // console output when virtual object is added
	myState->		attachListenerOnActivation(new SetClearColorListener(0.0,0.0,0.5)); // custom background color
	myState->       attachListenerOnActivation(new PrintCameraStatusListener( myState->getCamera()));
    myState->		attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener( IOManager::getInstance()->getDeltaTimePointer()));        // updates physics simulation
   // Camera* necam = new Camera();
    PlayerCamera* playercam = new PlayerCamera();
	myState->setCamera(playercam);
    
    
	configureScene(myState);
    
    /* create an invisible ground plane */
 /*   btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
    //create an invisible ground plane
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);
  
	btRigidBody* camBody = playercam->getRigidBody();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);
*/
					

    /* customize IOHandler */
	myInputHandler = myState-> getIOHandler();
	// attach some listeners to keyboard key presses
	myInputHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), 	GLFW_KEY_ESCAPE);	// Terminate Application by pressing Escape
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_LEFT);		// pressing '<-' : view direction at an angle to the left
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_LEFT);
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_RIGHT);	// pressing '->' : view direction at an angle to the right
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_RIGHT);
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.0f, 0.1f), 	GLFW_KEY_UP);		// pressing '<-' : view direction straight ahead
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_UP);
	myInputHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.0f, -0.1f), 	GLFW_KEY_DOWN);		// pressing '->' : view direction straight ahead
	myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_DOWN);
    myInputHandler->attachListenerOnKeyPress(new MovePlayerCameraListener(myState->getCamera(), 0.0f, -0.25f, 0.1f), 	GLFW_KEY_L);		// pressing '->' : view direction straight ahead
    myInputHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_L);
    

    configureTestingApplication();
	
	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());
    

	/*	add customized states to application state pool*/
	myApp->addState(	myState);		//add the VR State to Application

	myApp->setState(	"FEATURE"); 	//set initial state to the state labeled FEATURE
}

int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run applications

	return 0;				// 3 end :)
}
