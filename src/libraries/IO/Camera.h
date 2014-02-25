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
private:
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

	float getPhi();		//!< @todo please describe this further
	void setPhi(float updatePhi);	//!< @todo please use "[at]param" to describe which constraints exist to the parameter
	float getTheta();	//!< @todo please describe this further
	void setTheta(float updateTheta);	//!< @todo please use "[at]param" to describe which constraints exist to the parameter
	void setSpeedRight(float speed);
	void setSpeedForward(float speed);
	void updatePosition(float deltaTime);

	glm::vec3 getRight();
	glm::vec3 getViewDirection();
	glm::vec3 getPosition();
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 newPos);

	void setDirection(glm::vec3 dir);
	void setCenter(glm::vec3 center);
	/* GETTER AND SETTER END */


	inline void updateViewDirection();		//!< compute ViewDirection from Phi and Theta
	inline void updatePhiTheta();			//!< compute Phi and Theta from View Direction

	glm::mat4 getViewMatrix();		//!< compute ViewMatrix
};

#endif
