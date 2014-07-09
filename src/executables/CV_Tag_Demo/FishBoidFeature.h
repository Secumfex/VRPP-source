#ifndef FEATUREBOIDS_H
#define FEATUREBOIDS_H
#include "PlaceHolderListeners.h"
#include <Animation/Flock.h>

namespace FishBoidFeature
{
/*
 * GLOBAL VARIABLES
 */
VirtualObject* fish = 0;
Flock* flock = 0;
std::vector<VirtualObject* > fishes;
RenderPass* gbufferBoidRenderPass = 0;

void createObjects( ApplicationState* target ){

	fish = target->createVirtualObject(RESOURCES_PATH "/animation_test/fish.dae", VirtualObjectFactory::OTHER, 1.0f, 0, false);

	flock = new Flock();

	glm::mat4 trans = glm::rotate(glm::mat4(), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(0.05f));

	flock->addBoid(fish, trans);

	fishes.push_back(fish);

	unsigned int i;
	for (i = 0; i < 50; ++i) {
		VirtualObject *fish_copy = new VirtualObject(fish);
		flock->addBoid(fish_copy, trans);
		target->addVirtualObject(fish_copy);

		fishes.push_back(fish_copy);
	}

	flock->initializeStartPositions(1.0f, glm::vec3(0.0f, 2.0f, 0.0f));

	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsListener(flock));
	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsSwimCycleListener(flock));
	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsAvoidanceListener(flock));

}

/**
 * create a RenderPass that renders the boids into the provided FrameBufferObject
 */
RenderPass* createGBufferBoidRenderPass(FrameBufferObject* gbuffer)
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
	gbufferBoidRenderPass = new GBufferRenderPass( animatedFishGBufferShader, gbuffer );
	gbufferBoidRenderPass->setClearDepthBufferBit(false);

	// add Fish Objects as initial graphics components to be rendered
	for (unsigned int i = 0; i < FishBoidFeature::fishes.size(); i++) {
		gbufferBoidRenderPass->addInitialGraphicsComponent(
				FishBoidFeature::fishes[i]);
	}

	return gbufferBoidRenderPass;
}

}
#endif
