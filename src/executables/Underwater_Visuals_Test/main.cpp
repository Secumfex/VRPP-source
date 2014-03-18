#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "UnderwaterScene.h"

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

void configureTestingApplication(){
	/* customization of application or state*/
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

}

void configureVirtualObjects(){
	/* creation and customization of Virtual Objects */
	UnderwaterScene::createScene(testingState);

	
}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */
	testingApp->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));
}

void configureInputHandler(){
	/* customization of input handling */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress( 		new RecompileAndSetShaderListener(SHADERS_PATH "/Underwater_Visuals_Test/phong.vert", SHADERS_PATH "/Underwater_Visuals_Test/phong.frag"), GLFW_KEY_F5);
	testingInputHandler->attachListenerOnKeyPress( 		new PrintCameraStatusListener(UnderwaterScene::reflectedCamera), GLFW_KEY_R);

}

void configureRendering(){
	Shader* shader =  new Shader (SHADERS_PATH "/Underwater_Visuals_Test/phong.vert", SHADERS_PATH "/Underwater_Visuals_Test/phong.frag");
	Shader* reflection_shader =  new Shader (SHADERS_PATH "/Underwater_Visuals_Test/phong.vert", SHADERS_PATH "/Underwater_Visuals_Test/phong_clipping.frag");

	Listener* uniLightPos 	= new UploadUniformVec3Listener ("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, "uniformLightPosition");
	Listener* uniFogColor 	= new UploadUniformVec3Listener ("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, "uniformFogColor");
	Listener* uniFogBegin 	= new UploadUniformFloatListener("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin, "uniformFogBegin");
	Listener* uniFogEnd 	= new UploadUniformFloatListener("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end, "uniformFogEnd");
	
	testingApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( reflection_shader ));

	// 1: render Reflection Map
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( reflection_shader ));

	testingApp->attachListenerOnRenderManagerFrameLoop(uniLightPos);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogColor);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogBegin);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogEnd);		// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(	new ReflectionMapRenderPass(UnderwaterScene::framebuffer_water_reflection, UnderwaterScene::reflectedCamera, UnderwaterScene::scene_waterPlaneObject));
	
	// 2: render regular Scene
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(uniLightPos);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogColor);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogBegin);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogEnd);		// not clean, but easier to handle cuz of shader recompilation
	RenderloopPlaceHolderListener* renderloop = new RenderloopPlaceHolderListener(UnderwaterScene::scene_waterPlaneObject);
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderloop);

	// 3: render Water Surface with Reflection Map
	Shader* watershader = new Shader(SHADERS_PATH "/Underwater_Visuals_Test/water.vert", SHADERS_PATH "/Underwater_Visuals_Test/water.frag");
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( watershader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(uniLightPos);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogColor);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogBegin);	// not clean, but easier to handle cuz of shader recompilation
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogEnd);		// not clean, but easier to handle cuz of shader recompilation

	RenderWaterObjectWithShaderAndReflectionMapListener* renderwater = new RenderWaterObjectWithShaderAndReflectionMapListener(UnderwaterScene::scene_waterPlaneObject, watershader, UnderwaterScene::framebuffer_water_reflection);
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderwater);

	std::vector<std::string> uniforms = watershader->getUniformNames();
	for (int i = 0; i < uniforms.size(); i++){
		std::cout <<" uniform " << i << ": " << uniforms[i] << std::endl;
	}
}

void configureOtherStuff(){
	/* customization for other stuff */
	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("UNDER WATER RENDERING");
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

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
