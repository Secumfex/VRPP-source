#ifndef UNDERWATERSCENE_H
#define UNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "PlaceHolderListeners.h"

namespace UnderwaterScene{

	float water_height = 10.0f;

	float fog_begin = 2.0f;
	float fog_end	= 200.0f;

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.0f);
	glm::vec3 lightPosition(0.0f,1000.0f,0.0f);
	glm::vec4 skycolor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 0.0f);
	glm::vec3 fog_color(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);
	
	VirtualObject* scene_groundObject;
	VirtualObject* scene_stoneObject1;
	VirtualObject* scene_stoneObject2;
	VirtualObject* scene_sun_Object;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_wallObject2;
	VirtualObject* scene_waterPlaneObject;

	static void createScene(ApplicationState* target){
		SetClearColorListener* enterWater = new SetClearColorListener( watercolor.x, watercolor.y, watercolor.z, watercolor.w );
		SetClearColorListener* exitWater =  new SetClearColorListener( skycolor.x, skycolor.y, skycolor.z, skycolor.w );
		UnderOrAboveWaterListener* waterlistener = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater, exitWater);
		target->attachListenerOnBeginningProgramCycle(waterlistener);

		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", VirtualObjectFactory::OTHER);
		
		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", VirtualObjectFactory::OTHER);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", VirtualObjectFactory::OTHER);
		scene_stoneObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", VirtualObjectFactory::OTHER);
		scene_stoneObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", VirtualObjectFactory::OTHER);
		
//		scene_stoneObject1->translate(glm::vec3(3.0f, 0.0f, 3.0f));
//		scene_stoneObject2->translate(glm::vec3(5.0f, 0.0f, 3.0f));

		scene_sun_Object 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", VirtualObjectFactory::OTHER);

		if (scene_sun_Object->getGraphicsComponent().size() > 0){
				scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
		}

		// set CameraPosition
		Camera* cam =  target->getCamera();
		cam->setPosition( cam->getPosition() + glm::vec3(0.0,1.5,0.0));
	}

	static void getLightPosition(glm::vec3 &position){
		position = lightPosition;
	}

	static void configureInputHandling(ApplicationState* target){
		IOHandler* io =  target->getIOHandler();
	}
}

#endif