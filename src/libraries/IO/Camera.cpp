#include "Camera.h"

#define PI 3.14159265f

Camera::Camera(){
	xPosition = 0.0;
	yPosition = 0.0;
	zPosition = 5.0;

	// Initial position : on +Z
	position = glm::vec3(xPosition, yPosition, zPosition);

	// Initial horizontal angle : toward -Z
	phi = PI;
	// Initial vertical angle : none
	theta = 0.0f;

	speedRight = 0.0f;
	speedForward = 0.0f;

	//compute initial View Direction vector
	updateViewDirection();
}

Camera::~Camera(){}


/* GETTER AND SETTER BEGIN */
float Camera::getX(){
	return xPosition;
}

void Camera::setX(float updateX){
	xPosition = updateX;
	position.x = xPosition;
}

float Camera::getY(){
	return yPosition;
}

void Camera::setY(float updateY){
	yPosition = updateY;
	position.y = yPosition;
}

float Camera::getZ(){
	return zPosition;
}

void Camera::setZ(float updateZ){
	zPosition = updateZ;
	position.z = zPosition;
}

float Camera::getPhi(){
	return phi;
}

void Camera::setPhi(float updatePhi){
	phi = updatePhi;
	updateViewDirection();
}

float Camera::getTheta(){
	return theta;
}

void Camera::setTheta(float updateTheta){
	theta = updateTheta;
	updateViewDirection();
}

void Camera::setSpeedRight(float speed){
	speedRight = speed;
}
void Camera::setSpeedForward(float speed){
	speedForward = speed;
}

void Camera::updatePosition(float deltaTime){
	glm::vec3 gotPosition = getPosition();
	gotPosition += getViewDirection() * deltaTime * speedForward;
	gotPosition += getRight() * deltaTime * speedRight;
	setPosition(gotPosition);
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
	position = glm::vec3(x,y,z);
}

void Camera::setPosition(glm::vec3 newPos){
	position = newPos;
}
/* GETTER AND SETTER END */

// Direction : Spherical coordinates to Cartesian coordinates conversion
void Camera::updateViewDirection(){
	clampPhiTheta();
	direction = glm::vec3(	cos(theta) * sin(phi),
							sin(theta),
							cos(phi) * cos(theta)	);
	direction = glm::normalize(direction);
}

// assumption: direction is normalized
void Camera::updatePhiTheta(){
	theta 	= std::atan2(direction.y,std::sqrt(direction.x *direction.x + direction.z * direction.z)); // inclination 
	phi 	= std::atan2(direction.x, direction.z); // rotation
}

	// Right vector
glm::vec3 Camera::getRight(){
	glm::vec3 right = glm::vec3(	sin(phi - PI / 2.0f),
									0,
									cos(phi - PI / 2.0f));
	right = glm::normalize(right);
	return right;
}
	// Up vector
glm::vec3 Camera::getUp(){
	glm::vec3 up = glm::cross(getRight() , direction);
	up = glm::normalize(up);
	return up;
}

glm::mat4 Camera::getViewMatrix(){
	// Camera matrix
	return glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

void Camera::setDirection(glm::vec3 dir){
	direction = glm::normalize(dir);
	updatePhiTheta();	// update phi & theta by evaluating the new direction
}

void Camera::setCenter(glm::vec3 center){
	direction = center - position;
	direction = glm::normalize(direction);
	updatePhiTheta();	// update phi & theta by evaluating the new direction
}

void Camera::clampPhiTheta(){
	phi = std::fmod (phi , 2.0*PI);

	if (theta >= PI / 2.0){
		theta =  PI / 2.0 - 0.001;
	}
	if (theta <= -PI / 2.0){
		theta = -PI / 2.0 + 0.001;
	}
}