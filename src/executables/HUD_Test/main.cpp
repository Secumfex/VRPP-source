#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "UnderwaterScene.h"
#include "HUD.h"

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

/**SOME OTHER SHIT**/
unsigned int vaoID[1];

unsigned int vboID[1];

int numIndices;
int numVertices;
int numFaces;

static void createSquare(void){
		float* vertices = new float[18];

		vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.0; // Bottom left corner
		vertices[3] = -0.5; vertices[4] = 0.5; 	vertices[5] = 0.0; // Top left corner
		vertices[6] =  0.5;	vertices[7] = 0.5; 	vertices[8] = 0.0; // Top Right corner

		vertices[9]  =  0.5; 	vertices[10] = -0.5; 	vertices[11] = 0.0; // Bottom right corner
		vertices[12] = -0.5; 	vertices[13] = -0.5; 	vertices[14] = 0.0; // Bottom left corner
		vertices[15] =  0.5; 	vertices[16] = 0.5;	 	vertices[17] = 0.0; // Top Right corner

		glGenVertexArrays(1,&vaoID[0]);
		glBindVertexArray(vaoID[0]);

		glGenBuffers(1,vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		numIndices = 6;
		numVertices = 6;
		numFaces = 2;

		delete [] vertices;
}
/****************************/

void configureTestingApplication(){
	/* customization of application or state*/
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
}

void configureVirtualObjects(){
	/* creation and customization of Virtual Objects */
	UnderwaterScene::createScene(testingState);

	createSquare();
}

void configureOtherStuff(){
	HUD::createHUD(testingState);

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
	Shader* phong_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong.frag");
	Shader* underwater_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong_caustics.vert",SHADERS_PATH  "/Underwater_Visuals_Test/phong_caustics.frag");
	Shader* reflection_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
	Shader* refraction_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
	Shader* godRay_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/godrays.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/godrays.frag");
	Shader* water_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/water.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/water.frag");
	Shader* particles_shader	= new Shader( SHADERS_PATH "/HUD/Copy of particles.vert"	, SHADERS_PATH  "/HUD/Copy of particles.frag");
	Shader* composition_shader  = new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"	, SHADERS_PATH  "/Underwater_Visuals_Test/finalCompositing.frag");
	Shader* HUDShader			= new Shader( SHADERS_PATH "/HUD/HUD.pervert"								, SHADERS_PATH  "/HUD/HUD.faggot");

	FrameBufferObject* preCompositingScene = new FrameBufferObject(800, 600);
	preCompositingScene->bindFBO();
	preCompositingScene->createPositionTexture();
	preCompositingScene->makeDrawBuffers();	// draw color to color attachment 0

	preCompositingScene->unbindFBO();

	Listener* uniCamPos		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", testingState->getCamera()->getPositionPointer(), 		"uniformCameraWorldPos");
	Listener* uniClipPoint 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", glm::vec3(0.0, UnderwaterScene::water_height, 0.0), 	"uniformClippingPoint");
	Listener* uniClipNorm	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal , 				"uniformClippingNormal");
	Listener* uniClipNormInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal_inverse , 		"uniformClippingNormal");
	Listener* uniFogColor 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, 							"uniformFogColor");
	Listener* uniFogColorInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color_inverse, 					"uniformFogColor");
	Listener* uniLightPos 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, 						"uniformLightPosition");

	Listener* uniPreCompMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 9, "uniformPreCompositionMap",preCompositingScene->getPositionTextureHandle());
	Listener* uniGodRayMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 8, "uniformGodRayMap", 		UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
	Listener* uniRefrText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "uniformRefractionMap", 	UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle());
	Listener* uniReflText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 11, "uniformReflectionMap", 	UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle());
	Listener* uniCausticsTex= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniCausticsTex2=new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniPartMap	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 14,"uniformParticlesMap", 	UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle());
	Listener* uniPartText	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 4,"uniformParticleTexture",   UnderwaterScene::particlesTexture->getTextureHandle());

	Listener* uniSunVPersp	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunViewPerspective, "uniformProjectorViewPerspective");
	Listener* uniReflMatr	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", UnderwaterScene::reflectedCamera->getViewMatrixPointer(), "uniformReflectionView");

	Listener* uniFogBegin 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin, "uniformFogBegin");
	Listener* uniFogBeginInv= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin_inverse, "uniformFogBegin");
	Listener* uniFogEnd 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end, "uniformFogEnd");
	Listener* uniFogEndInv 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end_inverse, "uniformFogEnd");
	Listener* uniTime 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");
	Listener* uniTime2 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");
	Listener* uniTime3 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");

	Listener* uniTime4 		= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), "uniformTime");

	Listener* uniSinusWave  = new UploadUniformSinusWaveListener("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), 0.5f, 0.0f, "uniformSinus");

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

//	// 6: render Particles in the water
//	testingApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( particles_shader ));
//	testingApp->attachListenerOnRenderManagerFrameLoop( uniPartText);
//	testingApp->attachListenerOnRenderManagerFrameLoop( uniSinusWave);
//	ParticlesRenderPass* renderParticles = new ParticlesRenderPass(UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);
//	testingApp->attachListenerOnRenderManagerFrameLoop(( renderParticles));

	// 8: render HUD
	testingApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( HUDShader ));
	//testingApp->attachListenerOnRenderManagerFrameLoop( uniPartText);
	testingApp->attachListenerOnRenderManagerFrameLoop( uniSinusWave);
	ParticlesRenderPass* renderHUD = new ParticlesRenderPass(UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);
	testingApp->attachListenerOnRenderManagerFrameLoop( uniTime4 );
	testingApp->attachListenerOnRenderManagerFrameLoop(( renderHUD));

	// 7: Compositing
	testingApp->attachListenerOnRenderManagerFrameLoop( new SetCurrentShaderListener( composition_shader ));
	testingApp->attachListenerOnRenderManagerFrameLoop( uniPreCompMap );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniGodRayMap );
	testingApp->attachListenerOnRenderManagerFrameLoop( uniPartMap );
	RenderGraphicsComponentListener* renderCompositing = new RenderScreenFillingTriangleListener();
	testingApp->attachListenerOnRenderManagerFrameLoop( renderCompositing );
}


void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("HUD Test");
	testingState 	= 	new VRState("UNDER WATER RENDERING");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();
	configureOtherStuff();
	configurePhysics();
	configureInputHandler();
	configureRendering();
}

int main() {

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
