/*
 * Flock.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#include <Animation/Flock.h>

Flock::Flock() {
	srand(time(0));
	startVelocity = glm::vec3(1.0f, 0.0f, 0.0f);
	startBtVelocity = btVector3(1.0f, 0.0f, 0.0f);

}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}
void Flock::addBoid(VirtualObject *vo, glm::mat4 basePosition){
	mBoids.push_back(vo);
	mBasePositions.push_back(basePosition);
	vo->getPhysicsComponent()->getRigidBody()->setLinearVelocity(startBtVelocity);
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
	float delta_time = IOManager::getInstance()->getDeltaTime();

	for (i = 0; i < mBoids.size(); ++i){

		VirtualObject* vo_temp = mBoids[i];
		std::vector<VirtualObject*> neightbors = getNeighbors(vo_temp);

		btVector3 v;
		next_velocities.push_back(v);
	}
	for (i = 0; i < mBoids.size(); ++i){
		VirtualObject* vo_temp = mBoids[i];
		btVector3 v_temp = mBoids[i]->getPhysicsComponent()->getRigidBody()->getLinearVelocity();
		v_temp += next_velocities[i];
		mBoids[i]->getPhysicsComponent()->getRigidBody()->setLinearVelocity(v_temp);
		v_temp *= delta_time;

		glm::vec3 v_temp01 = glm::vec3(v_temp.x(), v_temp.y(), v_temp.z());
		glm::quat rotation = getRotation(v_temp01);

		v_temp01 += vo_temp->getPhysicsComponent()->getPosition();
		vo_temp->getPhysicsComponent()->setPosition(v_temp01.x, v_temp01.y, v_temp01.z);
	}
}

btVector3 Flock::getSeparation(std::vector<VirtualObject*> neighbors){
	btVector3 v = btVector3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {
	btVector3 v_temp = neighbors[i]->getPhysicsComponent()->getRigidBody()->getLinearVelocity();

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

glm::quat Flock::getRotation(glm::vec3 velocity){
	velocity = glm::normalize(velocity);

	glm::vec3 axis =

}
