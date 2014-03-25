/*
 * Bone.cpp
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#include <Animation/Bone.h>

Bone::Bone(std::string name) {
	// TODO Auto-generated constructor stub

}

Bone::~Bone() {
	// TODO Auto-generated destructor stub
}

void Bone::setOffsetMatrix(glm::mat4 offsetmatrix){
	mOffsetMatrix = offsetmatrix;
}
