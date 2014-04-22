#ifndef HUD_H
#define HUD_H

#include "HUDElement.h"

namespace HUD{

	FrameBufferObject* framebuffer_HUD;

	Texture* HUD_texture;

	HUDSystem* hudSys;
	HUDElement* airBar;

	int air = 100;

	void createHUD(ApplicationState* target){
	//----framebuffer object----//
		framebuffer_HUD = new FrameBufferObject(800, 600);
		framebuffer_HUD->bindFBO();
		framebuffer_HUD->createPositionTexture();
		framebuffer_HUD->makeDrawBuffers();
		framebuffer_HUD->unbindFBO();


	hudSys = new	HUDSystem();
	airBar = new HUDElement(glm::vec3(0.0, 0.0, 0.0));
	hudSys->addHUDElement(airBar);

	target->attachListenerOnBeginningProgramCycle(new UpdateHUDSystemListener(hudSys, IOManager::getInstance()->getDeltaTimePointer()));


	//----textures----//
		HUD_texture = new Texture(RESOURCES_PATH "/demo_scene/bubbles.png");
	}

}

#endif
