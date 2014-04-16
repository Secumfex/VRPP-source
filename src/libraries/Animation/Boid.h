/*
 * Boid.h
 *
 *  Created on: 16.04.2014
 *      Author: Raphimulator
 */

#ifndef BOID_H_
#define BOID_H_

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Visuals/VirtualObject.h"

class Boid {
public:
	Boid(VirtualObject* vo);
	virtual ~Boid();

	void setBaseMatrix(glm::mat4 mat);
	void setPosition(glm::vec3 pos);
	void setVelocity(glm::vec3 vel);

	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::mat4 getBasePosition();



protected:

	VirtualObject* mVirtualObject;

	glm::mat4 mBaseMatrix;
	glm::vec3 mPosition;
	glm::vec3 mVelocity;


};

#endif /* BOID_H_ */
