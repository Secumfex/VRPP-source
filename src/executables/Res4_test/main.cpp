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
RenderManager*  rm;

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
    rm = RenderManager::getInstance();
    GLFWwindow* window = rm->getWindow();
    int width, height;
	glfwGetFramebufferSize(window, &width, &height);
    RenderQueue* rq = myState->getRenderQueue();
    PlayerCamera* playercam = new PlayerCamera();
    Frustum* frustum = myState->getFrustum();
    playercam->setPosition(glm::vec3(0.0f, 2.0f, -10.0f));
	playercam->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	myState->setCamera(playercam);
	rm->setLightPosition(glm::vec3(5,2,-2),0);
    
    
 	VirtualObject* scene_chest_Object;
    scene_chest_Object	= target->createVirtualObject(RESOURCES_PATH "/chest_scene/nicer_chest.dae",VirtualObjectFactory::OTHER, 0.0f, 1, true);
    /* to animate the VirtualObject */
    // Listener* new_lesten = new AnimateRotatingModelMatrixListener(scene_chest_Object);
    //   myApp->attachListenerOnRenderManagerFrameLoop(new_lesten);

    Shader* phong_shader 		= new Shader( SHADERS_PATH "/chest_test/shader_chest.vert"	, SHADERS_PATH 	"/chest_test/shader_chest.frag");
	Shader *composition_shader  = new Shader( SHADERS_PATH "/chest_test/screenFill.vert", SHADERS_PATH "/chest_test/finalCompositing.frag");

    rq->addShader(phong_shader);
    rq->addCompositingShader(composition_shader);
    
    
    /******************* framebuffer objects *****************************************/
    
    FrameBufferObject* framebuffer_render = new FrameBufferObject(width, height);
   // framebuffer_render->bindFBO();
    
    myState->attachListenerOnActivation(new SetFrameBufferObjectListener(framebuffer_render)); //bindFBO;

    framebuffer_render->createPositionTexture();
    framebuffer_render->createNormalTexture();
    framebuffer_render->createColorTexture();
	framebuffer_render->createSpecularTexture();
	framebuffer_render->createShadowMap();
    
    
    framebuffer_render->makeDrawBuffers();
    
	// draw color to color attachment 0
   // framebuffer_render->unbindFBO();
    
    rm->setRenderQueue(rq);
    rm->setCurrentFBO(framebuffer_render);
    rm->setCamera(playercam);
    rm->setCurrentFrustum(frustum);
    
    frustum->updateModelMatrix();
    
    //glm::vec3 lightPosition(0.0f,1000.0f,0.0f);


  //  myApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( phong_shader ));
    
    // 4: render regular Scene
   framebuffer_render->bindFBO();
    SetFrameBufferObjectListener *bindFBO = new SetFrameBufferObjectListener(framebuffer_render);
    myApp->attachListenerOnRenderManagerFrameLoop(bindFBO);
    
    
	myApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( phong_shader ));
	AlternativeRenderloopListener* renderloop = new AlternativeRenderloopListener();
	myApp->attachListenerOnRenderManagerFrameLoop(	renderloop );
    UnbindFrameBufferObjectListener* unbindFBO = new UnbindFrameBufferObjectListener();
myApp->attachListenerOnRenderManagerFrameLoop(unbindFBO);
   // framebuffer_render->unbindFBO();
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    // 7: Compositing
	myApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( composition_shader ));
	RenderGraphicsComponentListener* renderCompositing = new RenderScreenFillingTriangleListener();

	myApp->attachListenerOnRenderManagerFrameLoop( renderCompositing );
    
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
