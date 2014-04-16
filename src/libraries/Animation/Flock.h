/*
 * Flock.h
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#ifndef FLOCK_H_
#define FLOCK_H_

#define NEIGHBORHOOD 2

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

private:

	glm::vec3 getSeparation(std::vector<Boid*> neighbors, Boid* boid);
	glm::vec3 getAllignment(std::vector<Boid*> neighbors, Boid* boid);
	glm::vec3 getCohesion(std::vector<Boid*> neighbors, Boid* boid);
	void updateAnimations(float t);


	glm::vec3 startVelocity;
	btVector3 startBtVelocity;
	std::vector<Boid*> mBoids;
	std::vector<glm::mat4> mBaseTransform;

};

#endif /* FLOCK_H_ */
