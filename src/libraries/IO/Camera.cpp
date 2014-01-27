#include "Camera.h"

#define PI 3.14159265f

Camera::Camera(){
	xPosition = 0;
	yPosition = 0;
	zPosition = 5;

	// Initial position : on +Z
	position = glm::vec3(xPosition, yPosition, yPosition);
	// Initial horizontal angle : toward -Z
	float phi = PI;
	// Initial vertical angle : none
	float theta = 0.0f;
}

Camera::~Camera(){}


/* GETTER AND SETTER BEGIN */
float Camera::getX(){
	return xPosition;
}

void Camera::setX(float updateX){
	xPosition = updateX;
}

float Camera::getY(){
	return yPosition;
}

void Camera::setY(float updateY){
	yPosition = updateY;
}

float Camera::getZ(){
	return zPosition;
}

void Camera::setZ(float updateZ){
	zPosition = updateZ;
}

float Camera::getPhi(){
	return phi;
}

void Camera::setPhi(float updatePhi){
	phi = updatePhi;
}

float Camera::getTheta(){
	return theta;
}

void Camera::setTheta(float updateTheta){
	theta = updateTheta;
}

glm::vec3 Camera::getViewDirection(){
	return direction;
}

glm::vec3 Camera::getPosition(){
	return position;
}

void Camera::setPosition(float x, float y, float z){
	xPosition = x;
	yPosition = y;
	zPosition = z;
}

void Camera::setPosition(glm::vec3 newPos){
	position = newPos;
}
/* GETTER AND SETTER END */

// Direction : Spherical coordinates to Cartesian coordinates conversion
void Camera::updateViewDirection(){
	direction = glm::vec3(	cos(theta) * sin(phi),
							sin(theta),
							cos(phi) * cos(theta)	);
	glm::normalize(direction);
}
	// Right vector
glm::vec3 Camera::getRight(){
	glm::vec3 right = glm::vec3(	sin(phi - PI / 2.0f),
									0,
									cos(phi - PI / 2.0f));
	glm::normalize(right);
	return right;
}
	// Up vector
glm::vec3 Camera::getUp(){
	glm::vec3 up = glm::cross(getRight() , direction);
	glm::normalize(up);
	return up;
}

glm::mat4 Camera::getViewMatrix(){
	// Camera matrix
	return glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		getUp()                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
