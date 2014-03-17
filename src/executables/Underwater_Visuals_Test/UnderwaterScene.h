#ifndef UNDERWATERSCENE_H
#define UNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "PlaceHolderListeners.h"

namespace UnderwaterScene{

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f/ 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.1f);
	glm::vec3 lightPosition(0.0f,1000.0f,0.0f);
	glm::vec3 lightDirection(0.0f,-1.0f,0.0f);
	
	VirtualObject* scene_groundObject;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_waterPlaneObject;
	VirtualObject* scene_wallObject2;
	VirtualObject* scene_sun_Object;

	static void createScene(ApplicationState* target){
		target->attachListenerOnActivation(	new SetClearColorListener( watercolor.x, watercolor.y, watercolor.z, watercolor.w ));

		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", VirtualObjectFactory::OTHER);
		
		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", VirtualObjectFactory::OTHER);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", VirtualObjectFactory::OTHER);

		scene_sun_Object 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", VirtualObjectFactory::OTHER);

		if (scene_sun_Object->getGraphicsComponent().size() > 0){
			//	scene_sun_Object->getGraphicsComponent()[0]->getMaterial()->setEmission(glm::vec3(1.0f, 1.0f, 1.0f));
				scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
				std::cout << "sun emission set " << std::endl;
				glm::vec3 ec = scene_sun_Object->getGraphicsComponent()[0]->getMaterial()->getEmission();
				std::cout << "sun emission color " <<ec.x << ", " << ec.y << ", "<<ec.z << std::endl;
		}

		// set CameraPosition
		Camera* cam =  target->getCamera();
		cam->setPosition( cam->getPosition() + glm::vec3(0.0,1.5,0.0));
	}

	static void getLightPosition(glm::vec3 &position){
		position = lightPosition;
	}

	static void getLightDirection(glm::vec3 &direction){
		direction = lightDirection;
	}

	static void configureInputHandling(ApplicationState* target){
		IOHandler* io =  target->getIOHandler();
	}
}
#endif