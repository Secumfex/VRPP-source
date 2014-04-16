/*
 * Flock.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#include <Animation/Flock.h>

Flock::Flock() {
	srand(time(0));
	startVelocity = glm::vec3(0.1f, 0.0f, 0.0f);
	startBtVelocity = btVector3(0.1f, 0.0f, 0.0f);

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

	for (i = 0; i < mBoids.size(); ++i) {
		glm::vec3 temp_pos = mBoids[i]->getPosition();

		if(glm::vec3(temp_pos  - vo_pos).length() < NEIGHBORHOOD && boid != mBoids[i])
			neighbors.push_back(mBoids[i]);
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

		cout << x << "/" << y << "/" << z << " LOL" << rand() << endl;

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

		glm::vec3 v;
		next_velocities.push_back(v);
	}


	for (i = 0; i < mBoids.size(); ++i){
		Boid* boid_temp = mBoids[i];
		glm::vec3 v_temp = mBoids[i]->getVelocity();
		v_temp += next_velocities[i];
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

glm::vec3 Flock::getSeparation(std::vector<Boid*> neighbors){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {
		glm::vec3 v_temp = neighbors[i]->getPosition();
		v += v_temp;
	}
	v = v * (1.0f/(neighbors.size() * 1.0f));

	return v * 0.01f;
}
glm::vec3 Flock::getAllignment(std::vector<Boid*> neighbors){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {

	}

	return v;
}
glm::vec3 Flock::getCohesion(std::vector<Boid*> neighbors){
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int i;
	for (i = 0; i < neighbors.size(); ++i) {

	}

	return v;
}

glm::quat Flock::getRotation(glm::vec3 velocity){

	glm::quat rotation = glm::quat (1.0f, 0.0f, 0.0f, 0.0f);

	if(velocity.length() == 0.0f)
		return rotation;

	float min_value = std::numeric_limits<float>::min();
	cout << "blablabla v: " << glm::to_string(velocity) << " length " << velocity.length() << endl;

	velocity *= (1.0f / velocity.length());
	glm::vec3 start = glm::normalize(startVelocity);

	if(velocity == start)
		return rotation;

	glm::vec3 axis = glm::cross(velocity, start);
	cout << min_value <<" BLAAA" << glm::to_string(axis) << " von " << glm::to_string(velocity) << " und " << glm::to_string(start) << endl;
	axis = glm::normalize(axis);
	//	cout << "oder normalisieren?" << endl;

	float angle = glm::dot(velocity, start);
	axis *= glm::sin(angle) * axis;
	//	cout << "oder skalarprodukt?" << endl;

	return rotation;

	rotation = glm::quat(glm::cos(angle), axis);
	cout << "fertisch" << endl;

	return rotation;
}

void Flock::updateAnimations(float t){
	unsigned int i;
	for (i = 0; i < mBoids.size(); ++i) {
		mBoids[i]->getVirtualObject()->getAnimation()->updateNodes(t);
	}
}
