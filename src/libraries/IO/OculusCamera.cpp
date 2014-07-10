/*
 * OculusCamera.cpp
 *
 *  Created on: 14.04.2014
 *      Author: Arend
 */

#include <IO/OculusCamera.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

OculusCamera::OculusCamera(Oculus* oculus) {
	this->oculus = oculus;
	eye = OVR::Util::Render::StereoEye_Center;
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

	// adjust view matrix if eye parameter is set
	if ( eye != OVR::Util::Render::StereoEye_Center )
	{
		float offset = oculus->getStereoConfig().GetIPD() * 0.5f;

		if ( eye == OVR::Util::Render::StereoEye_Right)
		{
			offset = - offset;
		}

		accumulatedViewMatrix = glm::translate(offset, 0.0f, 0.0f) * accumulatedViewMatrix;
	}

	return accumulatedViewMatrix;
}

glm::mat4* OculusCamera::getViewMatrixPointer()
{
	return &accumulatedViewMatrix;
}

void OculusCamera::setEye(OVR::Util::Render::StereoEye eye)
{
	this->eye = eye;
}
OVR::Util::Render::StereoEye OculusCamera::getEye()
{
	return eye;
}
