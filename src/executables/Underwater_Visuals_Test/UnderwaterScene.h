#ifndef UNDERWATERSCENE_H
#define UNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "PlaceHolderListeners.h"

namespace UnderwaterScene{

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f/ 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.1f);
	glm::vec3 lightPosition(0.0f,100.0f,0.0f);
	
	VirtualObject* scene_groundObject;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_waterPlaneObject;
	VirtualObject* scene_wallObject2;

	static void createScene(ApplicationState* target){
		target->attachListenerOnActivation(	new SetClearColorListener( watercolor.x, watercolor.y, watercolor.z, watercolor.w ));

		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", VirtualObjectFactory::OTHER);
		
		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", VirtualObjectFactory::OTHER);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", VirtualObjectFactory::OTHER);

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