#ifndef HUD_H
#define HUD_H

#include "Application/ApplicationStates.h"
#include "ParticleSystem.h"
#include "Visuals/FrameBufferObject.h"

namespace HUD{

	FrameBufferObject* framebuffer_HUD;

	Texture* HUD_texture;

	void createHUD(ApplicationState* target){
	//----framebuffer object----//
		framebuffer_HUD = new FrameBufferObject(800, 600);
		framebuffer_HUD->bindFBO();
		framebuffer_HUD->createPositionTexture();
		framebuffer_HUD->makeDrawBuffers();
		framebuffer_HUD->unbindFBO();

	//----textures----//
		HUD_texture = new Texture(RESOURCES_PATH "/demo_scene/CGSkies_0003_free.jpg");
	}

}

#endif
