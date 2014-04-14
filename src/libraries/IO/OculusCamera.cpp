/*
 * OculusCamera.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Arend
 */

#include <IO/OculusCamera.h>
#include <glm/gtc/quaternion.hpp>

OculusCamera::OculusCamera(Oculus* oculus) {
	this->oculus = oculus;
}

OculusCamera::~OculusCamera() {
}

glm::mat4 OculusCamera::getViewMatrix()
{
	Camera::getViewMatrix();
	OVR::Quatf orientation = oculus->GetOrientation();

	glm::quat rotationQuat((-1.0f) *  orientation.w, orientation.x,orientation.y,orientation.z);
	glm::mat4 rotation = glm::mat4_cast(rotationQuat);

	accumulatedViewMatrix =  rotation * viewMatrix;

	return accumulatedViewMatrix;
}

glm::mat4* OculusCamera::getViewMatrixPointer()
{
	return &accumulatedViewMatrix;
}
