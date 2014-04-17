/*
 * Flock.h
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#ifndef FLOCK_H_
#define FLOCK_H_

#define NEIGHBORHOOD 1

#include "Animation/Boid.h"
#include <cstdlib>
#include <time.h>
#include <IO/IOManager.h>

class Flock {
public:
	Flock();
	virtual ~Flock();

	void addBoid(VirtualObject *vo, glm::mat4 basePosition = glm::mat4());
	std::vector<Boid*> getNeighbors(Boid* boid);
	void initializeStartPositions(float maxDistance, glm::vec3 startPosition);
	void update(float t);
	glm::quat getRotation(glm::vec3 velocity);
	std::vector<Boid*> getBoids();
	void setPlaceToGo(glm::vec3 place);


private:

	glm::vec3 clampVelocity(glm::vec3 velocity);
	glm::vec3 getPlace(Boid* boid);
	glm::vec3 getSeparation(std::vector<Boid*> neighbors, Boid* boid);
	glm::vec3 getAllignment(std::vector<Boid*> neighbors, Boid* boid);
	glm::vec3 getCohesion(std::vector<Boid*> neighbors, Boid* boid);
	void updateAnimations(float t);

	float mSpeedlimit;
	glm::vec3 mPlaceToGo;
	glm::vec3 startVelocity;
	btVector3 startBtVelocity;
	std::vector<Boid*> mBoids;


};

#endif /* FLOCK_H_ */
