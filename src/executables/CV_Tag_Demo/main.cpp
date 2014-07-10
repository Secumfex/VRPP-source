#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"	// TODO use placeholder listeners header for missing listeners and stuff

#include "Physics/PhysicWorldSimulationListener.h"

#include "Tools/ShaderFactory.h"

// include features
#include "FeatureUnderwaterScene.h"
#include "FeatureTreasureChest.h"
#include "FeatureOculus.h"
#include "IO/OculusListeners.h"
#include "FishBoidFeature.h"
#include "FeatureAnimation.h"

		// TODO etc.

/****************** GLOBAL VARIABLES ****************************/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

OculusCamera* 	reflectedOculusCamera;

/*****************  UTILITY *************************************/
// debug views, if any
std::vector< RenderPass* > debugViews;

/**
 * Create a tiny view at the top of the window
 * should be used as very last renderpasses to write ontop of screen
 *
 * @param shader to be used ( should be simpleTex )
 * @param state to use to add the renderpass to
 * @param imageHandle of texture to be presented
 */
void addDebugView(Shader* shader, ApplicationState* state, GLuint imageHandle)
{
	int x = 0;
	int y = IOManager::getInstance()->getHeight() - 200 ;

	// max debug views : 8
	if ( debugViews.size() < IOManager::getInstance()->getWidth() / 200)
	{
		x = debugViews.size() * 200;
	}
	else{
		std::cout << "Maximum amount of debug views reached." << std::endl;
		return;
	}

	MixTexturesRenderPass* renderTinyView = new MixTexturesRenderPass(shader, 0, imageHandle);
	renderTinyView->setBaseTextureUniformName("diffuseTexture");
	renderTinyView->setViewPortY(y);
	renderTinyView->setViewPortX(x);
	renderTinyView->setViewPortWidth(200);
	renderTinyView->setViewPortHeight(200);
	state->getRenderLoop()->addRenderPass(renderTinyView);

	debugViews.push_back(renderTinyView);
}

/*****************  CONFIGURATION    ****************************/


void configureTestingApplication(){
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

}

void configureVirtualObjects(){
	/* creation and customization of Virtual Objects */
	/* use testingState->createVirtualObject() to create a Virtual Object */

	// some fine tuning of frame buffer sizes
	UnderwaterScene::framebuffer_water_refraction_scalefactor = 0.5f;
	UnderwaterScene::framebuffer_water_reflection_scalefactor = 0.5f;
	UnderwaterScene::framebuffer_water_caustics_scalefactor = 0.5f;

	// already create a reflected cam to be used as default reflected camera during object creation
	reflectedOculusCamera = new OculusCamera( OculusFeature::oculus );
	UnderwaterScene::reflectedCamera = reflectedOculusCamera;

	// alle Objektinstanzen & framebuffer der UnterwasserSzene erstellen
	UnderwaterScene::createScene( testingState );

	//TODO Statische Szene erstellen
	//TODO Andere Objekte ( Kiste, Fischschwarm, Seetang etc. ) erstellen

}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */

	testingState->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener( IOManager::getInstance()->getDeltaTimePointer() ) );

	//create an invisible ground plane
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
   	 btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);

	btRigidBody* camBody = OculusFeature::oculusCam->getRigidBody();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);
	OculusFeature::oculusCam->setPosition(0.0f,7.0f,5.0f);

	// TODO Kamera bei y > 10.0f runterziehen
}

void configureInputHandler(){
	/* customization of input handling */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

	testingInputHandler->attachListenerOnKeyPress(new PrintValueListener( IOManager::getInstance()->getDeltaTimePointer(), "d_t : "), GLFW_KEY_T );

	// TODO Tasten zum resetten etc.
}

