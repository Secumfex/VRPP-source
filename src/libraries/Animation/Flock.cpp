/*
 * Flock.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#include <Animation/Flock.h>

Flock::Flock() {
	srand(time(0));
	startVelocity = glm::vec3(0.001f, 0.0f, 0.0f);
	setPlaceToGo(glm::vec3(0.0f, 0.0f, 0.0f));
	setPlaceToAvoid(glm::vec3(0.0f, 0.0f, 0.0f));
	mSpeedlimit = 0.3f;
}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}
void Flock::addBoid(VirtualObject *vo, glm::mat4 baseTransformation){
	Boid* myBoid = new Boid(vo);
	myBoid->setBaseMatrix(baseTransformation);
	myBoid->setVelocity(startVelocity);

	mBoids.push_back(myBoid);
}


std::vector<Boid*> Flock::getNeighbors(Boid* boid){
	std::vector<Boid*> neighbors;
	unsigned int i;

	glm::vec3 vo_pos = boid->getPosition();
	glm::vec3 vo_vel = boid->getVelocity();

	vo_vel *= (1.0f / glm::length(vo_vel));

	for (i = 0; i < mBoids.size(); ++i) {
		glm::vec3 temp_pos = mBoids[i]->getPosition() - vo_pos;

		if(glm::length(temp_pos) < NEIGHBORHOOD && boid != mBoids[i]){
			temp_pos *= (1.0f / glm::length(temp_pos));

			if(glm::dot(temp_pos, vo_vel) > 0.0f)
				neighbors.push_back(mBoids[i]);}
	}

	return neighbors;
}

void Flock::initializeStartPositions(float maxDistance, glm::vec3 startPosition){
	unsigned int i;

	for (i = 0; i < mBoids.size(); ++i){
		float x = startPosition.x + ((1.0f * rand()/RAND_MAX) * maxDistance);
		float y = startPosition.y + ((1.0f * rand()/RAND_MAX) * maxDistance);
		float z = startPosition.z + ((1.0f * rand()/RAND_MAX) * maxDistance);

		x = (x * 2) - maxDistance;
		y = (y * 2) - maxDistance;
		z = (z * 2) - maxDistance;

		mBoids[i]->setPosition(glm::vec3(x, y, z));
	}
}

void Flock::update(float t){
	unsigned int i;

	updateAnimations(t);

	std::vector<glm::vec3> next_velocities;
	float delta_time = IOManager::getInstance()->getDeltaTime();

	for (i = 0; i < mBoids.size(); ++i){

		Boid* boid_temp = mBoids[i];
		std::vector<Boid*> neightbors = getNeighbors(boid_temp);

		glm::vec3 v = getAllignment(neightbors, boid_temp) * 0.5f;
		//		glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);
		v += getCohesion(neightbors, boid_temp) * -0.8f;
		v += getSeparation(neightbors, boid_temp) * 1.5f;
		v += getPlaceToGoVector(boid_temp) * 1.0f;
		v += getPlaceToAvoidVector(boid_temp) * 1.0f;
		next_velocities.push_back(v);

	}


	for (i = 0; i < mBoids.size(); ++i){
		Boid* boid_temp = mBoids[i];
		glm::vec3 v_temp = mBoids[i]->getVelocity();
		v_temp += next_velocities[i];
		v_temp = clampVelocity(v_temp);

		mBoids[i]->setVelocity(v_temp);


		glm::vec3 v_temp01 = v_temp * delta_time;

		glm::quat rotation = getRotation(boid_temp);
		//				glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f);


		v_temp01 += boid_temp->getPosition();
		boid_temp->setPosition(v_temp01);

		glm::mat4 transformation = glm::translate(glm::mat4(), v_temp01) * glm::mat4_cast(rotation) * boid_temp->getBasePosition();

		boid_temp->getVirtualObject()->setModelMatrix(transformation);
	}
}

glm::vec3 Flock::getCohesion(std::vector<Boid*> neighbors, Boid* boid){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	if(neighbors.size() <= 0)
		return v;

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {
		glm::vec3 v_temp = neighbors[i]->getPosition();
		v += v_temp;
	}
	v = v * (1.0f/neighbors.size());

	return (v - boid->getPosition()) * 0.01f;
}

glm::vec3 Flock::getAllignment(std::vector<Boid*> neighbors, Boid* boid){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	if(neighbors.size() <= 0)
		return v;

	glm::vec3 v1 = boid->getVelocity();

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {
		v += neighbors[i]->getVelocity();
	}
	v = v * (1.0f/(neighbors.size() * 1.0f));

	return (v - v1) * 0.125f;
}
glm::vec3 Flock::getSeparation(std::vector<Boid*> neighbors, Boid* boid){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 v1 = boid->getPosition();

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {
		glm::vec3 v2 = neighbors[i]->getPosition() - v1;
		if(glm::length(v2) <= 0.2f)
			v = v - v2;
	}

	return v * 1.5f;
}

glm::quat Flock::getRotation(Boid* boid){

	glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f);

	glm::vec3 velocity = mPlaceToGo - boid->getPosition();

	velocity = 0.25f * velocity + 0.75f * boid->getVelocity();

	if(glm::length(velocity) == 0.0f)
		return rotation;

	velocity *= (1.0f / glm::length(velocity));
	glm::vec3 start = startVelocity * (1.0f / glm::length(startVelocity));

	if(velocity == start)
		return rotation;

	if(velocity == -start)
		return glm::quat (-1.0f, 0.0f, 0.0f, 0.0f);

	glm::vec3 axis = glm::cross(start, velocity);
	axis /= glm::length(axis);

	float angle = glm::dot(velocity, start);
	angle = glm::acos(angle);

	glm::mat4 rot_matrix = glm::rotate(glm::mat4(), glm::degrees(angle), axis);

	rotation = glm::quat_cast(rot_matrix);

	return rotation;
}

void Flock::updateAnimations(float t){
	unsigned int i;
	AnimationLoop *ani = VirtualObjectFactory::getInstance()->createNonAssimpVO()->getAnimation();
	for (i = 0; i < mBoids.size(); ++i) {
		if(ani != mBoids[i]->getVirtualObject()->getAnimation()){
			ani = mBoids[i]->getVirtualObject()->getAnimation();
			ani->updateNodes(t);
		}

	}
}
std::vector<Boid*> Flock::getBoids(){
	return mBoids;
}
void Flock::setPlaceToGo(glm::vec3 place){
	mPlaceToGo = place;
}
void Flock::setPlaceToAvoid(glm::vec3 place){
	mPlaceToAvoid = place;
}
glm::vec3 Flock::getPlaceToGoVector(Boid* boid){
	return glm::vec3(mPlaceToGo - boid->getPosition()) * 0.001f;
}
glm::vec3 Flock::getPlaceToAvoidVector(Boid* boid){



	glm::vec3 vec = glm::vec3(boid->getPosition() - mPlaceToAvoid);
	float length = glm::length(vec);

	if(length > 2.0f || length <= 0.0f)
		return glm::vec3(0.0f, 0.0f, 0.0f);

	vec = vec * (1.0f / (length));

	return vec * 0.05f;
}

glm::vec3 Flock::clampVelocity(glm::vec3 velocity){
	mSpeedlimit = glm::abs(mSpeedlimit);
	if(glm::length(velocity) > mSpeedlimit)
		velocity = (velocity / glm::length(velocity)) * mSpeedlimit;

	return velocity;
}
