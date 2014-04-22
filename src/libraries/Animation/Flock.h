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

	/*! @brief Flock.
	 *
	 *	a flock is a group of boids interacting together. they follow a certain point and avoid others.
	 */

class Flock {
public:

	/** \brief constructor
	*
	* Default constructor with no values.
	*/

	Flock();

	/** \brief destructor
	*
	* clears the allocated memory.
	*/

	virtual ~Flock();

	/** \brief adds a Boid* with a VirtualObject* and a baseTransformation
	*
	* @param VirtualObject *vo : vo reprentant for Boid
	* @param glm::mat4 baseTransformation : basic position/size/rotation for Boid
	*/

	void addBoid(VirtualObject *vo, glm::mat4 baseTransformation = glm::mat4());

	/** \brief getter
	*
	* @param Boid* boid : a boid who's neighborhood is being calculated
	* @return a Boid's neighborhood
	*/

	std::vector<Boid*> getNeighbors(Boid* boid);

	/** \brief puts Boids at random positions around a certain point
	*
	* @param float maxDistance : the distance, a boid can be away from the startPosition
	* @param glm::vec3 startPosition : a position the boids start around
	*/

	void initializeStartPositions(float maxDistance, glm::vec3 startPosition);

	/** \brief updates the boid's position and the vo's animation
	*
	* @param float t : animation time
	*/

	void update(float t);

	/** \brief getter
	*
	* @return all boids of this flock
	*/

	std::vector<Boid*> getBoids();

	/** \brief setter
	*
	* @param vec3 place : a position the boids will follow
	*/

	void setPlaceToGo(glm::vec3 place);

	/** \brief setter
	*
	* @param vec3 place : a position the boids will avoid
	*/

	void setPlaceToAvoid(glm::vec3 place);


private:

	glm::quat getRotation(Boid* boid);/**< calculates the rotation for the current velocity vector */
	glm::vec3 clampVelocity(glm::vec3 velocity);/**< clamps the velocity vectors to a speedlimit */
	glm::vec3 getPlaceToGoVector(Boid* boid);/**< calculates a vector for the boids to follow */
	glm::vec3 getPlaceToAvoidVector(Boid* boid);/**< calculates a vector for the boids to follow */
	glm::vec3 getSeparation(std::vector<Boid*> neighbors, Boid* boid);/**< calculates the 1.rule of boids */
	glm::vec3 getAllignment(std::vector<Boid*> neighbors, Boid* boid);/**< calculates the 2.rule of boids */
	glm::vec3 getCohesion(std::vector<Boid*> neighbors, Boid* boid);/**< calculates the 3.rule of boids */
	void updateAnimations(float t);/**< updates the boids animations */

	float mSpeedlimit;/**< a maximum length for a velocity vector*/
	glm::vec3 mPlaceToGo;/**< a world position the boids will follow */
	glm::vec3 mPlaceToAvoid;/**< a world position the boids will avoid */
	glm::vec3 startVelocity;/**< a velocity vector, all boids will have in the first frame */
	std::vector<Boid*> mBoids;/**< array of boids */


};

#endif /* FLOCK_H_ */