void configureRendering(){
	// Oculus wurde bereits initialisiert --> fenster gr��e ist bekannt

	// alle Shader erstellen, die sp�ter ben�tigt werden
	UnderwaterScene::createShaders( testingState );

	// Testweise: alle Renderpasses erstellen und direkt in Renderloop einf�gen
	UnderwaterScene:: createRenderPasses( testingState, true);

	// create a renderpass for boids, rendering into default gbuffer right after under water scene gbuffer rendering
	RenderPass* gbufferBoidRenderPass = FishBoidFeature::createGBufferBoidRenderPass( UnderwaterScene::framebuffer_gbuffer_default );
	if ( !testingState->getRenderLoop()->addRenderPassAfter( gbufferBoidRenderPass, UnderwaterScene::gbufferRenderPass ) )
	{
		std::cout << "ERROR : could not insert Renderpass at the specified position" << std::endl;
	}


	// einer renderpass fuer bone_animation #copypasta_von_arend
	RenderPass* gbufferAnimationPass = AnimationFeature::createAnimationRenderPass( UnderwaterScene::framebuffer_gbuffer_default );
	if ( !testingState->getRenderLoop()->addRenderPassAfter( gbufferAnimationPass, UnderwaterScene::gbufferRenderPass ) )
	{
		std::cout << "ERROR : could not insert Renderpass at the specified position" << std::endl;
	}

	UnderwaterScene::gbufferShadowRenderPass->addInitialGraphicsComponent( FishBoidFeature::fishes );



	// TODO Alle anderen Renderpasses erstellen
	// TODO Richtige Reihenfolge und verkn�pfungen einstellen

	// make stereo renderpasses whenever geometry is rendered
	std::cout << " Reconfiguring RenderPasses to Stereo Rendering" << std::endl;
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferSunSkyRenderPass, 				OculusFeature::oculus, OculusFeature::oculusCam );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferRenderPass, 					OculusFeature::oculus, OculusFeature::oculusCam );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferReflectionMapSunSkyRenderPass, OculusFeature::oculus, reflectedOculusCamera );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferReflectionMapRenderPass, 		OculusFeature::oculus, reflectedOculusCamera );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferRefractionMapSunSkyRenderPass, OculusFeature::oculus, OculusFeature::oculusCam );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferRefractionMapRenderPass, 		OculusFeature::oculus, OculusFeature::oculusCam );
	OculusFeature::makeStereoRenderPass( UnderwaterScene::gbufferParticlesRenderPass, 			OculusFeature::oculus, OculusFeature::oculusCam );
	OculusFeature::makeStereoRenderPass( AnimationFeature::gbufferAnimationRenderPass, 			OculusFeature::oculus, OculusFeature::oculusCam );

	OculusFeature::makeStereoRenderPass( FishBoidFeature::gbufferBoidRenderPass, 				OculusFeature::oculus, OculusFeature::oculusCam );

	std::pair<
			OculusFeature::StereoRenderPassActivateRenderEyeSettingsListener *,
			OculusFeature::StereoRenderPassActivateRenderEyeSettingsListener *> listeners =
			OculusFeature::makeStereoRenderPass(
					UnderwaterScene::gbufferWaterRenderPass,
					OculusFeature::oculus, OculusFeature::oculusCam);

	listeners.first->attachListenerOnEyeSettingsActivation( new SetOculusCameraEyeListener(  reflectedOculusCamera, OVR::Util::Render::StereoEye_Left ) );
	listeners.second->attachListenerOnEyeSettingsActivation( new SetOculusCameraEyeListener( reflectedOculusCamera, OVR::Util::Render::StereoEye_Right ) );


	// use a different shader for water object render pass, due to reflection map hickups
	UnderwaterScene::gbufferWaterRenderPass->setShader( new Shader ( SHADERS_PATH "/CV_Tag_Demo/gbuffer_water_stereo.vert", SHADERS_PATH "/CV_Tag_Demo/gbuffer_water_stereo.frag") );

	// also add a Listener that updates the reflected camera view

	// apply oculus post processing on final image
	std::cout << " Setting Stereo Post Processing effect on final image" << std::endl;
	OculusFeature::oculus->setRenderBuffer( UnderwaterScene:: finalImage );
	testingState->getRenderLoop()->addRenderPass( OculusFeature::oculusPostProcessing );

	// some debug views
	addDebugView(UnderwaterScene::simpleTex, testingState, UnderwaterScene::framebuffer_shadow->getDepthBufferHandle() );
}

void configureOtherStuff(){
	/* customization for other stuff */

}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("TESTING FRAMEWORK");
	testingApp 			->	addState(testingState);

	testingApp->initialize();	// to ensure IO manager and RenderManager are aware of all things necessary

	testingInputHandler = testingState->getIOHandler();


	/**
	 * 	Initialisierung der einzelnen Features, bzw Objektinstanzen die so gebraucht werden
	 *
	 * 	Reihenfolge platzhaltend willk�rlich
	 */


	OculusFeature:: initializeAndConfigureOculus( testingState );

	// TODO TreasureChestFeature::createObjects( testingState);

	// TODO FloraFeature::createObjects( testingState);

	// TODO HUDFeature::createObjects( testingState);

	// TODO AkropolisFeature::createObjects( testingState );

	// TODO PostProcessingFeature::createObjects( testingState );

	// TODO OculusFeature::createObjects( testingState );

	// TODO KinectFeature::createObjects( testingState );

	// create boids
	FishBoidFeature::createObjects( testingState );

	// create animationloop
	AnimationFeature::createObjects( testingState );

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();

	
	configureInputHandler();
	configureRendering();
	configurePhysics();
	configureOtherStuff();
}

int main() {

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
