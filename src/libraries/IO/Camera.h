#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

/*First Person Kamera*/
class Camera{
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	float m_phi;		//Drehung
	float m_theta;		//Neigung

inline void updateViewDirection();	// Blickrichtung aus Winkeln berechnen 

public:
	Camera();
	~Camera();

	void turn(float deg_phi, float deg_theta);	// Kamera drehen
	void move(float delta_x, float delta_y, float delta_z);	// Kamera bewegen
	void move(glm::vec3 translation);	// Kamera bewegen
	void moveForward(float distance);	//Kamera entlang Blickrichtung bewegen
	void moveLeft(float distance);		//Kamera Horizontal zur Blickrichtung bewegen 
	void moveUp(float distance);		//Kamera entlang Up-Vektor verschieben -- NICHT VERTIKAL ZU BLICKRICHTUNG

	void setPosition(float x, float y, float z);
	glm::vec3 getPosition();
	glm::vec3 getViewDirection();
	float getPhi();
	float getTheta();

	glm::mat4 getViewMatrix();	// View Matrix berechnen und zurück lassen
};

#endif