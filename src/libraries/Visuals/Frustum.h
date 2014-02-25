/*
 * Frustum.h
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "IO/Camera.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Frustum {
public:
	Frustum();
	virtual ~Frustum();

	void setProjectionMatrix(float fovy, float aspect, float near, float far);
	glm::mat4 getProjectionMatrix();

private:
	Camera *mCam;
	btCollisionShape *mFrustum;
	glm::mat4 mProjectionMatrix;
};

#endif /* FRUSTUM_H_ */
