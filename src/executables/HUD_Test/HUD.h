#ifndef HUD_H
#define HUD_H

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
	airBar = new HUDElement();
	hudSys->addHUDElement(airBar);

	target->attachListenerOnBeginningProgramCycle(new UpdateHUDSystemListener(hudSys, IOManager::getInstance()->getDeltaTimePointer()));


	//----textures----//
		HUD_texture = new Texture(RESOURCES_PATH "/bubbles.png");
	}

}

#endif
