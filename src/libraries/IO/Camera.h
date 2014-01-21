#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#ifndef PI
#define PI 3.14159265
#endif

///A Camera can be used for first person view. It is represented by a position and view direction.
/**
 *	The view direction is computed by the polar coordinates phi and theta.
 *	The camera can be turned by using the turn method
 *	A view matrix can be computed.
 */
class Camera{
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	float m_phi;		///< yaw	:  rotation about y-axis
	float m_theta;		///< pitch : rotation about x-axis

inline void updateViewDirection();		// compute and save direction vector  from polar coordinates
inline void updatePolarCoordinates();	// compute and save polar coordinates from direction vector

public:
	Camera(glm::vec3 pos = glm::vec3(0.0,0.0,0.0), glm::vec3 direction = glm::vec3(0.0,0.0,-1.0), glm::vec3 up = glm::vec3(0.0,1.0,0.0));
	Camera(glm::vec3 pos = glm::vec3(0.0,0.0,0.0), float phi = 3.0*PI/2.0, float theta = PI/2.0,  glm::vec3 up = glm::vec3(0.0,1.0,0.0));
	~Camera();

	void turn(float deg_phi, float deg_theta);				//!< turn camera by degrees vertically, horizontally
	void move(float delta_x, float delta_y, float delta_z);	//!< move camera
	void move(glm::vec3 translation);		//!< move camera along translation vector
	void moveForward(float 	distance);		//!< move camera along direction vector
	void moveBackward(float 	distance);	//!< move camera along negative direction vector
	void moveLeft	(float 	distance);		//!< move camera orthogonally to direction to the left
	void moveRight	(float 	distance);		//!< move camera orthogonally to direction to the right
	void moveUp		(float	distance);		//!< move camera along up-vector (NOTE: not necessarily orthogonally to direction)
	void moveDown	(float	distance);		//!< move camera along negative up-vector (NOTE: not necessarily orthogonally to direction)

	void setPosition(float x, float y, float z);
	glm::vec3 getPosition();
	glm::vec3 getViewDirection();
	float getPhi();
	float getTheta();

	glm::mat4 getViewMatrix();	///< compute view matrix from position and direction vectors
};

#endif
