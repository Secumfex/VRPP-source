#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

using namespace std;

/** @brief Camera here means a first person camera.
 *
 */
class Camera{
protected:
	glm::vec3 position;		/**< !docu pls! */
	glm::vec3 direction;	/**< !docu pls! */

	float xPosition;		/**< !docu pls! */
	float yPosition;		/**< !docu pls! */
	float zPosition;		/**< !docu pls! */
	float phi;				/**< rotation, horizontal */
	float theta;			/**< inclination, vertical */
	float speedRight;		/**< !docu pls! */
	float speedForward;		/**< !docu pls! */

	/** \brief !docu pls!
	 *
	 */
	glm::vec3 getUp();

	/** \brief !docu pls!
	 *
	 * clip Phi, Theta into [-PI; PI] and [0, 2*PI]
	 */
	inline void clampPhiTheta();

public:
	/** \brief constructor
	 *
	 */
	Camera();

	/** \brief destructor
	 *
	 */
	~Camera();

	/* GETTER AND SETTER BEGIN */
	// TODO remove unnecessary methods
	/** \brief getter
	 *
	 * @return x value
	 */
	float getX();

	/** \brief setter
	 *
	 * sets/changes the x value
	 * @param updateX
	 */
	void setX(float updateX);

	/** \brief getter
	 *
	 * @return y value
	 */
	float getY();

	/** \brief setter
	 *
	 * sets/changes the y value
	 * @param updateY
	 */
	void setY(float updateY);

	/** \brief getter
	 *
	 * @return y value
	 */
	float getZ();

	/** \brief setter
	 *
	 * sets/changes the y value
	 * @param updateZ
	 */
	void setZ(float updateZ);

	/** \brief getter
	 *
	 * get rotational angle (yaw), always within [0,2*PI]
	 * @return float value
	 */
	float getPhi();

	/** \brief setter
	 *
	 * set phi to provided float, will be clamped to [0,2*PI]
	 * @param updatePhi
	 */
	void setPhi(float updatePhi);

	/** \brief getter
	 *
	 * get inclinational angle (pitch), always within ]-PI , PI[
	 * @return float value
	 */
	float getTheta();

	/** \brief setter
	 *
	 * set theta to provided float, will be clamped to ] -PI, PI []
	 * @param updateTheta
	 */
	void setTheta(float updateTheta);

	/** \brief setter
	 *
	 * sets/changes speedRight
	 * @param speed
	 */
	void setSpeedRight(float speed);

	/** \brief setter
	 *
	 * sets/changes speedForward
	 * @param speed
	 */
	void setSpeedForward(float speed);

	/** \brief !docu pls!
	 *
	 */
	virtual void updatePosition(float deltaTime);

	/** \brief getter
	 *
	 * @return speedRight
	 */
	float getSpeedRight();

	/** \brief getter
	 *
	 * @return speedForward
	 */
	float getSpeedForward();

	/** \brief getter
	 *
	 * @return right
	 */
	glm::vec3 getRight();

	/** \brief getter
	 *
	 * @return the viewDirection (direction)
	 */
	glm::vec3 getViewDirection();

	/** \brief getter
	 *
	 * @return position
	 */
	glm::vec3 getPosition();

	/** \brief setter
	 *
	 * sets/changes the x,y,and z value of position
	 * @param x,y,z position as float values
	 */
	virtual void setPosition(float x, float y, float z);

	/** \brief setter
	 *
	 * sets/changes the x,y,and z value of position
	 * @param newPos position as glm vec3
	 */
	virtual void setPosition(glm::vec3 newPos);

	/** \brief setter
	 *
	 * sets/changes direction
	 * @param dir
	 */
	void setDirection(glm::vec3 dir);

	/** \brief setter
	 *
	 * sets/changes center
	 * @param center
	 */
	void setCenter(glm::vec3 center);
	/* GETTER AND SETTER END */

	/** \brief !docu pls!
	 *
	 * compute ViewDirection from Phi and Theta
	 */
	inline void updateViewDirection();

	/** \brief !docu pls!
	 *
	 * compute Phi and Theta from View Direction
	 */
	inline void updatePhiTheta();

	/** \brief getter
	 *
	 * compute ViewMatrix
	 * @return viewMatrix
	 */
	glm::mat4 getViewMatrix();
};

#endif
