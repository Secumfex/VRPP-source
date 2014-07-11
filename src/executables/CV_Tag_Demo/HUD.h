#ifndef HUD_H
#define HUD_H

#include "HUDElement.h"
#include "HUDSystem.h"

namespace HUD{

	//create instances for later initialization
	FrameBufferObject* framebuffer_HUD;
	HUDSystem* hudSys;

	HUDElement* airBar;

	Texture* HUD_texture1;

	//globals
	int maxAir = 120.0;		//air amount of player (in seconds)

	void createHUD(ApplicationState* target){
	//creating frameBufferObject
		framebuffer_HUD = new FrameBufferObject(800, 600);
		framebuffer_HUD->bindFBO();
		framebuffer_HUD->createPositionTexture();
		framebuffer_HUD->makeDrawBuffers();
		framebuffer_HUD->unbindFBO();

	//creating textures
		HUD_texture1 = new Texture(RESOURCES_PATH "/demo_scene/bubbles4.png");
//		HUD_texture2 = new Texture(RESOURCES_PATH "/demo_scene/scala.png");
//		HUD_texture3 = new Texture(RESOURCES_PATH "/demo_scene/marker.png");

	//new HUDSystem - add some HUDElements
	hudSys = new	HUDSystem();

			//airBar
	airBar = new HUDElement(glm::vec3(-0.5, 0.0, 0.0));
	airBar->setTexture(HUD_texture1);
	hudSys->addHUDElement(airBar);		//add HUDElement to HUDElements Vector
//
//			//depthMeter
//	depthM = new HUDElement(glm::vec3(1.2, 0.0, 0.0));
//	depthM->setTexture(HUD_texture2);
//	hudSys->addHUDElement(depthM);		//add HUDElement to HUDElements Vector
//
//			//Marker
//	marker = new HUDElement(glm::vec3(0.32, -0.96, 0.0));
//	marker->setTexture(HUD_texture3);
//	hudSys->addHUDElement(marker);		//add HUDElement to HUDElements Vector

	//Listener (not used yet, but implemented for later purpose
	//target->attachListenerOnBeginningProgramCycle(new UpdateHUDSystemListener(hudSys, IOManager::getInstance()->getDeltaTimePointer()));
	}
}

#endif
