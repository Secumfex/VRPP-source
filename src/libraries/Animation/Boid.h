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

#include "Visuals/VirtualObjectFactory.h"

	/*! @brief Boid.
	 *
	 *	the boid is part of a flock. it contains a virtual object, a world position and a velocity-vector.
	 */

class Boid {

public:
	/** \brief constructor
	*
	* creates a boid with a given virtual object.
	* @param vo VirtualObject*
	*/
	Boid(VirtualObject* vo);

	/** \brief destructor
	*
	* clears the allocated memory.
	*/
	virtual ~Boid();


	/** \brief setter
	*
	* sets the base transformation of the Boid's VirtualObject.
	*
	* @param glm::mat4 mat : new basic position/size/rotation
	*/

	void setBaseMatrix(glm::mat4 mat);

	/** \brief setter
	*
	* sets/changes the world position of a Boid.
	*
	* @param glm::vec3 pos : new position
	*/

	void setPosition(glm::vec3 pos);

	/** \brief setter
	*
	* sets/changes the velocity of a Boid.
	*
	* @param glm::vec3 vel : new velocity
	*/

	void setVelocity(glm::vec3 vel);

	/** \brief setter
	*
	* sets/changes the VirtualObject* of a Boid.
	*
	* @param VirtualObject* vo : new virtualobject
	*/

	void setVirtualObject(VirtualObject* vo);

	/** \brief getter
	*
	* @return the virtualobject pointer of this boid
	*/

	VirtualObject* getVirtualObject();

	/** \brief getter
	*
	* @return a glm vec 3, the position of the boid
	*/

	glm::vec3 getPosition();

	/** \brief getter
	*
	* @return a glm vec 3, the velocity of the PhysicsComponent
	*/

	glm::vec3 getVelocity();

	/** \brief getter
	*
	* @return a glm mat4, the base transformation of this boid
	*/

	glm::mat4 getBasePosition();



protected:

	VirtualObject* mVirtualObject;/**< virtualobject pointer */

	glm::mat4 mBaseMatrix;/**< the base transformation of the vo in order to act like a boid */
	glm::vec3 mPosition;/**< the world position */
	glm::vec3 mVelocity;/**< the velocity */


};

#endif /* BOID_H_ */
