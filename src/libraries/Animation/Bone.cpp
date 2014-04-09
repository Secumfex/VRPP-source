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
	std::cout << glm::to_string(offsetmatrix) << std::endl;
	std::cout << glm::to_string(glm::translate(glm::mat4(), glm::vec3(5.0, 5.0, 5.0))) << std::endl;

	mOffsetMatrix = offsetmatrix;
}

void Bone::setBindPose(glm::vec3 trans, glm::quat rot, glm::vec3 scale){
	mTranslation = trans;
	mRotation = rot;
	mScale = scale;

	glm::mat4 offsetmatrix_alt = glm::translate(glm::mat4(), trans) * glm::mat4_cast(rot) * glm::scale(glm::mat4(), scale);

	std::cout << "GO " << mName << std::endl;
	std::cout << glm::to_string(offsetmatrix_alt) << std::endl;
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
	//	return glm::inverse(mOffsetMatrix) * mAnimationMatrix;
	//	return glm::mat4() * glm::inverse(mOffsetMatrix) ;
//	return mOffsetMatrix * mAnimationMatrix;
		return mOffsetMatrix * glm::mat4();
	//	return mOffsetMatrix ;
}
