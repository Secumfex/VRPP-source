/*
 * Flock.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#include <Animation/Flock.h>

Flock::Flock() {
	srand(time(0));

}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}
void Flock::addBoid(VirtualObject *vo, glm::mat4 basePosition){
	mBoids.push_back(vo);
	mBasePositions.push_back(basePosition);
}


std::vector<VirtualObject*> Flock::getNeighbors(VirtualObject *vo){
	std::vector<VirtualObject*> neighbors;
	unsigned int i;

	glm::vec3 vo_pos = vo->physicsComponent->getPosition();

	for (i = 0; i < mBoids.size(); ++i) {
		glm::vec3 temp_pos = mBoids[i]->physicsComponent->getPosition();

		if(glm::vec3(temp_pos  - vo_pos).length() < NEIGHBORHOOD)
			neighbors.push_back(mBoids[i]);
	}

	return neighbors;
}

void Flock::initializeStartPositions(float maxDistance, glm::vec3 startPosition){
	unsigned int i;

	for (i = 0; i < mBoids.size(); ++i){
		float x = startPosition.x + ((rand()/RAND_MAX) * maxDistance);
		float y = startPosition.y + ((rand()/RAND_MAX) * maxDistance);
		float z = startPosition.z + ((rand()/RAND_MAX) * maxDistance);

		mBoids[i]->physicsComponent->setPosition(x, y, z);
	}
}

void Flock::update(float t){
	unsigned int i;

	std::vector<btVector3> next_velocities;

	for (i = 0; i < mBoids.size(); ++i){

		VirtualObject* vo_temp = mBoids[i];
		std::vector<VirtualObject*> neightbors = getNeighbors(vo_temp);

		btVector3 v;
		next_velocities.push_back(v);
	}
}

btVector3 Flock::getSeparation(std::vector<VirtualObject*> neighbors){
	btVector3 v = btVector3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {

	}

	return v;
}
btVector3 Flock::getAllignment(std::vector<VirtualObject*> neighbors){
	btVector3 v = btVector3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {

	}

	return v;
}
btVector3 Flock::getCohesion(std::vector<VirtualObject*> neighbors){
	btVector3 v = btVector3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {

	}

	return v;
}
