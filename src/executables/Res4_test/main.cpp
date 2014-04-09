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

    
}

void configureScene(ApplicationState* target){
    
  	myState->		attachListenerOnActivation(new SetClearColorListener(0.0,0.0,0.5)); // custom background color
	myState->       attachListenerOnActivation(new PrintCameraStatusListener( myState->getCamera()));
    myState->		attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener( IOManager::getInstance()->getDeltaTimePointer()));        // updates physics simulation
    // Camera* necam = new Camera();
    PlayerCamera* playercam = new PlayerCamera();
	myState->setCamera(playercam);

    
    glm::vec3 lightPosition(0.0f,1000.0f,0.0f);
	VirtualObject* scene_chest_Object;

	   
    scene_chest_Object	= target->createVirtualObject(RESOURCES_PATH "/chest_scene/nicer_chest.dae",VirtualObjectFactory::OTHER, 0.0f, 1, true);
    /* to animate the VirtualObject */
 //   Listener* new_lesten = new AnimateRotatingModelMatrixListener(scene_chest_Object);
 //   myApp->attachListenerOnRenderManagerFrameLoop(new_lesten);

    /******************* framebuffer objects *****************************************/
    GLFWwindow* window = RenderManager::getInstance()->getWindow();

    int width, height;
	glfwGetFramebufferSize(window, &width, &height);
    FrameBufferObject* framebuffer_render;
    
    framebuffer_render = new FrameBufferObject(width, height);
    framebuffer_render->bindFBO();
    framebuffer_render->createPositionTexture();
    framebuffer_render->createNormalTexture();
    framebuffer_render->makeDrawBuffers();	// draw color to color attachment 0
   // framebuffer_render->unbindFBO();
    
    
    Shader* phong_shader 		= new Shader( SHADERS_PATH "/chest_test/shader_chest.vert"	, SHADERS_PATH 	"/chest_test/shader_chest.frag");
	//Shader *composition_shader  = new Shader( SHADERS_PATH "/chest_test/screenFill.vert", SHADERS_PATH "/chest_test/finalCompositing.frag");
    
    //myApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( phong_shader ));
    
    // 4: render regular Scene
    glEnable(GL_DEPTH_TEST);
    framebuffer_render->bindFBO();
	myApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( phong_shader ));
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	AlternativeRenderloopListener* renderloop = new AlternativeRenderloopListener();
	myApp->attachListenerOnRenderManagerFrameLoop(	renderloop );
    framebuffer_render->unbindFBO();
  
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glDisable(GL_DEPTH_TEST);
    // 7: Compositing
//	myApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( composition_shader ));
//	RenderGraphicsComponentListener* renderCompositing = new RenderScreenFillingTriangleListener();

//	myApp->attachListenerOnRenderManagerFrameLoop( renderCompositing );

}

void configureRendering(){

}


void configureMyApp(){
	/*	customize application a little bit */
	myApp = 		Application::getInstance();	//create an Application labeled CHEST
	myApp->			setLabel("CHEST");
    
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
