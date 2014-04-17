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
	startBtVelocity = btVector3(0.001f, 0.0f, 0.0f);
	setPlaceToGo(glm::vec3(0.0f, 0.0f, 0.0f));
	mSpeedlimit = 0.5f;
}

Flock::~Flock() {
	// TODO Auto-generated destructor stub
}
void Flock::addBoid(VirtualObject *vo, glm::mat4 basePosition){
	Boid* myBoid = new Boid(vo);
	myBoid->setBaseMatrix(basePosition);
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

			if(glm::dot(temp_pos, vo_vel) > -0.7f)
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


	std::vector<glm::vec3> next_velocities;
	float delta_time = IOManager::getInstance()->getDeltaTime();

	for (i = 0; i < mBoids.size(); ++i){

		Boid* boid_temp = mBoids[i];
		std::vector<Boid*> neightbors = getNeighbors(boid_temp);

		glm::vec3 v = getAllignment(neightbors, boid_temp);
//		glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);
		cout << "CHECK IT OUT MON " << neightbors.size()<< endl;
		cout << glm::to_string(v) << endl;
		v += getCohesion(neightbors, boid_temp);
		cout << glm::to_string(v) << endl;
		v += getSeparation(neightbors, boid_temp);
		cout << glm::to_string(v) << endl;
		v += getPlace(boid_temp);
		cout << glm::to_string(v) << endl << endl;
		next_velocities.push_back(v);

	}


	for (i = 0; i < mBoids.size(); ++i){
		Boid* boid_temp = mBoids[i];
		glm::vec3 v_temp = mBoids[i]->getVelocity();
		v_temp += next_velocities[i];
		v_temp = clampVelocity(v_temp);

		mBoids[i]->setVelocity(v_temp);


		glm::vec3 v_temp01 = v_temp * delta_time;

		//		glm::quat rotation = getRotation(v_temp);
				glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f);


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

glm::quat Flock::getRotation(glm::vec3 velocity){

	glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f);

	if(glm::length(velocity) == 0.0f)
		return rotation;

	float min_value = std::numeric_limits<float>::min();

	velocity *= (1.0f / glm::length(velocity));
	glm::vec3 start = glm::normalize(startVelocity);

	if(velocity == start)
		return rotation;

	glm::vec3 axis = glm::cross(velocity, start);
	axis = glm::normalize(axis);

	float angle = glm::dot(velocity, start);
	axis *= glm::sin(angle) * axis;

	return rotation;

	rotation = glm::quat(glm::cos(angle), axis);

	return rotation;
}

void Flock::updateAnimations(float t){
	unsigned int i;
	for (i = 0; i < mBoids.size(); ++i) {
		mBoids[i]->getVirtualObject()->getAnimation()->updateNodes(t);
	}
}
std::vector<Boid*> Flock::getBoids(){
	return mBoids;
}
void Flock::setPlaceToGo(glm::vec3 place){
	mPlaceToGo = place;
}
glm::vec3 Flock::getPlace(Boid* boid){
	return glm::vec3(mPlaceToGo - boid->getPosition()) * 0.001f;
}

glm::vec3 Flock::clampVelocity(glm::vec3 velocity){
	mSpeedlimit = glm::abs(mSpeedlimit);
	if(glm::length(velocity) > mSpeedlimit)
		velocity = (velocity / glm::length(velocity)) * mSpeedlimit;

	return velocity;
}
