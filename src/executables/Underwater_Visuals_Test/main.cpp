#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "UnderwaterScene.h"

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

/** Static Vertex Array Object : Quad, since VirtualObjectFactory functionality is buggy**/
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
	Shader* particles_shader	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/particles.vert"	, SHADERS_PATH  "/Underwater_Visuals_Test/particles.frag");
	Shader *composition_shader  = new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"	, SHADERS_PATH  "/Underwater_Visuals_Test/finalCompositing.frag");
	Shader *simpleTex			= new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"   , SHADERS_PATH  "/GBuffer/simpleTexture.frag");

	Shader* gbuffer_shader		= new Shader( SHADERS_PATH "/Underwater_visuals_Test/GBuffer.vert"      , SHADERS_PATH  "/Underwater_visuals_Test/GBuffer_normalTexture.frag");
	Shader* gbuffer_compositing_shader= new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"      , SHADERS_PATH  "/Underwater_visuals_Test/gbuffer_compositing.frag");

	FrameBufferObject* gbuffer_fbo = new FrameBufferObject(800,600);
	gbuffer_fbo->bindFBO();
	gbuffer_fbo->createPositionTexture();
	gbuffer_fbo->createNormalTexture();
	gbuffer_fbo->createColorTexture();
	gbuffer_fbo->makeDrawBuffers();
	gbuffer_fbo->unbindFBO();

	FrameBufferObject* gbuffer_compositing_fbo = new FrameBufferObject(800,600);
	gbuffer_compositing_fbo->bindFBO();
	gbuffer_compositing_fbo->createPositionTexture();
	gbuffer_compositing_fbo->makeDrawBuffers();
	gbuffer_compositing_fbo->unbindFBO();

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

