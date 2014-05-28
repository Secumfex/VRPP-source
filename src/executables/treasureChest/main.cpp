#include "SomeListeners.h"
#include "Application/Application.h"
#include "Application/ApplicationListeners.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Tools/UtilityListeners.h"
#include "Physics/PhysicWorldSimulationListener.h"
#include "IO/IOManager.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

Application*    myApp;
VRState*        myState;
IOHandler*      myInputHandler;
RenderManager*  rm;


void configureTestingApplication(){
    /*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

    
}

void configureScene(ApplicationState* target){

  	myState->		attachListenerOnActivation(new SetClearColorListener(0,1,1)); // custom background color
	myState->       attachListenerOnActivation(new PrintCameraStatusListener( myState->getCamera()));
    myState->		attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener( IOManager::getInstance()->getDeltaTimePointer()));        // updates physics simulation

    
    /*************** initialization ***************/
    
    rm = RenderManager::getInstance();
    
    PlayerCamera* playercam = new PlayerCamera();
    playercam->setPosition(glm::vec3(3.5f, 7.0f, 10.0f));
	playercam->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	myState->setCamera(playercam);
	rm->setLightPosition(glm::vec3(500,2,-2),0); // for uniformLightPerspective
    //rm->getCurrentFrustum()->setCamera(playercam);
    
    
    /*************** virtual objects ***************/
    
 	VirtualObject* scene_chest_top;
    scene_chest_top	= target->createVirtualObject(RESOURCES_PATH "/treasureChest_scene/treasureChest_top.dae",VirtualObjectFactory::OTHER, 0.0f, 1, true);

    VirtualObject* scene_chest_bottom;
    scene_chest_bottom = target->createVirtualObject(RESOURCES_PATH "/treasureChest_scene/treasureChest_bottom.dae",VirtualObjectFactory::OTHER, 0.0f, 1, true);
   // scene_chest_top->setModelMatrix(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(0.0,2.6,0.0)), 180.0f, glm::vec3(0.0,1.0,1.0)));

    
    /*************** shaders ***************/

    Shader* phong_shader 		= new Shader( SHADERS_PATH "/treasureChest_shader/shader_chest.vert", SHADERS_PATH 	"/treasureChest_shader/shader_chest.frag");
    
    Shader* depth_shader 		= new Shader( SHADERS_PATH "/treasureChest_shader/Depthwrite.vert", SHADERS_PATH 	"/treasureChest_shader/Depthwrite.frag");
    
	Shader* composition_shader  = new Shader( SHADERS_PATH "/treasureChest_shader/screenFill.vert", SHADERS_PATH "/treasureChest_shader/finalCompositing.frag");
    
    
    /*************** 1st framebuffer object ***************/
    
    FrameBufferObject* framebuffer_render = new FrameBufferObject(800, 600);
    myState->attachListenerOnActivation(new SetFrameBufferObjectListener(framebuffer_render)); //bindFBO;
    
    framebuffer_render->createPositionTexture();
    framebuffer_render->createNormalTexture();
    framebuffer_render->createColorTexture();
	framebuffer_render->createSpecularTexture();
    framebuffer_render->makeDrawBuffers();
    
    /*************** render scene in FBO ***************/
    // bindFBO
    myApp->attachListenerOnRenderManagerFrameLoop(new SetFrameBufferObjectListener(framebuffer_render));
	myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(phong_shader));

	myApp->attachListenerOnRenderManagerFrameLoop(new AlternativeRenderloopListener());
    // unbindFBO
    myApp->attachListenerOnRenderManagerFrameLoop(new UnbindFrameBufferObjectListener());

    
    
    
   /*************** 2nd framebuffer objects ***************/
   
    FrameBufferObject* framebuffer_render2 = new FrameBufferObject(800, 600);
    myState->attachListenerOnActivation(new SetFrameBufferObjectListener(framebuffer_render2)); //bindFBO;
    
    framebuffer_render2->createShadowMap();
    framebuffer_render2->makeDrawBuffers();
    
    /*************** 'render' shadows in FBO ***************/
    myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(depth_shader));
	myApp->attachListenerOnRenderManagerFrameLoop(new AlternativeRenderloopListener());
    myApp->attachListenerOnRenderManagerFrameLoop(new UnbindFrameBufferObjectListener());
 
    
    
    /*************** compositing ***************/
    
	myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(composition_shader));
	myApp->attachListenerOnRenderManagerFrameLoop(new RenderScreenFillingTriangleListener());
    
    framebuffer_render->unbindAllTextures();
    
    
    
    /*************** interaction ***************/
    
    IOHandler* myVRStateIOHandler = myState-> getIOHandler();
    myVRStateIOHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), 	GLFW_KEY_ESCAPE);	// Terminate Application by pressing Escape
    myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.0,0.0,0.0),	GLFW_KEY_1);		// pressing '1' : black background
    myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(1.0,1.0,1.0), 	GLFW_KEY_2);		// pressing '2' : white background
    myVRStateIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.44,0.5,0.56), 	GLFW_KEY_3);		// pressing '3' : default greyish-blue background
    myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_A);		// pressing '<-' : view direction at an angle to the left
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_A);
    myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_D);	// pressing '->' : view direction at an angle to the right
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_D);
    myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.0f, 0.1f), 	GLFW_KEY_W);		// pressing '<-' : view direction straight ahead
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_W);
    myVRStateIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myState->getCamera(), 0.0f, -0.1f), 	GLFW_KEY_Z);		// pressing '->' : view direction straight ahead
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()), 								GLFW_KEY_Z);
    

    btRigidBody* camBody = playercam->getRigidBody();
    

    myVRStateIOHandler->attachListenerOnKeyPress(new MovePlayerCameraListener(myState->getCamera(), -0.25,0.0,0.0, scene_chest_bottom, scene_chest_top, camBody ), 	GLFW_KEY_LEFT);
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()),              GLFW_KEY_LEFT);
    myVRStateIOHandler->attachListenerOnKeyPress(new MovePlayerCameraListener(myState->getCamera(), 0.25,0.0,0.0, scene_chest_bottom, scene_chest_top, camBody),      GLFW_KEY_RIGHT);
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()),              GLFW_KEY_RIGHT);
    myVRStateIOHandler->attachListenerOnKeyPress(new MovePlayerCameraListener(myState->getCamera(), 0.0,0.0,-0.25, scene_chest_bottom, scene_chest_top, camBody),      GLFW_KEY_UP);
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()),              GLFW_KEY_UP);
    myVRStateIOHandler->attachListenerOnKeyPress(new MovePlayerCameraListener(myState->getCamera(), 0.0,-0.25,0.25, scene_chest_bottom, scene_chest_top, camBody),      GLFW_KEY_DOWN);
    myVRStateIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myState->getCamera()),              GLFW_KEY_DOWN);

    
}


void configureMyApp(){
	/*	customize application a little bit */
	myApp = 		Application::getInstance();	//create an Application labeled CHEST
	myApp->			setLabel("TREASURE_CHEST - please zoom in");
    
	/*	customize myVRState */
	myState = 	new VRState("FEATURE"); // create a VRState labeled FEATURE
    myApp->addState(	myState);		//add the VR State to Application
    
    configureTestingApplication();
    
	configureScene(myState);
}


int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run applications

	return 0;				// 3 end :)
}
