#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

using namespace std;

/*! @brief Camera here means a first person camera.
 *
 *
 */
class Camera{
protected:
	glm::vec3 position;
	glm::vec3 direction;

	float xPosition;
	float yPosition;
	float zPosition;
	float phi;		// rotation, horizontal
	float theta;	// inclination, vertical
	float speedRight;
	float speedForward;

	glm::vec3 getUp();

	inline void clampPhiTheta();	// clip Phi, Theta into [-PI; PI] and [0, 2*PI]

public:
	Camera();	//!< constructor
	~Camera();	//!< destructor

	/* GETTER AND SETTER BEGIN */
	// TODO remove unnecessary methods
	float getX();
	void setX(float updateX);
	float getY();
	void setY(float updateY);
	float getZ();
	void setZ(float updateZ);

	float getPhi();		//!< get rotational angle (yaw), always within [0,2*PI]
	void setPhi(float updatePhi);	//!< set phi to provided float, will be clamped to [0,2*PI]
	float getTheta();	//!< get inclinational angle (pitch), always within ]-PI , PI[
	void setTheta(float updateTheta);	//!< set theta to provided float, will be clamped to ] -PI, PI []
	void setSpeedRight(float speed);
	void setSpeedForward(float speed);
	virtual void updatePosition(float deltaTime);

	float getSpeedRight();
	float getSpeedForward();
	glm::vec3 getRight();
	glm::vec3 getViewDirection();
	glm::vec3 getPosition();
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(glm::vec3 newPos);

	void setDirection(glm::vec3 dir);
	void setCenter(glm::vec3 center);
	/* GETTER AND SETTER END */


	inline void updateViewDirection();		//!< compute ViewDirection from Phi and Theta
	inline void updatePhiTheta();			//!< compute Phi and Theta from View Direction

	glm::mat4 getViewMatrix();		//!< compute ViewMatrix
};

#endif
