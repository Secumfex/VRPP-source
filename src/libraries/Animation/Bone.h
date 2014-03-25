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
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Bone {
public:
	Bone(std::string name = "default");
	virtual ~Bone();

	void setOffsetMatrix(glm::mat4 offsetmatrix);
	std::string getName();

protected:
	std::string mName;
	std::vector<Bone> children;
	glm::mat4 mOffsetMatrix;
};

#endif /* BONE_H_ */
