/*
 * Bone.cpp
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#include <Animation/Bone.h>

Bone::Bone(std::string name) {
	mName = name;
	mOffsetMatrix = glm::mat4();
	mAnimationMatrix= glm::mat4();
}

Bone::~Bone() {
	// TODO Auto-generated destructor stub
}

void Bone::setOffsetMatrix(glm::mat4 offsetmatrix){
	std::string name = glm::to_string(glm::inverse(offsetmatrix));
	std::cout << name << std::endl;
//	mOffsetMatrix = glm::transpose(offsetmatrix);
	mOffsetMatrix = offsetmatrix;
}
std::string Bone::getName(){
	return mName;
}
void Bone::setAnimationMatrix(glm::mat4 animationmatrix){
	mAnimationMatrix = animationmatrix;
}

glm::mat4 Bone::getOffsetMatrix(){
	return mOffsetMatrix;
}

glm::mat4 Bone::getAnimationMatrix(){
	return mAnimationMatrix;
}

glm::mat4 Bone::getBoneMatrix(){
//	return glm::mat4();
	return glm::inverse(mOffsetMatrix) * mAnimationMatrix;
}
