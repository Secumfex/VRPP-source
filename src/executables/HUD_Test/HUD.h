#ifndef HUD_H
#define HUD_H

#include "HUDElement.h"

namespace HUD{

	FrameBufferObject* framebuffer_HUD;
	HUDSystem* hudSys;

	HUDElement* airBar;
	HUDElement* depthM;
	HUDElement* marker;

	Texture* HUD_texture1;
	Texture* HUD_texture2;
	Texture* HUD_texture3;

	//globals
	int maxAir = 120.0;		//in seconds

	void createHUD(ApplicationState* target){
	//frameBufferObject
		framebuffer_HUD = new FrameBufferObject(800, 600);
		framebuffer_HUD->bindFBO();
		framebuffer_HUD->createPositionTexture();
		framebuffer_HUD->makeDrawBuffers();
		framebuffer_HUD->unbindFBO();

	//textures
		HUD_texture1 = new Texture(RESOURCES_PATH "/demo_scene/bubbles.png");
		HUD_texture2 = new Texture(RESOURCES_PATH "/demo_scene/bubbles.png");
		HUD_texture3 = new Texture(RESOURCES_PATH "/demo_scene/bubbles.png");

	//new HUDSystem - add some HUDElements
	hudSys = new	HUDSystem();

			//airBar
	airBar = new HUDElement(glm::vec3(-0.5, 0.0, 0.0));
	airBar->setTexture(HUD_texture1);
	hudSys->addHUDElement(airBar);

			//depthMeter
	depthM = new HUDElement(glm::vec3(1.2, 0.0, 0.0));
	depthM->setTexture(HUD_texture2);
	hudSys->addHUDElement(depthM);

			//Marker
	marker = new HUDElement(glm::vec3(1.0, 0.0, 0.0));
	marker->setTexture(HUD_texture3);
	hudSys->addHUDElement(marker);

	//Listeners
	target->attachListenerOnBeginningProgramCycle(new UpdateHUDSystemListener(hudSys, IOManager::getInstance()->getDeltaTimePointer()));


	}



}

#endif
