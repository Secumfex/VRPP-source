/*
 * Frustum.cpp
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#include "Visuals/Frustum.h"

Frustum::Frustum() {
	mProjectionMatrix = glm::perspective(40.0f, 1.0f, 0.1f, 100.f);

}

Frustum::~Frustum() {
	// TODO Auto-generated destructor stub
}

void Frustum::setProjectionMatrix(float fovy, float aspect, float near, float far){

	mProjectionMatrix = glm::perspective(fovy, aspect, near, far);

	float fovx = fovy / aspect;

	float nfovy = (fovy * near) / far ;
	float nfovx = (fovx * near) / far ;


	glm::vec3 n_d_l = glm::vec3(-nfovx/2, -nfovy/2, near);
	glm::vec3 n_d_r = glm::vec3(nfovx/2, -nfovy/2, near);
	glm::vec3 n_u_l = glm::vec3(-nfovx/2, nfovy/2, near);
	glm::vec3 n_u_r = glm::vec3(nfovx/2, nfovy/2, near);
	glm::vec3 f_d_l = glm::vec3(-fovx/2, -fovy/2, far);
	glm::vec3 f_d_r = glm::vec3(fovx/2, -fovy/2, far);
	glm::vec3 f_u_l = glm::vec3(-fovx/2, fovy/2, far);
	glm::vec3 f_u_r = glm::vec3(fovx/2, fovy/2, far);



}

glm::mat4 Frustum::getProjectionMatrix(){
	return mProjectionMatrix;
}
