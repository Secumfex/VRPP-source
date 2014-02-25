/*
 * Frustum.cpp
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#include "Visuals/Frustum.h"

Frustum::Frustum() {
	mProjectionMatrix = glm::perspective(40.0f, 1.0f, 0.1f, 100.f);
	std::cout << "WURSTSALAT" << std::endl;

}

Frustum::~Frustum() {
	// TODO Auto-generated destructor stub
}

void Frustum::setProjectionMatrix(float fovy, float aspect, float near, float far){
	std::cout << "hier ist er 02" << std::endl;
	glm::mat4 mat = glm::perspective(fovy, aspect, near, far);
	std::cout << "hier ist er 03" << std::endl;
	mProjectionMatrix = glm::perspective(40.0f, 1.0f, 0.1f, 100.f);

	std::cout << "hier ist er 04" << std::endl;
}

glm::mat4 Frustum::getProjectionMatrix(){
	return mProjectionMatrix;
}
