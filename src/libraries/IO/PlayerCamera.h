#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include "Camera.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

/*! @brief A First Person Camera with Bullet-Physics behaviour
 * a PlayerCamera is derived from Camera and behaves in very similar ways
 * additionally, a PlayerCamera's position is based on it's Bullet Bounding Box 
 * thus, a PlayerCamera cann collide with other Virtual Objects, and is influenced by gravity
 */
class PlayerCamera : public Camera{
private:
	btCollisionShape* collisionShape; //!< bullet Collision Shape associated with this Player Camera (cylinder shape by default)
	
	bool isRigid;			//!< true, if rigid body functionality is wanted in this Camera
	btRigidBody* rigidBody; //!< Rigid Body, incase Gravity and other Physical Interaction is wanted 

	void createCollisionShape(); //!< create a btCylinderShape as collision Shape 
	void createRigidBody();
public:
	PlayerCamera();	//!< constructor @param createRigidBody is false by default
	~PlayerCamera();	//!< destructor

	virtual void updatePosition(float deltaTime);	//!< updates Position by updating and reading the CollisionShape's Position

	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(glm::vec3 newPos);

	btRigidBody* 		getRigidBody();
	btCollisionShape* 	getCollisionShape();
};

#endif