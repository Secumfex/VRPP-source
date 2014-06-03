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

std::vector< RenderPass* > debugViews;

/**
 * Create a tiny view at the top of the window
 * @param shader to be used ( should be simpleTex )
 * @param state to use to add the renderpass to
 * @param imageHandle of texture to be presented
 */
void addDebugView(Shader* shader, ApplicationState* state, GLuint imageHandle)
{
	int x = 0;
	int y = 500;

	// max debug views : 8
	if ( debugViews.size() < 8)
	{
		x = debugViews.size() * 100;
	}
	else{
		std::cout << "Maximum amount of debug views reached." << std::endl;
		return;
	}

	MixTexturesRenderPass* renderTinyView = new MixTexturesRenderPass(shader, 0, imageHandle);
	renderTinyView->setBaseTextureUniformName("diffuseTexture");
	renderTinyView->setViewPortY(y);
	renderTinyView->setViewPortX(x);
	renderTinyView->setViewPortWidth(100);
	renderTinyView->setViewPortHeight(100);
	state->getRenderLoop()->addRenderPass(renderTinyView);

	debugViews.push_back(renderTinyView);
}

void configureRendering(){

	Shader *simpleTex			= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH  "/Underwater_Visuals_Test/simpleTexture.frag");

	Shader* gbuffer_shader		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/GBuffer.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/GBuffer_normalTexture.frag");
	Shader* gbuffer_caustics_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/gbuffer_caustics.frag");
	Shader* gbuffer_compositing_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/gbuffer_compositing.frag");
	Shader* gbuffer_culling_shader	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/GBuffer_culling.vert", SHADERS_PATH "/Underwater_Visuals_Test/GBuffer_culling.frag");
	Shader* gbuffer_particle_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/particles.vert" , SHADERS_PATH "/Underwater_Visuals_Test/particles.frag");
	Shader* gbuffer_god_rays_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert" , SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_godrays.frag");
	Shader* gbuffer_water_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_water.vert", SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_water.frag");

	Shader* add_shader 			= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH "/Underwater_Visuals_Test/add.frag ");
	Shader* overlay_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH "/Underwater_Visuals_Test/overlay.frag ");

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

	// Image to be used to assemble the final image
	FrameBufferObject* finalImage = new FrameBufferObject(800, 600);
	finalImage->bindFBO();
	finalImage->createPositionTexture();
	finalImage->makeDrawBuffers();
	finalImage->unbindFBO();

	Listener* uniCamPos		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", testingState->getCamera()->getPositionPointer(), 		"uniformCameraWorldPos");
	Listener* uniClipPoint 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", glm::vec3(0.0, UnderwaterScene::water_height, 0.0), 	"uniformClippingPoint");
	Listener* uniClipNorm	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal , 				"uniformClippingNormal");
	Listener* uniClipNormInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal_inverse , 		"uniformClippingNormal");
	Listener* uniFogColor 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, 							"uniformFogColor");
	Listener* uniFogColorInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color_inverse, 					"uniformFogColor");
	Listener* uniLightPos 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, 						"uniformLightPosition");
	Listener* uniSunDir		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunLightDirection,					"uniformSunDirection");

	Listener* uniRefrText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "uniformRefractionMap", 	UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle());
	Listener* uniReflText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 11, "uniformReflectionMap", 	UnderwaterScene::framebuffer_water_reflection_compositing->getPositionTextureHandle());
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

