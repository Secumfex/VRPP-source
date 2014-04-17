/*
 * Bone.h
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#ifndef BONE_H_
#define BONE_H_

#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>

	/*! @brief Bone.
	 *
	 *	a bone is an object that describes an animation for a vertex group of a mesh
	 */

class Bone {
public:

	/** \brief constructor
	*
	* creates a node with a name
	* @param  std::string name
	*/

	Bone(std::string name = "default");

	/** \brief destructor
	*
	* clears the allocated memory.
	*/

	virtual ~Bone();

	/** \brief setter
	*
	* sets the Bone's offset transformation.
	*
	* @param glm::mat4 offsetmatrix : new offsetmatrix
	*/

	void setOffsetMatrix(glm::mat4 offsetmatrix);

	/** \brief setter
	*
	* sets the Bone's inverse scene transformation.
	*
	* @param glm::mat4 inversematrix : new inverse matrix
	*/

	void setInverseSceneMatrix(glm::mat4 inversematrix);

	/** \brief setter
	*
	* sets the Bone's animation transformation.
	*
	* @param glm::mat4 animationmatrix : new animation matrix
	*/

	void setAnimationMatrix(glm::mat4 animationmatrix);

	/** \brief getter
	*
	* @return the bone's offsetmatrix
	*/

	glm::mat4 getOffsetMatrix();

	/** \brief getter
	*
	* @return the bone's inverse scene matrix
	*/

	glm::mat4 getInverseMatrix();

	/** \brief getter
	*
	* @return the bone's animation matrix
	*/

	glm::mat4 getAnimationMatrix();

	/** \brief getter
	*
	* @return the bone's combined matrices for a final bone transformation
	*/

	glm::mat4 getBoneMatrix();

	/** \brief getter
	*
	* @return the bone's name
	*/

	std::string getName();

protected:
	std::string mName;/**< bone's name */

	glm::mat4 mOffsetMatrix;/**< bone's offsetmatrix */
	glm::mat4 mInverseMatrix;/**< bone's inverse scene matrix */
	glm::mat4 mAnimationMatrix;/**< bone's animation */

};

#endif /* BONE_H_ */
