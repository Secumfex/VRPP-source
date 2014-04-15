/*
 * Flock.h
 *
 *  Created on: 14.04.2014
 *      Author: Raphimulator
 */

#ifndef FLOCK_H_
#define FLOCK_H_

#define NEIGHBORHOOD 2

#include <Visuals/VirtualObject.h>
#include <cstdlib>
#include <time.h>
#include <IO/IOManager.h>

class Flock {
public:
	Flock();
	virtual ~Flock();

	void addBoid(VirtualObject *vo, glm::mat4 basePosition = glm::mat4());
	std::vector<VirtualObject*>getNeighbors(VirtualObject *vo);
	void initializeStartPositions(float maxDistance, glm::vec3 startPosition);
	void update(float t);
	glm::quat getRotation(glm::vec3 velocity);

private:

	btVector3 getSeparation(std::vector<VirtualObject*> neighbors);
	btVector3 getAllignment(std::vector<VirtualObject*> neighbors);
	btVector3 getCohesion(std::vector<VirtualObject*> neighbors);

	glm::vec3 startVelocity;
	btVector3 startBtVelocity;
	std::vector<VirtualObject*> mBoids;
	std::vector<glm::mat4> mBasePositions;

};

#endif /* FLOCK_H_ */
