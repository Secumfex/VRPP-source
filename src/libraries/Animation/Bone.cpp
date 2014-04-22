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

	mOffsetMatrix = offsetmatrix;
	mAnimationMatrix = glm::inverse(offsetmatrix);
}

void Bone::setInverseSceneMatrix(glm::mat4 inversematrix){
	mInverseMatrix = inversematrix;
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
glm::mat4 Bone::getInverseMatrix(){
	return mInverseMatrix;
}

glm::mat4 Bone::getAnimationMatrix(){
	return mAnimationMatrix;
}

glm::mat4 Bone::getBoneMatrix(){

	return mInverseMatrix * mAnimationMatrix * mOffsetMatrix;
}
