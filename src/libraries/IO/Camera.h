#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

using namespace std;

/*FIRST PERSON CAMERA*/
class Camera{
private:
	glm::vec3 position;
	glm::vec3 direction;

	float xPosition;
	float yPosition;
	float zPosition;
	float phi;		// rotation, horizontal
	float theta;	// inclination, vertical

	glm::vec3 getUp();


public:
	/* Constructor & Destructor */
	Camera();
	~Camera();

	/* GETTER AND SETTER BEGIN */
	// TODO remove unnecessary methods
	float getX();
	void setX(float updateX);
	float getY();
	void setY(float updateY);
	float getZ();
	void setZ(float updateZ);

	float getPhi();
	void setPhi(float updatePhi);
	float getTheta();
	void setTheta(float updateTheta);

	glm::vec3 getRight();
	glm::vec3 getViewDirection();
	glm::vec3 getPosition();
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 newPos);
	/* GETTER AND SETTER END */

	// compute ViewDirection
	inline void updateViewDirection();

	// compute ViewMatrix
	glm::mat4 getViewMatrix();
};

#endif
