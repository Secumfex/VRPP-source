#ifndef FEATUREBOIDS_H
#define FEATUREBOIDS_H
#include "PlaceHolderListeners.h"
#include <Animation/Flock.h>

namespace FishBoidFeature
{
void createObjects( ApplicationState* target ){

	VirtualObject *fish = target->createVirtualObject(RESOURCES_PATH "/animation_test/fish.dae", VirtualObjectFactory::OTHER, 1.0f, 0, false);

	Flock* myFlock = new Flock();

	glm::mat4 trans = glm::rotate(glm::mat4(), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(0.05f));

	myFlock->addBoid(fish, trans);

	unsigned int i;
	for (i = 0; i < 25; ++i) {
		VirtualObject *fish_copy = new VirtualObject(fish);
		myFlock->addBoid(fish_copy, trans);
		target->addVirtualObject(fish_copy);
	}

	myFlock->initializeStartPositions(5.0f, glm::vec3(0.0f, 2.0f, 0.0f));

	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsListener(myFlock));
	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsSwimCycleListener(myFlock));
	target->attachListenerOnBeginningProgramCycle(new UpdateBoidsAvoidanceListener(myFlock));

}



}
#endif
