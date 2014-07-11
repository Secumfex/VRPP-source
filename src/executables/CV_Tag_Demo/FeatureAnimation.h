#ifndef FEATUREANIMATION_H
#define FEATUREANIMATION_H
#include "PlaceHolderListeners.h"
#include <Animation/Flock.h>

namespace AnimationFeature
{
/*
 * GLOBAL VARIABLES
 */
VirtualObject* fish = 0;
AnimationLoop* anime = 0;
RenderPass* gbufferAnimationRenderPass = 0;
FrameBufferObject* fbo = 0;

void createObjects( ApplicationState* target ){

	fish = VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/animation_test/piranha.dae", VirtualObjectFactory::OTHER, 1.0f, 0, false);

	target->addVirtualObject(fish);

	glm::vec3 position = glm::vec3(0.0f, 4.0f, 0.0f);

	glm::mat4 mat = glm::translate(glm::mat4(), position) * glm::scale(glm::mat4(), glm::vec3(0.25f, 0.25f, 0.25f));

	fish->setModelMatrix(mat);
	fish->scale(glm::vec3(0.25f, 0.25f, 0.25f));
	fish->translate(position);
	target->attachListenerOnBeginningProgramCycle(new UpdateAnimationLoopListener(fish->getAnimation()));
	target->attachListenerOnBeginningProgramCycle(new LookAtCameraListener(fish, mat, position));
}

/**
 * create a RenderPass that renders the boids into the provided FrameBufferObject
 */
RenderPass* createAnimationRenderPass(FrameBufferObject* gbuffer)
{
	Shader* animatedFishGBufferShader = 0;

	// generate a suitable GBuffer Shader
	if ( fish == 0)
	{
		std::cout << "ERROR : createObjects() has not yet been called. RenderPass has no shader"<< std::endl;
	}
	else
	{
		animatedFishGBufferShader = ShaderFactory::getInstance()->createGBuffer( fish->getGraphicsComponent()[0]);
	}

	// create and configure RenderPass
	gbufferAnimationRenderPass = new GBufferRenderPass( animatedFishGBufferShader, gbuffer );
	gbufferAnimationRenderPass->setClearDepthBufferBit(false);

	// add Fish Object as initial graphics components to be rendered
		gbufferAnimationRenderPass->addInitialGraphicsComponent(
				AnimationFeature::fish);

	return gbufferAnimationRenderPass;
}

}
#endif
