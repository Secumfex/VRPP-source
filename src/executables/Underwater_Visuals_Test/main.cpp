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
	Shader* phong_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"	, SHADERS_PATH 	"/Underwater_Visuals_Test/phong.frag");
	Shader* underwater_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong_caustics.vert", SHADERS_PATH "/Underwater_Visuals_Test/phong_caustics.frag");
	Shader* reflection_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"	, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
	Shader* refraction_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"	, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
	Shader* godRay_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/godrays.vert"	, SHADERS_PATH 	"/Underwater_Visuals_Test/godrays.frag");
	Shader* water_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/water.vert"	, SHADERS_PATH 	"/Underwater_Visuals_Test/water.frag");
	Shader *composition_Shader  = new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert", SHADERS_PATH "/Underwater_Visuals_Test/finalCompositing.frag");

	FrameBufferObject* preCompositingScene = new FrameBufferObject(800, 600);
	preCompositingScene->bindFBO();
	preCompositingScene->createPositionTexture();
	preCompositingScene->makeDrawBuffers();	// draw color to color attachment 0
	preCompositingScene->unbindFBO();

	Listener* uniCamPos		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", testingState->getCamera()->getPositionPointer(), "uniformCameraWorldPos");
	Listener* uniCausticsTex= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniCausticsTex2= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniClipPoint 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", glm::vec3(0.0, UnderwaterScene::water_height, 0.0), "uniformClippingPoint");
	Listener* uniClipNorm	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal , "uniformClippingNormal");
	Listener* uniClipNormInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal_inverse , "uniformClippingNormal");
	Listener* uniFogColor 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, "uniformFogColor");
	Listener* uniFogBegin 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin, "uniformFogBegin");
	Listener* uniFogEnd 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end, "uniformFogEnd");
	Listener* uniFogColorInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color_inverse, "uniformFogColor");
	Listener* uniFogBeginInv= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin_inverse, "uniformFogBegin");
	Listener* uniFogEndInv 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end_inverse, "uniformFogEnd");
	Listener* uniLightPos 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, "uniformLightPosition");
	Listener* uniGodRayMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 8, "uniformGodRayMap", UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
	Listener* uniPreCompMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 9, "uniformPreCompositionMap", preCompositingScene->getPositionTextureHandle());
	Listener* uniReflMatr	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", UnderwaterScene::reflectedCamera->getViewMatrixPointer(), "uniformReflectionView");
	Listener* uniRefrText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "uniformRefractionMap", UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle());
	Listener* uniReflText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 11, "uniformReflectionMap", UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle());
	Listener* uniSunVPersp	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunViewPerspective, "uniformProjectorViewPerspective");
	Listener* uniTime 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");
	Listener* uniTime2 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");
	Listener* uniTime3 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");

	Listener* setClearColor 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColor2 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColorInv 	= new SetClearColorListener 		( &UnderwaterScene::fog_color_inverse, 1.0);

	Listener* bindWaterRefrFBO	= new SetFrameBufferObjectListener ( UnderwaterScene::framebuffer_water_refraction );
	Listener* bindWaterReflFBO	= new SetFrameBufferObjectListener ( UnderwaterScene::framebuffer_water_reflection );
	Listener* bindWaterGodRayFBO= new SetFrameBufferObjectListener ( UnderwaterScene::framebuffer_water_god_rays );
	Listener* bindPreCompFBO	= new SetFrameBufferObjectListener ( preCompositingScene );

	Listener* unbindCurrentFBO	= new UnbindFrameBufferObjectListener ();


	testingApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( reflection_shader ));

	// 1: render Reflection Map
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( reflection_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(	setClearColor );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniLightPos );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogColor );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogBegin );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogEnd );		
	testingApp->attachListenerOnRenderManagerFrameLoop( uniClipPoint );		
	testingApp->attachListenerOnRenderManagerFrameLoop( uniClipNorm );		
	testingApp->attachListenerOnRenderManagerFrameLoop(	new ReflectionMapRenderPass(UnderwaterScene::framebuffer_water_reflection, UnderwaterScene::reflectedCamera, UnderwaterScene::scene_waterPlaneObject));
	
	// 2: render Refraction Map
	testingApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( refraction_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(	setClearColorInv );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniLightPos  );		
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogColorInv  );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogBeginInv  );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogEndInv    );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniClipPoint );		
	testingApp->attachListenerOnRenderManagerFrameLoop( uniClipNormInv  );	
	RefractionMapRenderPass* renderRefraction = new RefractionMapRenderPass(UnderwaterScene::framebuffer_water_refraction, UnderwaterScene::scene_waterPlaneObject);
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderRefraction );
	
	// 3: render Godrays into FBO
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( godRay_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(uniCausticsTex2);
	testingApp->attachListenerOnRenderManagerFrameLoop(uniSunVPersp);
	testingApp->attachListenerOnRenderManagerFrameLoop(uniTime3);
	testingApp->attachListenerOnRenderManagerFrameLoop(uniCamPos);
	GodRaysRenderPass* renderGodRays = new GodRaysRenderPass(UnderwaterScene::framebuffer_water_god_rays);
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderGodRays );

	// 4: render regular Scene
	testingApp->attachListenerOnRenderManagerFrameLoop(bindPreCompFBO);
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( underwater_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(	setClearColor2 );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniLightPos );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogColor );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogBegin );	
	testingApp->attachListenerOnRenderManagerFrameLoop( uniFogEnd );		
	testingApp->attachListenerOnRenderManagerFrameLoop( uniCausticsTex );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniSunVPersp );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniTime2 );
	RenderloopPlaceHolderListener* renderloop = new RenderloopPlaceHolderListener(UnderwaterScene::scene_waterPlaneObject);	// Render Everything except waterPlaneObject
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderloop );

	// 5: render Water Surface with Reflection Map and RefractionMap
	testingApp->attachListenerOnRenderManagerFrameLoop(	new SetCurrentShaderListener( water_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop(uniLightPos);	
	testingApp->attachListenerOnRenderManagerFrameLoop(uniReflMatr);	
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogColor);	
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogBegin);	
	testingApp->attachListenerOnRenderManagerFrameLoop(uniFogEnd);		
	testingApp->attachListenerOnRenderManagerFrameLoop(uniTime);		
	testingApp->attachListenerOnRenderManagerFrameLoop(uniReflText);
	testingApp->attachListenerOnRenderManagerFrameLoop(uniRefrText);
	RenderVirtualObjectListener* renderwater = new RenderVirtualObjectListener(UnderwaterScene::scene_waterPlaneObject);
	testingApp->attachListenerOnRenderManagerFrameLoop(	renderwater);
	testingApp->attachListenerOnRenderManagerFrameLoop( unbindCurrentFBO );

	// 6: Compositing 
	// TODO: Render into FBOs and do a final Compositing Renderpass

	testingApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( composition_Shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop( uniPreCompMap );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniGodRayMap );
	RenderGraphicsComponentListener* renderCompositing = new RenderScreenFillingTriangleListener();
	testingApp->attachListenerOnRenderManagerFrameLoop( renderCompositing );
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
