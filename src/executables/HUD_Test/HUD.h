#ifndef HUD_H
#define HUD_H

#include "Application/ApplicationStates.h"
#include "PlaceHolderListeners.h"
#include "ParticleSystem.h"
#include "Visuals/FrameBufferObject.h"

namespace HUD{

	FrameBufferObject* framebuffer_HUD = new FrameBufferObject(800, 600);

	framebuffer_HUD->bindFBO();


}

#endif
