#ifndef HUD_H
#define HUD_H

#include "HUDElement.h"

namespace HUD{

	FrameBufferObject* framebuffer_HUD;
	HUDSystem* hudSys;

	HUDElement* airBar;
	HUDElement* depthM;

	Texture* HUD_texture;

	//globals
	int maxAir = 120.0;		//in seconds

	void createHUD(ApplicationState* target){
	//frameBufferObject
		framebuffer_HUD = new FrameBufferObject(800, 600);
		framebuffer_HUD->bindFBO();
		framebuffer_HUD->createPositionTexture();
		framebuffer_HUD->makeDrawBuffers();
		framebuffer_HUD->unbindFBO();

	//new HUDSystem - add some HUDElements
	hudSys = new	HUDSystem();

			//airBar
	airBar = new HUDElement(glm::vec3(-0.5, 0.0, 0.0));
	hudSys->addHUDElement(airBar);

			//depthMeter
	depthM = new HUDElement(glm::vec3(0.5, 0.0, 0.0));
	hudSys->addHUDElement(depthM);

	//Listeners
	target->attachListenerOnBeginningProgramCycle(new UpdateHUDSystemListener(hudSys, IOManager::getInstance()->getDeltaTimePointer()));


	//textures
		HUD_texture = new Texture(RESOURCES_PATH "/demo_scene/bubbles.png");
	}



}

#endif