/******************** GBuffer Alternative Rendering ************************/
	
	// 1.1: render scene into GBuffer
	GBufferRenderPass* gbufferRenderPass = new GBufferRenderPass(gbuffer_shader, gbuffer_fbo);
	gbufferRenderPass->setClearColorBufferBit(true);
	gbufferRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList( ) );
	gbufferRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true ) );

	testingState->getRenderLoop()->addRenderPass( gbufferRenderPass);

	// 1.2: light GBuffer scene
	CompositingPass* gbufferCompositingRenderPass = new CompositingPass(gbuffer_compositing_shader, gbuffer_compositing_fbo);
	gbufferCompositingRenderPass->setColorMap(    gbuffer_fbo->getColorTextureHandle());
	gbufferCompositingRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle());
	gbufferCompositingRenderPass->setNormalMap(   gbuffer_fbo->getNormalTextureHandle());
	
	testingState->getRenderLoop()->addRenderPass( gbufferCompositingRenderPass );
	
	/************* WATER ***********/

	// 2.1. render reflected View into seperate GBuffer FBO
	GBufferRenderPass* gbufferReflectionMapRenderPass = new GBufferRenderPass(gbuffer_culling_shader, UnderwaterScene::framebuffer_water_reflection_gbuffer);
	gbufferReflectionMapRenderPass->setClearColorBufferBit(true);
	gbufferReflectionMapRenderPass->setInitialGraphicsComponentList( testingState->getRenderQueue()->getGraphicsComponentList() );
	gbufferReflectionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject( UnderwaterScene::scene_waterPlaneObject, true ) ); // render everything but the water plane object
	gbufferReflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
	gbufferReflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNorm );  // upload clipping plane normal

	gbufferReflectionMapRenderPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before rendering
	gbufferReflectionMapRenderPass->attachListenerOnDeactivation( new SetCameraListener( testingState->getCamera() ));		 // set camera to regular camera after rendering (undo above)

	testingState->getRenderLoop()->addRenderPass( gbufferReflectionMapRenderPass );

	// 2.2. render refracted View into seperate GBuffer FBO
	GBufferRenderPass* gbufferRefractionMapRenderPass = new GBufferRenderPass(gbuffer_culling_shader, UnderwaterScene::framebuffer_water_refraction_gbuffer);
	gbufferRefractionMapRenderPass->setClearColorBufferBit(true);
	gbufferRefractionMapRenderPass->setInitialGraphicsComponentList( testingState->getRenderQueue()->getGraphicsComponentList() );	// render everything but the water plane object
	gbufferRefractionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject( UnderwaterScene::scene_waterPlaneObject, true ) );
	gbufferRefractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
	gbufferRefractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNormInv );  // upload clipping plane normal

	testingState->getRenderLoop()->addRenderPass( gbufferRefractionMapRenderPass );

	// 2.3. light gbuffer reflection map
	CompositingPass* gbufferReflectionMapCompositingPass = new CompositingPass(gbuffer_compositing_shader, UnderwaterScene::framebuffer_water_reflection_compositing);
	gbufferReflectionMapCompositingPass->setColorMap( 	UnderwaterScene::framebuffer_water_reflection_gbuffer->getColorTextureHandle());
	gbufferReflectionMapCompositingPass->setNormalMap( 	UnderwaterScene::framebuffer_water_reflection_gbuffer->getNormalTextureHandle());
	gbufferReflectionMapCompositingPass->setPositionMap(UnderwaterScene::framebuffer_water_reflection_gbuffer->getPositionTextureHandle());

//	gbufferReflectionMapCompositingPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before composing
//	gbufferReflectionMapCompositingPass->attachListenerOnDeactivation( new SetCameraListener( testingState->getCamera() ));		 // set camera to regular camera after composing (undo above)

	testingState->getRenderLoop()->addRenderPass( gbufferReflectionMapCompositingPass);

	// 2.4. light gbuffer refraction map
	CompositingPass* gbufferRefractionMapCompositingPass = new CompositingPass(gbuffer_compositing_shader, UnderwaterScene::framebuffer_water_refraction_compositing);
	gbufferRefractionMapCompositingPass->setColorMap( 	UnderwaterScene::framebuffer_water_refraction_gbuffer->getColorTextureHandle());
	gbufferRefractionMapCompositingPass->setNormalMap( 	UnderwaterScene::framebuffer_water_refraction_gbuffer->getNormalTextureHandle());
	gbufferRefractionMapCompositingPass->setPositionMap(UnderwaterScene::framebuffer_water_refraction_gbuffer->getPositionTextureHandle());

	testingState->getRenderLoop()->addRenderPass( gbufferRefractionMapCompositingPass);


	// 2.5. render waterobject into seperate Gbuffer FBO and use
	RenderPass* gbufferWaterRenderPass = new RenderPass(gbuffer_water_shader, UnderwaterScene::framebuffer_water_water_object);

	gbufferWaterRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_waterPlaneObject);	// render only water plane object
	gbufferWaterRenderPass->setClearColorBufferBit(true);	// clear color
	gbufferWaterRenderPass->setClearDepthBufferBit(true);
	gbufferWaterRenderPass->setUseDepthTest(true);
	gbufferWaterRenderPass->setCustomClearColor(glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f) );	// clear with 0 alpha to use for overlay later

	gbufferWaterRenderPass->attachListenerOnPostUniformUpload( new UploadUniformTextureListener("", 7, "uniformDepthMap", gbuffer_fbo->getDepthBufferHandle( ) ) );	// use depth buffer of gbuffer
	gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniReflText );	// reflectionmap
	gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniRefrText );	// refractionmap
	gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	// upload light position
	gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniReflMatr );	// upload reflective view matrix

	testingState->getRenderLoop()->addRenderPass( gbufferWaterRenderPass );

	/******** OTHER EFFECTS ***********/

	// 3. render god_rays with gbuffer information ( depth ) into seperate FBO
	CompositingPass* gbufferGodraysRenderPass = new CompositingPass(gbuffer_god_rays_shader, UnderwaterScene::framebuffer_water_god_rays);	// compositing
	gbufferGodraysRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle( ) );	// use gbuffer position information for depth testing

	//TODO check the water object depth map aswell
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCamPos );			// upload cam world position

	testingState->getRenderLoop()->addRenderPass(gbufferGodraysRenderPass);

	// 4. render particles into a seperate fbo, use depth information of gbuffer as depth map
	ParticlesRenderPass* gbufferParticlesRenderPass = new ParticlesRenderPass(gbuffer_particle_shader, UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);

	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( new UploadUniformTextureListener("", 7, "uniformDepthMap", gbuffer_fbo->getDepthBufferHandle( ) ) );

	gbufferParticlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
	gbufferParticlesRenderPass->setUseDepthTest(false);	// disable depth testing
	gbufferParticlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
	gbufferParticlesRenderPass->setCustomClearColor( glm::vec4 ( 0.0f, 0.0f, 0.0f, 0.0f) );// set clear color to transparent
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniPartText);	// upload Particles Texture
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value

	testingState->getRenderLoop()->addRenderPass( gbufferParticlesRenderPass );

	// 5. render caustics with gbuffer information ( depth ) into seperate FBO
	CompositingPass* gbufferCausticsRenderPass = new CompositingPass( gbuffer_caustics_shader, UnderwaterScene::framebuffer_water_caustics);
	gbufferCausticsRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle( ) ); // use position texture handle as depth information
	gbufferCausticsRenderPass->setNormalMap( gbuffer_fbo->getNormalTextureHandle() );	// use normal texture

	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunDir );	// upload sun light direction

	testingState->getRenderLoop()->addRenderPass( gbufferCausticsRenderPass );

	/******** COMPOSITING ***********/

	// 6.0.1 : overlay Water ontop of scene fbo
	MixTexturesRenderPass* overlayWaterObject = new MixTexturesRenderPass( overlay_shader, finalImage, gbuffer_compositing_fbo->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_water_object->getPositionTextureHandle());
	overlayWaterObject->setMixTextureUniformName("uniformOverlayTexture");
	testingState->getRenderLoop()->addRenderPass(overlayWaterObject);

	// 6.1. : overlay particles ontop of scene fbo
	MixTexturesRenderPass* overlayParticles = new MixTexturesRenderPass( overlay_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );
	overlayParticles->setMixTextureUniformName("uniformOverlayTexture");
	testingState->getRenderLoop()->addRenderPass(overlayParticles);

	// 6.2. : add caustics on top of scene fbo
	MixTexturesRenderPass* addCaustics = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );
	addCaustics->setMixTextureUniformName("uniformAddTexture");
	testingState->getRenderLoop()->addRenderPass(addCaustics);


	// 6.3. : add god rays ontop of scene fbo
	MixTexturesRenderPass* addGodRays = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
	addGodRays->setMixTextureUniformName("uniformAddTexture");
	testingState->getRenderLoop()->addRenderPass(addGodRays);

	/********* Present Final Image ***************/
	TextureRenderPass* presentFinalImage = new TextureRenderPass(simpleTex,0,finalImage->getPositionTextureHandle());
	presentFinalImage->setTextureUniformName("diffuseTexture");

	testingState->getRenderLoop()->addRenderPass(presentFinalImage);

/******************** Debug Views ************************/
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, preCompositingScene->getPositionTextureHandle() );

//	addDebugView(simpleTex, testingState, gbuffer_fbo->getDepthBufferHandle() );										// Depth Texture
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );	// Particles
//	addDebugView(simpleTex, testingState, gbuffer_fbo->getNormalTextureHandle() );										// Normals
//	addDebugView(simpleTex, testingState, gbuffer_compositing_fbo->getPositionTextureHandle() );						// GBuffer Compositing

//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );	// God Rays
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );	// Caustics

//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection_gbuffer->getPositionTextureHandle()); // Refraction Position
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection_gbuffer->getNormalTextureHandle()); // Refraction Normal
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection_gbuffer->getColorTextureHandle()); // Refraction Color

//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction_gbuffer->getPositionTextureHandle()); // Refraction Position
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction_gbuffer->getNormalTextureHandle()); // Refraction Normal
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction_gbuffer->getColorTextureHandle()); // Refraction Color


	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection_compositing->getPositionTextureHandle());	// Reflection Compositing
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle());	// Refraction Compositing
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_water_object->getPositionTextureHandle());	// Water Object

//	addDebugView(simpleTex, testingState, finalImage->getPositionTextureHandle() );										// Final Image

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
