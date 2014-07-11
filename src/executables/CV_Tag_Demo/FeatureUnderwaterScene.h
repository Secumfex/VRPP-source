#ifndef FEATUREUNDERWATERSCENE_H
#define FEATUREUNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "IO/IOManager.h"

#include "PlaceHolderListeners.h"

#include "UnderwaterSceneParticleSystem.h"

namespace UnderwaterScene{
/**
 * PARAMETERS
 */

	bool is_underwater;

	float water_height = 10.0f;

	float fog_begin = 5.0f;
	float fog_end	= 15.0f;
	float fog_begin_inverse = 100.0f;
	float fog_end_inverse	= 10000.0f;

	float fog_begin_under_water = 3.0f;
	float fog_end_under_water = 50.0f;
	float fog_end_above_water = 190.0f;
	float fog_begin_above_water = 20.0f;

	int   particle_amount = 100;
	float particle_distance_max = 3.5f;

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.0f);
	glm::vec4 skycolor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 0.0f);
//	glm::vec3 fog_color(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);
	glm::vec3 fog_color(102.0f / 255.0f * 0.7f, 205.0f / 255.0f * 0.7f, 170.0f/ 255.0f * 0.7f);
	glm::vec3 fog_color_inverse(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f);
	glm::vec3 fog_color_above_water(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f);
	glm::vec3 fog_color_under_water(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);

	glm::vec3 reflectedCameraPosition(0.0f,0.0f,0.0f);

	glm::vec3 water_plane_normal( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_under_water( 0.0f, -1.0f, 0.0f );
	glm::vec3 water_plane_normal_above_water( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_inverse( 0.0f, -1.0f, 0.0f );
	glm::vec3 water_plane_normal_under_water_inverse( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_above_water_inverse( 0.0f, -1.0f, 0.0f );

	glm::vec3 lightPosition(1000.0f,1000.0f,0.0f);
	glm::vec3 sunLightDirection( -1.0f, -1.0f, 0.0f );	// light direction
	glm::mat4 sunView;
	glm::mat4 sunPerspective;
	glm::mat4 sunViewPerspective;
	glm::mat4 depthMVP;
	glm::mat4 depthBiasMVP;

	float framebuffer_water_refraction_scalefactor = 1.0f; // size in proportion to actual window size
	float framebuffer_water_reflection_scalefactor = 1.0f; // size in proportion to actual window size
	float framebuffer_water_godrays_scalefactor = 0.25f; // size in proportion to actual window size
	float framebuffer_water_particles_scalefactor = 0.5f; // size in proportion to actual window size
	float framebuffer_water_caustics_scalefactor = 1.0f; // size in proportion to actual window size


/**
 * OBJECTS
 */
	std::vector<VirtualObject* > scene_objects;	// contains all Underwaterscene objects
	std::vector<VirtualObject* > scene_objects_background;	// contains all Underwaterscene background objects ( sun, sky )

	VirtualObject* scene_groundObject;
	VirtualObject* scene_sky_dome;
	VirtualObject* scene_stoneObject1;
	VirtualObject* scene_sun_Object;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_wallObject2;
	VirtualObject* scene_waterPlaneObject;
	VirtualObject* scene_mountainObject1;
	VirtualObject* scene_Octopus;

/**
 * FRAMEBUFFERS
 */

	FrameBufferObject* framebuffer_water_reflection_gbuffer;
	FrameBufferObject* framebuffer_water_reflection_compositing;
	FrameBufferObject* framebuffer_water_refraction_gbuffer;
	FrameBufferObject* framebuffer_water_refraction_compositing;
	FrameBufferObject* framebuffer_water_god_rays;
	FrameBufferObject* framebuffer_water_particles;
	FrameBufferObject* framebuffer_sand_particles;
	FrameBufferObject* framebuffer_water_water_object;
	FrameBufferObject* framebuffer_water_caustics;
	FrameBufferObject* framebuffer_scene_sky_sun;
	FrameBufferObject* framebuffer_shadow;

	FrameBufferObject* framebuffer_gbuffer_default;
	FrameBufferObject* framebuffer_gbuffer_compositing_default;
	FrameBufferObject* finalImage;

/**
 * SHADERS
 */

Shader* simpleTex;
Shader* clearGBuffer;

Shader* gbuffer_shader;
Shader* gbuffer_caustics_shader;
Shader* gbuffer_compositing_shader;
Shader* gbuffer_compositing_shadeless_shader;
Shader* gbuffer_culling_shader;
Shader* gbuffer_fog;
Shader* gbuffer_god_rays_shader;
Shader* gbuffer_particle_shader;
Shader* gbuffer_sand_particle_shader;
Shader* gbuffer_water_shader;
Shader* gbuffer_shadow_shader;

Shader* add_shader;
Shader* overlay_shader;
Shader *combine_GBuffers;


/**
 * RENDERPASSES
 */

// Take note the renderpasses should be also added in this order to the renderloop
GBufferRenderPass* 			gbufferSunSkyRenderPass;
CompositingPass* 			gbufferCompositingSkySunRenderPass;
GBufferRenderPass* 			gbufferRenderPass;
RenderPass* 				gbufferShadowRenderPass;
CompositingPass* 			gbufferCompositingRenderPass;
GBufferRenderPass* 			gbufferReflectionMapSunSkyRenderPass;
CompositingPass* 			gbufferCompositingReflectionMapSkySunRenderPass;
GBufferRenderPass* 			gbufferReflectionMapRenderPass;
CompositingPass* 			gbufferReflectionMapCompositingPass;
GBufferRenderPass* 			gbufferRefractionMapSunSkyRenderPass;
CompositingPass* 			gbufferCompositingRefractionMapSkySunRenderPass;
GBufferRenderPass* 			gbufferRefractionMapRenderPass;
CompositingPass* 			gbufferRefractionMapCompositingPass;
ScreenFillingTriangleRenderPass* gbufferCombineGBuffersOfBackGroundAndForeGround;
CompositingPass* 			gbufferGodraysRenderPass;
ParticlesRenderPass* 		gbufferParticlesRenderPass;
ParticlesRenderPass*		gbufferSandParticlesRenderPass;
CompositingPass* 			gbufferCausticsRenderPass;
MixTexturesRenderPass* 		addCausticsRefraction;		// will not be added
ConditionalRenderPassProxy*	addCausticsRefractionProxy; // will be added instead
CompositingPass* 			overlayFogRefraction;
CompositingPass* 			overlayFogReflection;
MixTexturesRenderPass* 		addGodRaysRefraction;		// will not be added
ConditionalRenderPassProxy* addGodRaysRefractionProxy;  // will be added instead
MixTexturesRenderPass* 		overlayParticlesRefraction; // will not be added
MixTexturesRenderPass*      overlaySandParticlesRefraction;
ConditionalRenderPassProxy* overlayParticlesRefractionProxy;// will be added instead
ConditionalRenderPassProxy* overlaySandParticlesRefractionProxy;
RenderPass* 				gbufferWaterRenderPass;
MixTexturesRenderPass* 		overlayWaterObject;
MixTexturesRenderPass* 		addCaustics;				// will not be added
ConditionalRenderPassProxy*	addCausticsProxy;			// will be added instead
ScreenFillingTriangleRenderPass* combineWaterObjectWithGBuffer;
CompositingPass* 			addFog;
MixTexturesRenderPass* 		addGodRays;
ConditionalRenderPassProxy* addGodRaysProxy;
MixTexturesRenderPass* 		overlayParticles;			// will not be added
ConditionalRenderPassProxy* overlayParticlesProxy;		// will be added instead
MixTexturesRenderPass* 		overlaySandParticles;			
ConditionalRenderPassProxy* overlaySandParticlesProxy;		
TextureRenderPass* 			presentFinalImage;

/**
 * MISC
 */
	Camera* reflectedCamera = 0;

	Texture* causticsTexture;
	Texture* particlesTexture;
	Texture* sandParticlesTexture;

	ParticleSystem* water_particles;
	ParticleSystem* sand_particles;

	// Subject to be used to attach Listeners to entering or exiting the water
	UnderOrAboveWaterListener* scene_subject_under_above_water = 0;

	Listener* scene_listener_keep_offset_sun_reflection;
	Listener* scene_listener_keep_offset_sky_reflection;
	Listener* scene_listener_keep_offset_sun;
	Listener* scene_listener_keep_offset_sky;

	std::vector< std::pair <Listener*, Listener* > > scene_listeners_under_above_water;

	/**
	 * attaches a pair of listeners to scene_subject_under_above_water that will call
	 * either enterWater or exitWater when entering or exiting the water
	 * and add both as a pair to scene_listeners_under_above_water
	 *
	 * @param enterWater Listener to be called once when water is being entered
	 * @param exitWater  Listener to be called once when water is being exited
	 */
	static void addUnderOrAboveWaterListener( Listener* enterWater, Listener* exitWater, ApplicationState* target)
	{
		if ( scene_subject_under_above_water != 0 )
		{
			scene_subject_under_above_water->attachListenerOnEnterWater( enterWater );
			scene_subject_under_above_water->attachListenerOnExitWater(  exitWater  );
		}
		else
		{
			std::cout << "ERROR : scene_subject_under_above_water has not yet been initialized. Could not attach Listeners." << std::endl;
		}

		scene_listeners_under_above_water.push_back( std::pair<Listener*, Listener*> (enterWater, exitWater ) );
	}


	/**
	 * modify the scene and create all objects necessary for rendering the underwater scene
	 *
	 * - loads above / under water behaviour ( set of Listeners ) and attaches them to scene_subject_under_above_water
	 * - attaches scene_subject_under_above_water to target state
	 * - creates the objects and pushes them back to scene_virtual_objects
	 * - creates sun parameters ( -View, -Perspective, -ViewPerspective )
	 * - creates water_particles ParticleSystem and attaches update listener to target state
	 * - creates framebuffer objects in relation to window size
	 * - creates reflectedCamera from active Camera of target state
	 * - creates scene_listener_keep_offset for sun and sky objects and attaches them to target state
	 * @param target state to be modified
	 */
	static void createScene(ApplicationState* target){
		/******************* above or underneath water surface handling *****************/
		SetBoolValueListener* enterWater_0 = new SetBoolValueListener( &is_underwater, true );
		SetBoolValueListener*  exitWater_0 = new SetBoolValueListener( &is_underwater, false );

		SetClearColorListener* enterWater_1 = new SetClearColorListener( &watercolor );
		SetClearColorListener*  exitWater_1 = new SetClearColorListener( &skycolor );

		SetFloatValueListener* enterWater_2 = new SetFloatValueListener( &fog_begin, &fog_begin_under_water );
		SetFloatValueListener*  exitWater_2 = new SetFloatValueListener( &fog_begin, &fog_begin_above_water );
		SetFloatValueListener* enterWater_3 = new SetFloatValueListener( &fog_end,   &fog_end_under_water );
		SetFloatValueListener*  exitWater_3 = new SetFloatValueListener( &fog_end,   &fog_end_above_water );
		SetVec3ValuesListener* enterWater_4 = new SetVec3ValuesListener( &fog_color, &fog_color_under_water );
		SetVec3ValuesListener*  exitWater_4 = new SetVec3ValuesListener( &fog_color, &fog_color_above_water );
		SetVec3ValuesListener* enterWater_5 = new SetVec3ValuesListener( &water_plane_normal, &water_plane_normal_under_water );
		SetVec3ValuesListener*  exitWater_5 = new SetVec3ValuesListener( &water_plane_normal, &water_plane_normal_above_water );

		SetVec3ValuesListener* enterWater_6 = new SetVec3ValuesListener( &water_plane_normal_inverse, &water_plane_normal_under_water_inverse );
		SetVec3ValuesListener*  exitWater_6 = new SetVec3ValuesListener( &water_plane_normal_inverse, &water_plane_normal_above_water_inverse );
		SetFloatValueListener* enterWater_7 = new SetFloatValueListener( &fog_begin_inverse, &fog_begin_above_water );
		SetFloatValueListener*  exitWater_7 = new SetFloatValueListener( &fog_begin_inverse, &fog_begin_under_water );
		SetFloatValueListener* enterWater_8 = new SetFloatValueListener( &fog_end_inverse,   &fog_end_above_water );
		SetFloatValueListener*  exitWater_8 = new SetFloatValueListener( &fog_end_inverse,   &fog_end_under_water );
		SetVec3ValuesListener* enterWater_9 = new SetVec3ValuesListener( &fog_color_inverse, &fog_color_above_water );
		SetVec3ValuesListener*  exitWater_9 = new SetVec3ValuesListener( &fog_color_inverse, &fog_color_under_water );

		scene_subject_under_above_water = new UnderOrAboveWaterListener(target->getCamera(), &water_height);

		addUnderOrAboveWaterListener( enterWater_0, exitWater_0, target);
		addUnderOrAboveWaterListener( enterWater_1, exitWater_1, target);
		addUnderOrAboveWaterListener( enterWater_2, exitWater_2, target);
		addUnderOrAboveWaterListener( enterWater_3, exitWater_3, target);
		addUnderOrAboveWaterListener( enterWater_4, exitWater_4, target);
		addUnderOrAboveWaterListener( enterWater_5, exitWater_5, target);
		addUnderOrAboveWaterListener( enterWater_6, exitWater_6, target);
		addUnderOrAboveWaterListener( enterWater_7, exitWater_7, target);
		addUnderOrAboveWaterListener( enterWater_8, exitWater_8, target);
		addUnderOrAboveWaterListener( enterWater_9, exitWater_9, target);

		target->attachListenerOnBeginningProgramCycle( scene_subject_under_above_water );
		/*********************************************************************************/

		/******************* scene creation **********************************************/
		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", 		VirtualObjectFactory::OTHER, 0.0f, 4, true);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", 	VirtualObjectFactory::OTHER, 0.0f, 4, true);

		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", 		VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", 		VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_stoneObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_mountainObject1	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_mountain_01.dae", 	VirtualObjectFactory::OTHER, 0.0f, 4, true);
		scene_Octopus			= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_octopus.dae", 		VirtualObjectFactory::SPHERE, 0.0f, 1, true);

		scene_sky_dome			= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sky_dome.dae", 	VirtualObjectFactory::OTHER, 0.0f, 4, true);
		scene_sun_Object 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", 	VirtualObjectFactory::OTHER, 0.0f, 4, true);

		sunView = glm::lookAt( - sunLightDirection * 20.0f , glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) );
		sunPerspective = glm::ortho(-25.0f, 25.0f, -15.0f, 10.0f, 0.1f, 50.0f);
		sunViewPerspective 		= sunPerspective * sunView;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 glm::mat4 depthModelMatrix = glm::mat4(1.0);
		 depthMVP = sunPerspective * sunView * depthModelMatrix;

		 glm::mat4 biasMatrix(
				 0.5, 0.0, 0.0, 0.0,
				 0.0, 0.5, 0.0, 0.0,
				 0.0, 0.0, 0.5, 0.0,
				 0.5, 0.5, 0.5, 1.0);
		 depthBiasMVP = biasMatrix * depthMVP;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (scene_sun_Object->getGraphicsComponent().size() > 0){
				scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
		}

		scene_objects.push_back( scene_groundObject );
		scene_objects.push_back( scene_waterPlaneObject );
		scene_objects.push_back( scene_wallObject1 );
		scene_objects.push_back( scene_wallObject2 );
		scene_objects.push_back( scene_stoneObject1 );
		scene_objects.push_back( scene_mountainObject1 );
		scene_objects.push_back( scene_Octopus );

		scene_objects_background.push_back( scene_sun_Object );
		scene_objects_background.push_back( scene_sky_dome );
		/*********************************************************************************/

		/******************* framebuffer objects *****************************************/

		// window size to use for framebuffer creation
		int window_width = IOManager::getInstance()->getWidth();
		int window_height = IOManager::getInstance()->getHeight();

		framebuffer_water_reflection_compositing = new FrameBufferObject(window_width * framebuffer_water_reflection_scalefactor,window_height * framebuffer_water_reflection_scalefactor);
		framebuffer_water_reflection_compositing ->bindFBO();
		framebuffer_water_reflection_compositing ->createPositionTexture();
		framebuffer_water_reflection_compositing ->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_reflection_compositing ->unbindFBO();

		framebuffer_water_refraction_compositing = new FrameBufferObject(window_width * framebuffer_water_refraction_scalefactor,window_height * framebuffer_water_refraction_scalefactor);
		framebuffer_water_refraction_compositing ->bindFBO();
		framebuffer_water_refraction_compositing ->createPositionTexture();
		framebuffer_water_refraction_compositing ->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_refraction_compositing ->unbindFBO();

		framebuffer_water_reflection_gbuffer = new FrameBufferObject(window_width * framebuffer_water_reflection_scalefactor, window_height * framebuffer_water_reflection_scalefactor);
		framebuffer_water_reflection_gbuffer->bindFBO();
		framebuffer_water_reflection_gbuffer->createPositionTexture();
		framebuffer_water_reflection_gbuffer->createNormalTexture();
		framebuffer_water_reflection_gbuffer->createColorTexture();
		framebuffer_water_reflection_gbuffer->makeDrawBuffers();
		framebuffer_water_reflection_gbuffer->unbindFBO();

		framebuffer_water_refraction_gbuffer = new FrameBufferObject(window_width * framebuffer_water_refraction_scalefactor, window_height * framebuffer_water_refraction_scalefactor);
		framebuffer_water_refraction_gbuffer->bindFBO();
		framebuffer_water_refraction_gbuffer->createPositionTexture();
		framebuffer_water_refraction_gbuffer->createNormalTexture();
		framebuffer_water_refraction_gbuffer->createColorTexture();
		framebuffer_water_refraction_gbuffer->makeDrawBuffers();
		framebuffer_water_refraction_gbuffer->unbindFBO();

		framebuffer_water_god_rays = new FrameBufferObject(window_width * framebuffer_water_godrays_scalefactor , window_height * framebuffer_water_godrays_scalefactor );
		framebuffer_water_god_rays->bindFBO();
		framebuffer_water_god_rays->createPositionTexture();
		framebuffer_water_god_rays->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_god_rays->unbindFBO();

		framebuffer_water_particles = new FrameBufferObject(window_width *  framebuffer_water_particles_scalefactor, window_height *  framebuffer_water_particles_scalefactor);
		framebuffer_water_particles->bindFBO();
		framebuffer_water_particles->createPositionTexture();
		framebuffer_water_particles->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_particles->unbindFBO();

		framebuffer_sand_particles = new FrameBufferObject(window_width *  framebuffer_water_particles_scalefactor, window_height *  framebuffer_water_particles_scalefactor);
		framebuffer_sand_particles->bindFBO();
		framebuffer_sand_particles->createPositionTexture();
		framebuffer_sand_particles->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_sand_particles->unbindFBO();

		framebuffer_water_caustics = new FrameBufferObject(window_width * framebuffer_water_caustics_scalefactor, window_height * framebuffer_water_caustics_scalefactor);
		framebuffer_water_caustics->bindFBO();
		framebuffer_water_caustics->createPositionTexture();
		framebuffer_water_caustics->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_caustics->unbindFBO();

		framebuffer_water_water_object = new FrameBufferObject(window_width,window_height);
		framebuffer_water_water_object->bindFBO();
		framebuffer_water_water_object->createPositionTexture();
		framebuffer_water_water_object->createNormalTexture();
		framebuffer_water_water_object->createColorTexture();
		framebuffer_water_water_object->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_water_object->unbindFBO();

		framebuffer_scene_sky_sun	= new FrameBufferObject(window_width,window_height);
		framebuffer_scene_sky_sun->bindFBO();
		framebuffer_scene_sky_sun->createPositionTexture();
		framebuffer_scene_sky_sun->createNormalTexture();
		framebuffer_scene_sky_sun->createColorTexture();
		framebuffer_scene_sky_sun->makeDrawBuffers();
		framebuffer_scene_sky_sun->unbindFBO();

		framebuffer_shadow 	= new FrameBufferObject( 1024, 1024 );	// create a depth map
		framebuffer_shadow->createPositionTexture();
		framebuffer_shadow->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_shadow->unbindFBO();


		framebuffer_gbuffer_default = new FrameBufferObject(window_width,window_height);
		framebuffer_gbuffer_default->bindFBO();
		framebuffer_gbuffer_default->createPositionTexture();
		framebuffer_gbuffer_default->createNormalTexture();
		framebuffer_gbuffer_default->createColorTexture();
		framebuffer_gbuffer_default->makeDrawBuffers();
		framebuffer_gbuffer_default->unbindFBO();

		framebuffer_gbuffer_compositing_default = new FrameBufferObject(window_width,window_height);
		framebuffer_gbuffer_compositing_default->bindFBO();
		framebuffer_gbuffer_compositing_default->createPositionTexture();
		framebuffer_gbuffer_compositing_default->makeDrawBuffers();
		framebuffer_gbuffer_compositing_default->unbindFBO();

		// Image to be used to assemble the final image
		finalImage = new FrameBufferObject(window_width, window_height);
		finalImage->bindFBO();
		finalImage->createPositionTexture();
		finalImage->makeDrawBuffers();
		finalImage->unbindFBO();
		/*********************************************************************************/

		/******************* textures creation	  ****************************************/
		causticsTexture = new Texture( RESOURCES_PATH "/demo_scene/caustics.jpg" );
		particlesTexture= new Texture( RESOURCES_PATH "/demo_scene/particle.png");
		sandParticlesTexture = new Texture( RESOURCES_PATH "/demo_scene/sand_particle.png");
		/*********************************************************************************/

		/******************* default cam position ****************************************/
		Camera* cam =  target->getCamera();
		cam->setPosition(0.0f,7.0f,5.0f);
		cam->setPosition( cam->getPosition() + glm::vec3(0.0,1.5,0.0));

		// check whether there is already a camera instance to be used as reflected camera
		if ( reflectedCamera == 0 )
		{
			reflectedCamera = new Camera();
		}

		reflectedCamera->setTopDown( true );
		target->attachListenerOnBeginningProgramCycle(new UpdateReflectedCameraPositionListener(cam, reflectedCamera, &water_height));
		/*********************************************************************************/

		/******************* offset listeners for sky and sun ****************************/
		glm::vec3 offset = glm::normalize(sunLightDirection) * -32.5f;
		scene_listener_keep_offset_sky = new KeepOffsetListener( scene_sky_dome, target->getCamera()->getPositionPointer(), new glm::vec3( 0.0f, 0.0f, 0.0f));
		scene_listener_keep_offset_sun = new KeepOffsetListener(scene_sun_Object, target->getCamera()->getPositionPointer(), new glm::vec3( offset ) );

		scene_listener_keep_offset_sun_reflection = new KeepOffsetListener( scene_sky_dome, reflectedCamera->getPositionPointer(), new glm::vec3( 0.0f, 0.0f, 0.0f));
		scene_listener_keep_offset_sky_reflection = new KeepOffsetListener( scene_sun_Object, reflectedCamera->getPositionPointer(), new glm::vec3( offset ) );
		/*********************************************************************************/

		/******************* particle System objects *****************************************/
		water_particles = new ParticleSystem(target->getCamera()->getPositionPointer(), particle_distance_max);
		water_particles->setParticleAmount(particle_amount);
		target->attachListenerOnBeginningProgramCycle(new UpdateParticleSystemListener(water_particles, IOManager::getInstance()->getDeltaTimePointer()));
		/*********************************************************************************/

		/*******************sand particle System objects *****************************************/
		sand_particles = new ParticleSystem(target->getCamera()->getPositionPointer(), particle_distance_max);
		sand_particles->setParticleAmount(particle_amount*1.5);
		target->attachListenerOnBeginningProgramCycle(new UpdateParticleSystemListener(sand_particles, IOManager::getInstance()->getDeltaTimePointer()));
		/*********************************************************************************/
	}

	/**
	 * creates all shader instances used for rendering this scene
	 * - MUST be called before createRenderPasses()
	 * @param target
	 */
	static void createShaders( ApplicationState* target )
	{
	simpleTex = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/simpleTexture.frag");

	clearGBuffer = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/clearGBuffer.frag");

	gbuffer_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/GBuffer.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/GBuffer_normalTexture.frag");

	gbuffer_caustics_shader = new Shader(
			SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_caustics.frag");

	gbuffer_compositing_shader = new Shader(
			SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_compositing.frag");

	gbuffer_compositing_shadeless_shader =
			new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert",
					SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_compositing_shadeless.frag");

	gbuffer_culling_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/GBuffer_culling.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/GBuffer_culling.frag");

	gbuffer_fog = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_fog.frag");

	gbuffer_god_rays_shader = new Shader(
			SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_godrays.frag");

	gbuffer_particle_shader = new Shader(
			SHADERS_PATH "/Underwater_visuals_Test/particles.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/particles.frag");

	gbuffer_sand_particle_shader = new Shader(
			SHADERS_PATH "/Underwater_visuals_Test/sand_particles.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/sand_particles.frag");

	gbuffer_water_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_water.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_water.frag");

	gbuffer_shadow_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_shadow.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_shadow.frag");

	add_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/add.frag ");

	overlay_shader = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/overlay.frag ");

	combine_GBuffers = new Shader(
			SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert",
			SHADERS_PATH "/Underwater_Visuals_Test/combineGBuffers.frag ");
}

	/**
	 * creates all render pass instances used for rendering this scene
	 * to make sure they can be accessed from outside this header
	 * They will be added to the state's render loop in this order,
	 * so to add Render Passes in between, use RenderLoop::addRenderPassBefore()
	 *
	 * Keep in mind that objects from outside this feature have to be added to
	 * the initial graphicscomponent lists of the renderpasses manually, after calling this method
	 *
	 * @param target state to get camera etc. from
	 * @param addToRenderLoop boolean whether to add renderpasses to renderloop instantly, true by default
	 */
	static void createRenderPasses(ApplicationState* target, bool addToRenderLoop = true)
	{
		Listener* uniCamPos		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", target->getCamera()->getPositionPointer(), 		"uniformCameraWorldPos");
		Listener* uniClipPoint 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", glm::vec3(0.0, UnderwaterScene::water_height, 0.0), 	"uniformClippingPoint");
		Listener* uniClipNorm	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal , 				"uniformClippingNormal");
		Listener* uniClipNormInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal_inverse , 		"uniformClippingNormal");
		Listener* uniFogColor 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, 							"uniformFogColor");
		Listener* uniFogColorInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color_inverse, 					"uniformFogColor");
		Listener* uniLightPos 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, 						"uniformLightPosition");
		Listener* uniSunDir		= new UploadUniformVec3Listener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunLightDirection,					"uniformSunDirection");
		Listener* uniDepthMVP	=new UploadUniformMat4Listener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::depthMVP,						"uniformDepthMVP");
		Listener* uniDepthBiasMVP=new UploadUniformMat4Listener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::depthBiasMVP,					"uniformDepthBiasMVP");

		Listener* uniRefrText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "uniformRefractionMap", 	UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle());
		Listener* uniReflText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 11, "uniformReflectionMap", 	UnderwaterScene::framebuffer_water_reflection_compositing->getPositionTextureHandle());
		Listener* uniCausticsTex= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
		Listener* uniCausticsTex2=new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
		Listener* uniGBufferDepthMap = new UploadUniformTextureListener("", 7, "uniformDepthMap", framebuffer_gbuffer_default->getDepthBufferHandle( ) );
		Listener* uniPartMap	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 14,"uniformParticlesMap", 	UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle());
		Listener* uniSandPartMap	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 14,"uniformSandParticlesMap", 	UnderwaterScene::framebuffer_sand_particles->getPositionTextureHandle());
		Listener* uniPartText	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 4,"uniformParticleTexture",   UnderwaterScene::particlesTexture->getTextureHandle());
		Listener* uniSandPartText	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 4,"uniformSandParticleTexture",   UnderwaterScene::sandParticlesTexture->getTextureHandle());
		Listener* uniShadowMap  = new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 10,"uniformDepthMap",   		UnderwaterScene::framebuffer_shadow->getDepthBufferHandle() );	// shadow map from sun view

		Listener* uniSunView	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunView, "uniformView");
		Listener* uniSunPersp	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunPerspective, "uniformPerspective");
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

	/******************** 1 GBuffer Alternative Rendering ************************/

		// sun & sky dome must keep an offset to Camera
		//1.1.1: render sky and sun into GBuffer
		gbufferSunSkyRenderPass = new GBufferRenderPass(gbuffer_shader, UnderwaterScene::framebuffer_scene_sky_sun);

		gbufferSunSkyRenderPass->setClearColorBufferBit(true);
		gbufferSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sky_dome);
		gbufferSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sun_Object);

		if (addToRenderLoop)
			target->getRenderLoop()->addRenderPass(gbufferSunSkyRenderPass);

		//1.1.2: light sky and sun
		gbufferCompositingSkySunRenderPass = new CompositingPass(gbuffer_compositing_shadeless_shader, framebuffer_gbuffer_compositing_default );
		gbufferCompositingSkySunRenderPass->setColorMap(    UnderwaterScene::framebuffer_scene_sky_sun->getColorTextureHandle());

		if (addToRenderLoop)
			target->getRenderLoop()->addRenderPass( gbufferCompositingSkySunRenderPass );

		// 1.2.1: render scene into GBuffer
		gbufferRenderPass = new GBufferRenderPass(gbuffer_shader, framebuffer_gbuffer_default);
		gbufferRenderPass->setClearColorBufferBit(true);
		gbufferRenderPass->setInitialGraphicsComponentList ( scene_objects );
		gbufferRenderPass->removeInitialGraphicsComponent( scene_waterPlaneObject );

		if (addToRenderLoop)
			target->getRenderLoop()->addRenderPass( gbufferRenderPass);

		// 1.2.2: render shadowMap
		gbufferShadowRenderPass = new RenderPass(gbuffer_shadow_shader, framebuffer_shadow);
		gbufferShadowRenderPass->setInitialGraphicsComponentList( scene_objects );
		gbufferShadowRenderPass->removeInitialGraphicsComponent( scene_waterPlaneObject );
		gbufferShadowRenderPass->attachListenerOnPostUniformUpload( uniSunView );
		gbufferShadowRenderPass->attachListenerOnPostUniformUpload( uniSunPersp );
		gbufferShadowRenderPass->attachListenerOnPostUniformUpload( uniCamPos );
		if(addToRenderLoop)
			target->getRenderLoop()->addRenderPass(gbufferShadowRenderPass);

		// 1.2.3: light GBuffer scene
		gbufferCompositingRenderPass = new CompositingPass(gbuffer_compositing_shader, framebuffer_gbuffer_compositing_default);
		gbufferCompositingRenderPass->setClearColorBufferBit(false);
		gbufferCompositingRenderPass->setUseAlphaBlending(true);
		gbufferCompositingRenderPass->setColorMap(    framebuffer_gbuffer_default->getColorTextureHandle());
		gbufferCompositingRenderPass->setPositionMap( framebuffer_gbuffer_default->getPositionTextureHandle());
		gbufferCompositingRenderPass->setNormalMap(   framebuffer_gbuffer_default->getNormalTextureHandle());

		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniSunDir );	// attach sun direction
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );

		// add uniforms needed for shadow mapping
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniShadowMap ); // shadow map to compare depth values with
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp ); // needed to compute shadow map coordinates
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniDepthMVP ); // just for the cause
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniDepthBiasMVP); // just in the case
		gbufferCompositingRenderPass->attachListenerOnPostUniformUpload( uniCamPos );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferCompositingRenderPass );

		/************* 2 WATER: Rendering everything needed to render the WaterObject***********/

		/***********  2.1 Render Reflection Map	*********/

		//2.1.1: render sky and sun into GBuffer with reflected camera view
		gbufferReflectionMapSunSkyRenderPass = new GBufferRenderPass(gbuffer_shader, UnderwaterScene::framebuffer_water_reflection_gbuffer);
		gbufferReflectionMapSunSkyRenderPass->setClearColorBufferBit(true);
		gbufferReflectionMapSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sky_dome);
		gbufferReflectionMapSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sun_Object);

		gbufferReflectionMapSunSkyRenderPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before rendering
		gbufferReflectionMapSunSkyRenderPass->attachListenerOnDeactivation( new SetCameraListener( target->getCamera() ));		 // set camera to regular camera after rendering (undo above)

		// make sure Sky Dome and sun is at the correct positon
		gbufferReflectionMapSunSkyRenderPass->attachListenerOnActivation( UnderwaterScene::scene_listener_keep_offset_sky_reflection );
		gbufferReflectionMapSunSkyRenderPass->attachListenerOnActivation( UnderwaterScene::scene_listener_keep_offset_sun_reflection );
		gbufferReflectionMapSunSkyRenderPass->attachListenerOnDeactivation( UnderwaterScene::scene_listener_keep_offset_sky );
		gbufferReflectionMapSunSkyRenderPass->attachListenerOnDeactivation( UnderwaterScene::scene_listener_keep_offset_sun );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferReflectionMapSunSkyRenderPass );

		//2.1.2: light sky and sun
		gbufferCompositingReflectionMapSkySunRenderPass = new CompositingPass(gbuffer_compositing_shadeless_shader, UnderwaterScene::framebuffer_water_reflection_compositing );
		gbufferCompositingReflectionMapSkySunRenderPass->setColorMap(    UnderwaterScene::framebuffer_water_reflection_gbuffer->getColorTextureHandle());

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferCompositingReflectionMapSkySunRenderPass );

		// back ground is done, now render, light and overlay the rest of the scene

		//2.1.3: render the rest of the scene into GBuffer
		gbufferReflectionMapRenderPass = new GBufferRenderPass(gbuffer_culling_shader, UnderwaterScene::framebuffer_water_reflection_gbuffer);
		gbufferReflectionMapRenderPass->setClearColorBufferBit(true);	// clear background information
		gbufferReflectionMapRenderPass->setInitialGraphicsComponentList( scene_objects );	// render scene without background
		gbufferReflectionMapRenderPass->removeInitialGraphicsComponent( UnderwaterScene::scene_waterPlaneObject );  // render everything but the water plane object
		gbufferReflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
		gbufferReflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNorm );  // upload clipping plane normal

		gbufferReflectionMapRenderPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before rendering
		gbufferReflectionMapRenderPass->attachListenerOnDeactivation( new SetCameraListener( target->getCamera() ));		// set camera to regular camera after rendering (undo above)

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferReflectionMapRenderPass );

		// 2.1.4 : light gbuffer reflection map and write into partially filled compositing fbo
		gbufferReflectionMapCompositingPass = new CompositingPass(gbuffer_compositing_shader, UnderwaterScene::framebuffer_water_reflection_compositing);
		gbufferReflectionMapCompositingPass->setClearColorBufferBit(false);	// dont clear color buffer, since background is already rendered
		gbufferReflectionMapCompositingPass->setUseAlphaBlending(true);		// use blending, to overlay image
		gbufferReflectionMapCompositingPass->setColorMap( 	UnderwaterScene::framebuffer_water_reflection_gbuffer->getColorTextureHandle());
		gbufferReflectionMapCompositingPass->setNormalMap( 	UnderwaterScene::framebuffer_water_reflection_gbuffer->getNormalTextureHandle());
		gbufferReflectionMapCompositingPass->setPositionMap(UnderwaterScene::framebuffer_water_reflection_gbuffer->getPositionTextureHandle());

		gbufferReflectionMapCompositingPass->attachListenerOnPostUniformUpload( uniSunDir );	// attach sun direction

		gbufferReflectionMapCompositingPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before composing
		gbufferReflectionMapCompositingPass->attachListenerOnDeactivation( new SetCameraListener( target->getCamera() ));		 // set camera to regular camera after composing (undo above)

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferReflectionMapCompositingPass );

		/*************** 2.2 Render Refraction Map *********/

		//2.2.1: render sky and sun into GBuffer
		gbufferRefractionMapSunSkyRenderPass = new GBufferRenderPass(gbuffer_shader, UnderwaterScene::framebuffer_water_refraction_gbuffer);
		gbufferRefractionMapSunSkyRenderPass->setClearColorBufferBit(true);
		gbufferRefractionMapSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sky_dome);
		gbufferRefractionMapSunSkyRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_sun_Object);

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferRefractionMapSunSkyRenderPass );

		//2.2.2: light sky and sun
		gbufferCompositingRefractionMapSkySunRenderPass = new CompositingPass(gbuffer_compositing_shadeless_shader, UnderwaterScene::framebuffer_water_refraction_compositing );
		gbufferCompositingRefractionMapSkySunRenderPass->setColorMap(    UnderwaterScene::framebuffer_water_refraction_gbuffer->getColorTextureHandle());

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferCompositingRefractionMapSkySunRenderPass );

		// back ground is done, now render, light and overlay the rest of the scene

		// 2.2.3 : render refracted View into seperate GBuffer FBO
		gbufferRefractionMapRenderPass = new GBufferRenderPass(gbuffer_culling_shader, UnderwaterScene::framebuffer_water_refraction_gbuffer);
		gbufferRefractionMapRenderPass->setClearColorBufferBit(true);
		gbufferRefractionMapRenderPass->setInitialGraphicsComponentList( scene_objects );
		gbufferRefractionMapRenderPass->removeInitialGraphicsComponent( scene_waterPlaneObject );  // render everything but the water plane object
		gbufferRefractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
		gbufferRefractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNormInv );  // upload clipping plane normal

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferRefractionMapRenderPass );

		// 2.2.4 COMPOSITING : light gbuffer refraction map
		gbufferRefractionMapCompositingPass = new CompositingPass(gbuffer_compositing_shader, UnderwaterScene::framebuffer_water_refraction_compositing);
		gbufferRefractionMapCompositingPass->setClearColorBufferBit( false );	// dont clear color buffer, since background is already rendered
		gbufferRefractionMapCompositingPass->setUseAlphaBlending( true );		// use blending, to overlay image
		gbufferRefractionMapCompositingPass->setColorMap( 	UnderwaterScene::framebuffer_water_refraction_gbuffer->getColorTextureHandle());
		gbufferRefractionMapCompositingPass->setNormalMap( 	UnderwaterScene::framebuffer_water_refraction_gbuffer->getNormalTextureHandle());
		gbufferRefractionMapCompositingPass->setPositionMap(UnderwaterScene::framebuffer_water_refraction_gbuffer->getPositionTextureHandle());

		gbufferRefractionMapCompositingPass->attachListenerOnPostUniformUpload( uniSunDir );	// attach sun direction

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferRefractionMapCompositingPass);

		/******** 2.3 Render other Water Effects ***********/

		// 2.3.1 render god_rays with gbuffer information ( depth ) into seperate FBO

		// 2.3.1.1 before rendering god_rays, combine gbuffers
		ScreenFillingTriangleRenderPass* gbufferCombineGBuffersOfBackGroundAndForeGround = new ScreenFillingTriangleRenderPass(combine_GBuffers, UnderwaterScene::framebuffer_scene_sky_sun);
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 6 , "colorMap", framebuffer_gbuffer_default->getColorTextureHandle() ) );
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 5 , "normalMap", framebuffer_gbuffer_default->getNormalTextureHandle() ) );
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 4 , "positionMap", framebuffer_gbuffer_default->getPositionTextureHandle() ) );
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 10, "colorMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getColorTextureHandle() ) );
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 11, "normalMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getNormalTextureHandle() ) );
		gbufferCombineGBuffersOfBackGroundAndForeGround->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 12, "positionMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getPositionTextureHandle() ) );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass(gbufferCombineGBuffersOfBackGroundAndForeGround);

		gbufferGodraysRenderPass = new CompositingPass(gbuffer_god_rays_shader, UnderwaterScene::framebuffer_water_god_rays);	// compositing
		gbufferGodraysRenderPass->setPositionMap( UnderwaterScene::framebuffer_scene_sky_sun->getPositionTextureHandle( ) );	// use gbuffer position information for depth testing

		gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
		gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
		gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCamPos );			// upload cam world position

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass(gbufferGodraysRenderPass);

		// 2.3.1 render particles into a seperate fbo, use depth information of gbuffer as depth map
		gbufferParticlesRenderPass = new ParticlesRenderPass(gbuffer_particle_shader, UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, VirtualObjectFactory::getInstance()->getQuad()->getMesh()->getVAO());

		gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniGBufferDepthMap );

		gbufferParticlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
		gbufferParticlesRenderPass->setUseDepthTest(false);	// disable depth testing
		gbufferParticlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
		gbufferParticlesRenderPass->setCustomClearColor( glm::vec4 ( 0.0f, 0.0f, 0.0f, 0.0f) );// set clear color to transparent
		gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniPartText);	// upload Particles Texture
		gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferParticlesRenderPass );
		

		gbufferSandParticlesRenderPass = new ParticlesRenderPass(gbuffer_sand_particle_shader, UnderwaterScene::framebuffer_sand_particles, UnderwaterScene::sand_particles, VirtualObjectFactory::getInstance()->getQuad()->getMesh()->getVAO());

		gbufferSandParticlesRenderPass->attachListenerOnPostUniformUpload( uniGBufferDepthMap );

		gbufferSandParticlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
		gbufferSandParticlesRenderPass->setUseDepthTest(false);	// disable depth testing
		gbufferSandParticlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
		gbufferSandParticlesRenderPass->setCustomClearColor( glm::vec4 ( 0.0f, 0.0f, 0.0f, 0.0f) );// set clear color to transparent
		gbufferSandParticlesRenderPass->attachListenerOnPostUniformUpload( uniSandPartText);	// upload Particles Texture
		gbufferSandParticlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferSandParticlesRenderPass );

		// 2.3.1 render caustics with gbuffer information ( depth ) into seperate FBO
		gbufferCausticsRenderPass = new CompositingPass( gbuffer_caustics_shader, UnderwaterScene::framebuffer_water_caustics);
		gbufferCausticsRenderPass->setPositionMap( framebuffer_gbuffer_default->getPositionTextureHandle( ) ); // use position texture handle as depth information
		gbufferCausticsRenderPass->setNormalMap( framebuffer_gbuffer_default->getNormalTextureHandle() );	// use normal texture
		gbufferCausticsRenderPass->setColorMap( framebuffer_gbuffer_default->getColorTextureHandle() );		// use color texture

		gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
		gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
		gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunDir );	// upload sun light direction

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferCausticsRenderPass );

		/************** 2.4 Overlay Effects if above water*********/

		// 2.4.1 add caustics ontop of refracted view if above water
		addCausticsRefraction = new MixTexturesRenderPass( add_shader, UnderwaterScene::framebuffer_water_refraction_compositing, UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );
		addCausticsRefraction->setMixTextureUniformName("uniformAddTexture");

		addCausticsRefractionProxy = new ConditionalRenderPassProxy (addCausticsRefraction, &UnderwaterScene::is_underwater, true);
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( addCausticsRefractionProxy );

		// 2.4.2 alwas overlay fog ontop of refracted view
		overlayFogRefraction = new CompositingPass(gbuffer_fog, UnderwaterScene::framebuffer_water_refraction_compositing );
		overlayFogRefraction ->setPositionMap(UnderwaterScene::framebuffer_water_refraction_gbuffer->getPositionTextureHandle());
		overlayFogRefraction ->setUseAlphaBlending(true);
		overlayFogRefraction ->setClearColorBufferBit( false );
		// upload fog properties
		overlayFogRefraction->attachListenerOnPostUniformUpload( uniFogBeginInv );
		overlayFogRefraction->attachListenerOnPostUniformUpload( uniFogEndInv );
		overlayFogRefraction->attachListenerOnPostUniformUpload( uniFogColorInv );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlayFogRefraction );

		// 2.4.3 always overlay fog ontop of reflected view
		overlayFogReflection = new CompositingPass(gbuffer_fog, UnderwaterScene::framebuffer_water_reflection_compositing );
		overlayFogReflection ->setPositionMap(UnderwaterScene::framebuffer_water_reflection_gbuffer->getPositionTextureHandle());
		overlayFogReflection ->setUseAlphaBlending(true);
		overlayFogReflection ->setClearColorBufferBit( false );
		// upload fog properties
		overlayFogReflection->attachListenerOnPostUniformUpload( uniFogBegin );
		overlayFogReflection->attachListenerOnPostUniformUpload( uniFogEnd );
		overlayFogReflection->attachListenerOnPostUniformUpload( uniFogColor );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlayFogReflection );

		// 2.4.4 overlay god rays ontop of refracted view if above water
		addGodRaysRefraction = new MixTexturesRenderPass( add_shader, UnderwaterScene::framebuffer_water_refraction_compositing, UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
		addGodRaysRefraction->setMixTextureUniformName("uniformAddTexture");

		addGodRaysRefractionProxy = new ConditionalRenderPassProxy (addGodRaysRefraction, &UnderwaterScene::is_underwater, true);

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( addGodRaysRefractionProxy );

		// 2.4.5 overlay particles ontop of refracted view if above water
		overlayParticlesRefraction = new MixTexturesRenderPass( overlay_shader, UnderwaterScene::framebuffer_water_refraction_compositing, UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );
		overlayParticlesRefraction->setMixTextureUniformName("uniformAddTexture");
		overlayParticlesRefractionProxy = new ConditionalRenderPassProxy (overlayParticlesRefraction, &UnderwaterScene::is_underwater, true);
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlayParticlesRefractionProxy );

		overlaySandParticlesRefraction = new MixTexturesRenderPass( overlay_shader, UnderwaterScene::framebuffer_water_refraction_compositing, UnderwaterScene::framebuffer_water_refraction_compositing->getPositionTextureHandle(), UnderwaterScene::framebuffer_sand_particles->getPositionTextureHandle() );
		overlaySandParticlesRefraction->setMixTextureUniformName("uniformAddTexture");
		overlaySandParticlesRefractionProxy = new ConditionalRenderPassProxy (overlaySandParticlesRefraction, &UnderwaterScene::is_underwater, true);
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlaySandParticlesRefractionProxy );

		/**************	2.6 Render Water Object ***************/

		// 2.6. render waterobject into seperate FBO
		gbufferWaterRenderPass = new RenderPass(gbuffer_water_shader, UnderwaterScene::framebuffer_water_water_object);

		gbufferWaterRenderPass->addInitialGraphicsComponent(UnderwaterScene::scene_waterPlaneObject);	// render only water plane object
		gbufferWaterRenderPass->setClearColorBufferBit(true);	// clear color
		gbufferWaterRenderPass->setClearDepthBufferBit(true);
		gbufferWaterRenderPass->setUseDepthTest(true);
		gbufferWaterRenderPass->setCustomClearColor(glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f) );	// clear with 0 alpha to use for overlay later

		gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniGBufferDepthMap );	// use depth buffer of gbuffer
		gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniReflText );	// reflectionmap
		gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniRefrText );	// refractionmap
		gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	// upload light position
		gbufferWaterRenderPass->attachListenerOnPostUniformUpload( uniReflMatr );	// upload reflective view matrix

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( gbufferWaterRenderPass );

		/******** COMPOSITING ***********/

		// 6.0.1 : overlay Water ontop of scene fbo
		overlayWaterObject = new MixTexturesRenderPass( overlay_shader, finalImage, framebuffer_gbuffer_compositing_default->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_water_object->getColorTextureHandle());
		overlayWaterObject->setMixTextureUniformName("uniformOverlayTexture");
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass(overlayWaterObject);

		// 6.1. : add caustics on top of scene fbo
		addCaustics = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );
		addCaustics->setMixTextureUniformName("uniformAddTexture");
		addCausticsProxy = new ConditionalRenderPassProxy (addCaustics, &UnderwaterScene::is_underwater);
		// add only, if camera is underwater
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( addCausticsProxy );

		//6.2. : add fog as a post-process
		//6.2.1 : combine Gbuffers of Scene, Sky and Water Object
		combineWaterObjectWithGBuffer = new ScreenFillingTriangleRenderPass(combine_GBuffers, UnderwaterScene::framebuffer_scene_sky_sun);
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 6 , "colorMap", UnderwaterScene::framebuffer_water_water_object->getColorTextureHandle() ) );
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 5 , "normalMap", UnderwaterScene::framebuffer_water_water_object->getNormalTextureHandle() ) );
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 4 , "positionMap", UnderwaterScene::framebuffer_water_water_object->getPositionTextureHandle() ) );
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 10, "colorMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getColorTextureHandle() ) );
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 11, "normalMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getNormalTextureHandle() ) );
		combineWaterObjectWithGBuffer->attachListenerOnPostUniformUpload(new UploadUniformTextureListener("", 12, "positionMap_2", UnderwaterScene::framebuffer_scene_sky_sun->getPositionTextureHandle() ) );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass(combineWaterObjectWithGBuffer);

		//6.2.2 : Compose Fog with updated PositionMap
		addFog = new CompositingPass(gbuffer_fog, finalImage );
		addFog->setPositionMap(UnderwaterScene::framebuffer_scene_sky_sun->getPositionTextureHandle());
		addFog->setUseAlphaBlending(true);
		addFog->setClearColorBufferBit( false );

		// upload fog properties
		addFog->attachListenerOnPostUniformUpload( uniFogBegin );
		addFog->attachListenerOnPostUniformUpload( uniFogEnd );
		addFog->attachListenerOnPostUniformUpload( uniFogColor );

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( addFog );

		// 6.3. : add god rays ontop of scene fbo
		addGodRays = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
		addGodRays->setMixTextureUniformName("uniformAddTexture");
		addGodRaysProxy = new ConditionalRenderPassProxy (addGodRays, &UnderwaterScene::is_underwater);

		// add only, if camera is underwater
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( addGodRaysProxy );

		// 6.4. : overlay particles ontop of scene fbo
		overlayParticles = new MixTexturesRenderPass( overlay_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );
		overlayParticles->setMixTextureUniformName("uniformOverlayTexture");
		// add only, if camera is underwater
		overlayParticlesProxy = new ConditionalRenderPassProxy (overlayParticles, &UnderwaterScene::is_underwater);
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlayParticlesProxy );

		overlaySandParticles = new MixTexturesRenderPass( overlay_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_sand_particles->getPositionTextureHandle() );
		overlaySandParticles->setMixTextureUniformName("uniformOverlayTexture");

		overlaySandParticlesProxy = new ConditionalRenderPassProxy (overlaySandParticles, &UnderwaterScene::is_underwater);
		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass( overlaySandParticlesProxy );

		/********* Present Final Image ***************/
		presentFinalImage = new TextureRenderPass(simpleTex,0,finalImage->getPositionTextureHandle());
		presentFinalImage->setTextureUniformName("diffuseTexture");

		if (addToRenderLoop)
				target->getRenderLoop()->addRenderPass(presentFinalImage);

	/******************** Debug Views ************************/

	}

	static void getLightPosition(glm::vec3 &position){
		position = lightPosition;
	}

	static void configureInputHandling(ApplicationState* target){
		IOHandler* io =  target->getIOHandler();
	}

	/**
	 * mirrors a point at the water height and returns the mirrored point
	 *
	 * @param vec point to be reflected on water surface
	 *
	 * @return the reflected point
	 */
	static glm::vec3 reflectOnWaterSurface(glm::vec3& vec){
		glm::vec3 result(vec);

		float mirrored_height = 2.0f * water_height - result.y;
		result.y = mirrored_height;
		return result;
	}
}

#endif