//	Listener* uniPreCompMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 9, "uniformPreCompositionMap",preCompositingScene->getPositionTextureHandle());
//	Listener* uniGodRayMap	= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 8, "uniformGodRayMap", 		UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
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

	Listener* uniSinusWave  = new UploadUniformSinusWaveListener("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), 0.5f, 0.0f, "uniformSinus");

	Listener* setClearColor 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColor2 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColorInv 	= new SetClearColorListener 		( &UnderwaterScene::fog_color_inverse, 1.0);

	testingApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( reflection_shader ));

	// -1: render into GBuffer
	GBufferRenderPass* gbufferRenderPass = new GBufferRenderPass(gbuffer_shader, gbuffer_fbo);
	gbufferRenderPass->setClearColorBufferBit(true);
	gbufferRenderPass->setInitialGraphicsComponentList ( (testingState->getRenderQueue() )->getGraphicsComponentList());
	gbufferRenderPass->addRenderQueueRequestFlag(new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));

	testingState->getRenderLoop()->addRenderPass( gbufferRenderPass);

	//-0.5 : render GBuffer compositing for fun
	CompositingPass* gbufferCompositingRenderPass = new CompositingPass(gbuffer_compositing_shader, gbuffer_compositing_fbo);
	gbufferCompositingRenderPass->setColorMap(gbuffer_fbo->getColorTextureHandle());
	gbufferCompositingRenderPass->setPositionMap(gbuffer_fbo->getPositionTextureHandle());
	gbufferCompositingRenderPass->setNormalMap(gbuffer_fbo->getNormalTextureHandle());
	testingState->getRenderLoop()->addRenderPass( gbufferCompositingRenderPass );

	// 1: render Reflection Map
	// use reflection_shader, render into framebuffer_water_reflection framebuffer object
	RenderPass* reflectionMapRenderPass = new RenderPass(reflection_shader, UnderwaterScene::framebuffer_water_reflection);
	reflectionMapRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	reflectionMapRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList());			// start with all scene objects as render candidates
	reflectionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	// render if not part of waterplaneobject
	reflectionMapRenderPass->attachListenerOnActivation( setClearColor );// set clear color on activation, before bits are cleared
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	 // upload fog color
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );  // upload fog begin distance
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );    // upload fog end distance
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNorm );  // upload clipping plane normal
	reflectionMapRenderPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before rendering
	reflectionMapRenderPass->attachListenerOnDeactivation( new SetCameraListener( testingState->getCamera() ));		 // set camera to regular camera after rendering (undo above)

	testingState->getRenderLoop()->addRenderPass(	reflectionMapRenderPass );	//add ReflectionMap RenderPass
	
	// 2: render Refraction Map
	// use refraction_shader, render into framebuffer_water_refraction
	RenderPass* refractionMapRenderPass = new RenderPass(refraction_shader, UnderwaterScene::framebuffer_water_refraction);
	refractionMapRenderPass->setClearColorBufferBit(true); // clear color buffer on every frame
	refractionMapRenderPass->setInitialGraphicsComponentList ( (testingState->getRenderQueue() )->getGraphicsComponentList()); 			// start with all scene objects as render candidates
	refractionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	// render if not part of waterplaneobject
	refractionMapRenderPass->attachListenerOnActivation( setClearColorInv );//set clear color on activation, before bits are cleared
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniLightPos  );	//upload custom uniforms
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogColorInv  );	//upload fog color
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogBeginInv  );	//upload fog begin distance
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogEndInv    );	//upload fog end distance
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint );	//upload clipping plane support point
	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNormInv  );	//upload clipping plane normal
	
	testingState->getRenderLoop()->addRenderPass (refractionMapRenderPass);		//add RefractionMap RenderPass
	
	// 3: render Godrays into FBO
	// use godRay_Shader, render into framebuffer_water_god_rays Framebuffer Object
	RenderPass* godraysRenderPass = new RenderPass( godRay_shader, UnderwaterScene::framebuffer_water_god_rays );
	godraysRenderPass->setClearColorBufferBit(true);
	godraysRenderPass->setInitialGraphicsComponentList( testingState->getRenderQueue()->getGraphicsComponentList()); // start with all scene objects as render candidates
	// dont add any renderqueuerequest flags since all scene objects shall be rendered
	godraysRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);	// upload caustics texture used for god ray sampling
	godraysRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
	godraysRenderPass->attachListenerOnPostUniformUpload( uniCamPos );			// upload cam world position

	testingState->getRenderLoop()->addRenderPass( godraysRenderPass );			//add God Rays Render Pass

	// 4: render regular Scene
	// use underwater_shader, render into preCompositingScene Framebuffer Object
	RenderPass* regularSceneRenderPass = new RenderPass( underwater_shader, preCompositingScene );
	regularSceneRenderPass->setClearColorBufferBit(true);	//clear color buffer on every frame
	regularSceneRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList()); // start with all scene objects as render candidates
	regularSceneRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	//render if not part of waterplaneobject
	regularSceneRenderPass->attachListenerOnActivation( setClearColor2 ); // set clear color on activation, before bits are cleared
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	  // upload light position
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	  // upload fog color
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );	  // upload fog begin distance
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );  	  // upload fog end distance
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex ); // upload caustics texture
	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );   // upload sun view perspecitve matrix

	testingState->getRenderLoop()->addRenderPass( regularSceneRenderPass );		//add regular Scene Render pass
	
	// 5: render Water Surface with Reflection Map and RefractionMap
	// use water_shader, render into preCompositingScene Framebuffer Object
	RenderPass* waterRenderPass = new RenderPass( water_shader, preCompositingScene );
	waterRenderPass->setClearColorBufferBit(false);	// do NOT clear Color buffer bit, since it has already been partially filled by the preceding render pass
	waterRenderPass->setClearDepthBufferBit(false); // do NOT clear Depth buffer bit, since it has already been filled by the preceding render pass
	waterRenderPass->addInitialGraphicsComponent ( UnderwaterScene::scene_waterPlaneObject );	// set only the water plane object as render candidate
	waterRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	// upload light position
	waterRenderPass->attachListenerOnPostUniformUpload( uniReflMatr );	// upload reflective view matrix
	waterRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	// upload fog color
	waterRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );	// upload fog begin distancce
	waterRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );	// upload fog end distance
	waterRenderPass->attachListenerOnPostUniformUpload( uniReflText ); // upload reflection map
	waterRenderPass->attachListenerOnPostUniformUpload( uniRefrText ); // upload refraction map

	testingState->getRenderLoop()->addRenderPass( waterRenderPass);				//add Water Render Pass

	// 6: render Particles in the water
	// use particles_shader, use framebuffer_water_particles Framebuffer object as render target, use water_particles as particle system, use quad as vao
	ParticlesRenderPass* particlesRenderPass = new ParticlesRenderPass(particles_shader, UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);
	// do not use any graphics components or render flags, since this is a custom render pass for particle systems which doesn't use either
	particlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
	particlesRenderPass->setUseDepthTest(false);	// disable depth testing
	particlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
	particlesRenderPass->attachListenerOnActivation(new SetClearColorListener(0.0f,0.0f,0.0f,0.0f));	// set clear color to transparent
	particlesRenderPass->attachListenerOnPostUniformUpload( uniPartText);	// upload Particles Texture
	particlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value

	testingState->getRenderLoop()->addRenderPass(particlesRenderPass);			//add particles render pass

	// 7: Compositing
	// use a MixTexturesRenderPass to perform a compositing pass of three frame buffer textures, keep in mind that MixTexturesRenderPass is designed for two textures, therefore another custom uniform texture upload is necessary
	// use composition_shader, render to window (fbo = 0), use preCompositingScene-Texture as base texture, use framebuffer_water_god_rays as texture to mix with
	MixTexturesRenderPass* compositingRenderPass = new MixTexturesRenderPass(composition_shader, 0, preCompositingScene->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
	// MixTexturesRenderPasses do not need any RenderQueueRequestFlags or GraphicsComponent, since only a ScreenFillingTriangle will be rendered by default
	compositingRenderPass->setBaseTextureUniformName( "uniformPreCompositionMap" );	// set custom uniform name for base texture
	compositingRenderPass->setMixTextureUniformName(  "uniformGodRayMap" );			// set custom uniform name for mix texture
//		// // alternatively : ignore hard coded texture upload functionality and use listeners instead
//		 compositingRenderPass->attachListenerOnPostUniformUpload( uniPreCompMap );
//		 compositingRenderPass->attachListenerOnPostUniformUpload( uniGodRayMap );
		
		// add a third texture as a listener
		compositingRenderPass->attachListenerOnPostUniformUpload(uniPartMap);

	testingState->getRenderLoop()->addRenderPass( compositingRenderPass );		// add compositing render Pass

	// tiny views
	MixTexturesRenderPass* renderTinyView = new MixTexturesRenderPass(simpleTex, 0, UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle());
	renderTinyView->setBaseTextureUniformName("diffuseTexture");
	renderTinyView->setViewPortY(500);
	renderTinyView->setViewPortX(0);

	renderTinyView->setViewPortWidth(100);
	renderTinyView->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView);

	MixTexturesRenderPass* renderTinyView2 = new MixTexturesRenderPass(simpleTex, 0, UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle());
	renderTinyView2->setBaseTextureUniformName("diffuseTexture");
	renderTinyView2->setViewPortY(500);

	renderTinyView2->setViewPortX(100);
	renderTinyView2->setViewPortWidth(100);
	renderTinyView2->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView2);

	// tiny views
	MixTexturesRenderPass* renderTinyView3= new MixTexturesRenderPass(simpleTex, 0, UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
	renderTinyView3->setBaseTextureUniformName("diffuseTexture");
	renderTinyView3->setViewPortY(500);
	renderTinyView3->setViewPortX(200);
	renderTinyView3->setViewPortWidth(100);
	renderTinyView3->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView3);

	MixTexturesRenderPass* renderTinyView4 = new MixTexturesRenderPass(simpleTex, 0, UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle());
	renderTinyView4->setBaseTextureUniformName("diffuseTexture");
	renderTinyView4->setViewPortY(500);
	renderTinyView4->setViewPortX(300);
	renderTinyView4->setViewPortWidth(100);
	renderTinyView4->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView4);

	MixTexturesRenderPass* renderTinyView5 = new MixTexturesRenderPass(simpleTex, 0, preCompositingScene->getPositionTextureHandle());
	renderTinyView5->setBaseTextureUniformName("diffuseTexture");
	renderTinyView5->setViewPortY(500);
	renderTinyView5->setViewPortX(400);
	renderTinyView5->setViewPortWidth(100);
	renderTinyView5->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView5);

	MixTexturesRenderPass* renderTinyView6 = new MixTexturesRenderPass(simpleTex, 0, preCompositingScene->getDepthBufferHandle());
	renderTinyView6->setBaseTextureUniformName("diffuseTexture");
	renderTinyView6->setViewPortY(500);
	renderTinyView6->setViewPortX(500);
	renderTinyView6->setViewPortWidth(100);
	renderTinyView6->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView6);

	MixTexturesRenderPass* renderTinyView7 = new MixTexturesRenderPass(simpleTex, 0, gbuffer_fbo->getNormalTextureHandle());
	renderTinyView7->setBaseTextureUniformName("diffuseTexture");
	renderTinyView7->setViewPortY(500);
	renderTinyView7->setViewPortX(600);
	renderTinyView7->setViewPortWidth(100);
	renderTinyView7->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView7);

	MixTexturesRenderPass* renderTinyView8 = new MixTexturesRenderPass(simpleTex, 0, gbuffer_compositing_fbo->getPositionTextureHandle());
	renderTinyView8->setBaseTextureUniformName("diffuseTexture");
	renderTinyView8->setViewPortY(500);
	renderTinyView8->setViewPortX(700);
	renderTinyView8->setViewPortWidth(100);
	renderTinyView8->setViewPortHeight(100);
	testingState->getRenderLoop()->addRenderPass(renderTinyView8);
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
