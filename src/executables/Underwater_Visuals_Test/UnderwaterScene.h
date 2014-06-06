#ifndef UNDERWATERSCENE_H
#define UNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "PlaceHolderListeners.h"

#include "ParticleSystem.h"

namespace UnderwaterScene{

	bool is_underwater;

	float water_height = 10.0f;

	float fog_begin = 2.0f;
	float fog_end	= 200.0f;
	float fog_begin_inverse = 100.0f;
	float fog_end_inverse	= 10000.0f;

	float fog_begin_under_water = 2.0f;
	float fog_end_under_water = 300.0f;
	float fog_end_above_water = 10000.0f;
	float fog_begin_above_water = 100.0f;

	int   particle_amount = 100;
	float particle_distance_max = 3.5f;

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.0f);
	glm::vec4 skycolor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 0.0f);
	glm::vec3 fog_color(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);
	glm::vec3 fog_color_inverse(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f);
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

	VirtualObject* scene_groundObject;
	VirtualObject* scene_sky_dome;
	VirtualObject* scene_stoneObject1;
	VirtualObject* scene_sun_Object;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_wallObject2;
	VirtualObject* scene_waterPlaneObject;
	VirtualObject* scene_mountainObject1;

	FrameBufferObject* framebuffer_water_reflection_gbuffer;
	FrameBufferObject* framebuffer_water_reflection_compositing;
	FrameBufferObject* framebuffer_water_refraction_gbuffer;
	FrameBufferObject* framebuffer_water_refraction_compositing;
	FrameBufferObject* framebuffer_water_god_rays;
	FrameBufferObject* framebuffer_water_particles;
	FrameBufferObject* framebuffer_water_water_object;
	FrameBufferObject* framebuffer_water_caustics;
	FrameBufferObject* framebuffer_scene_sky_sun;

	Camera* reflectedCamera;

	Texture* causticsTexture;
	Texture* particlesTexture;

	ParticleSystem* water_particles;

	Listener* scene_listener_keep_offset_sun_reflection;
	Listener* scene_listener_keep_offset_sky_reflection;
	Listener* scene_listener_keep_offset_sun;
	Listener* scene_listener_keep_offset_sky;

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

		UnderOrAboveWaterListener* waterlistener0 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_0, exitWater_0);

		UnderOrAboveWaterListener* waterlistener1 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_1, exitWater_1);
		UnderOrAboveWaterListener* waterlistener2 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_2, exitWater_2);
		UnderOrAboveWaterListener* waterlistener3 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_3, exitWater_3);
		UnderOrAboveWaterListener* waterlistener4 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_4, exitWater_4);
		UnderOrAboveWaterListener* waterlistener5 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_5, exitWater_5);
		UnderOrAboveWaterListener* waterlistener6 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_6, exitWater_6);
		UnderOrAboveWaterListener* waterlistener7 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_7, exitWater_7);
		UnderOrAboveWaterListener* waterlistener8 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_8, exitWater_8);
		UnderOrAboveWaterListener* waterlistener9 = new UnderOrAboveWaterListener(target->getCamera(), &water_height, enterWater_9, exitWater_9);
		
		target->attachListenerOnBeginningProgramCycle(waterlistener0);
		target->attachListenerOnBeginningProgramCycle(waterlistener1);
		target->attachListenerOnBeginningProgramCycle(waterlistener2);
		target->attachListenerOnBeginningProgramCycle(waterlistener3);
		target->attachListenerOnBeginningProgramCycle(waterlistener4);
		target->attachListenerOnBeginningProgramCycle(waterlistener5);
		target->attachListenerOnBeginningProgramCycle(waterlistener6);
		target->attachListenerOnBeginningProgramCycle(waterlistener7);
		target->attachListenerOnBeginningProgramCycle(waterlistener8);
		target->attachListenerOnBeginningProgramCycle(waterlistener9);
		/*********************************************************************************/

		/******************* scene creation **********************************************/
		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", 		VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);
		
		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", 		VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", 		VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_stoneObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_mountainObject1	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_mountain_01.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);
		
		scene_sky_dome			= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sky_dome.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);
		scene_sun_Object 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", 	VirtualObjectFactory::OTHER, 0.0f, 1, true);

		sunView = glm::lookAt( - sunLightDirection , glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) );
		sunPerspective = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
		sunViewPerspective 		= sunPerspective * sunView;

		if (scene_sun_Object->getGraphicsComponent().size() > 0){
				scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
		}
		/*********************************************************************************/

		/******************* particle System objects *****************************************/
		water_particles = new ParticleSystem(target->getCamera()->getPositionPointer(), particle_distance_max);
		water_particles->setParticleAmount(particle_amount);
		target->attachListenerOnBeginningProgramCycle(new UpdateParticleSystemListener(water_particles, IOManager::getInstance()->getDeltaTimePointer()));
		/*********************************************************************************/

		/******************* framebuffer objects *****************************************/
		framebuffer_water_reflection_compositing = new FrameBufferObject(800,600);
		framebuffer_water_reflection_compositing ->bindFBO();
		framebuffer_water_reflection_compositing ->createPositionTexture();
		framebuffer_water_reflection_compositing ->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_reflection_compositing ->unbindFBO();

		framebuffer_water_refraction_compositing = new FrameBufferObject(800,600);
		framebuffer_water_refraction_compositing ->bindFBO();
		framebuffer_water_refraction_compositing ->createPositionTexture();
		framebuffer_water_refraction_compositing ->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_refraction_compositing ->unbindFBO();

		framebuffer_water_reflection_gbuffer = new FrameBufferObject(800,600);
		framebuffer_water_reflection_gbuffer->bindFBO();
		framebuffer_water_reflection_gbuffer->createPositionTexture();
		framebuffer_water_reflection_gbuffer->createNormalTexture();
		framebuffer_water_reflection_gbuffer->createColorTexture();
		framebuffer_water_reflection_gbuffer->makeDrawBuffers();
		framebuffer_water_reflection_gbuffer->unbindFBO();

		framebuffer_water_refraction_gbuffer = new FrameBufferObject(800,600);
		framebuffer_water_refraction_gbuffer->bindFBO();
		framebuffer_water_refraction_gbuffer->createPositionTexture();
		framebuffer_water_refraction_gbuffer->createNormalTexture();
		framebuffer_water_refraction_gbuffer->createColorTexture();
		framebuffer_water_refraction_gbuffer->makeDrawBuffers();
		framebuffer_water_refraction_gbuffer->unbindFBO();

		framebuffer_water_god_rays = new FrameBufferObject(200,150);
		framebuffer_water_god_rays->bindFBO();
		framebuffer_water_god_rays->createPositionTexture();
		framebuffer_water_god_rays->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_god_rays->unbindFBO();

		framebuffer_water_particles = new FrameBufferObject(400,300);
		framebuffer_water_particles->bindFBO();
		framebuffer_water_particles->createPositionTexture();
		framebuffer_water_particles->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_particles->unbindFBO();

		framebuffer_water_caustics = new FrameBufferObject(800,600);
		framebuffer_water_caustics->bindFBO();
		framebuffer_water_caustics->createPositionTexture();
		framebuffer_water_caustics->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_caustics->unbindFBO();

		framebuffer_water_water_object = new FrameBufferObject(800,600);
		framebuffer_water_water_object->bindFBO();
		framebuffer_water_water_object->createPositionTexture();
		framebuffer_water_water_object->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_water_object->unbindFBO();

		framebuffer_scene_sky_sun	= new FrameBufferObject(800,600);
		framebuffer_scene_sky_sun->bindFBO();
		framebuffer_scene_sky_sun->createPositionTexture();
		framebuffer_scene_sky_sun->createNormalTexture();
		framebuffer_scene_sky_sun->createColorTexture();
		framebuffer_scene_sky_sun->makeDrawBuffers();
		framebuffer_scene_sky_sun->unbindFBO();

		/*********************************************************************************/

		/******************* textures creation	  ****************************************/
		causticsTexture = new Texture( RESOURCES_PATH "/demo_scene/caustics.jpg" );
		particlesTexture= new Texture( RESOURCES_PATH "/demo_scene/particle.png");
		/*********************************************************************************/

		/******************* default cam position ****************************************/
		Camera* cam =  target->getCamera();
		cam->setPosition( cam->getPosition() + glm::vec3(0.0,1.5,0.0));
		
		reflectedCamera = new Camera();
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
	}

	static void getLightPosition(glm::vec3 &position){
		position = lightPosition;
	}

	static void configureInputHandling(ApplicationState* target){
		IOHandler* io =  target->getIOHandler();
	}

	static glm::vec3 reflectOnWaterSurface(glm::vec3& vec){
		glm::vec3 result(vec);

		float mirrored_height = 2.0f * water_height - result.y;
		result.y = mirrored_height;   
		return result;
	}
}

#endif
