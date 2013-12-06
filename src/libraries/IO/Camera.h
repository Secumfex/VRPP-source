#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class Camera{
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	float m_phi;		//Drehung
	float m_theta;		//Neigung

inline void updateViewDirection();

public:
	Camera();
	~Camera();

	void turn(float deg_phi, float deg_theta);

void setPosition(float x, float y, float z);
	glm::vec3 getPosition();
	glm::vec3 getViewDir();
	float getPhi();
	float getTheta();

glm::mat4 getViewMatrix();

};

#endif