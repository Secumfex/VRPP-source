#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include "Camera.h"
#include "btBulletDynamicsCommon.h"


using namespace std;

/** @brief A First Person Camera with Bullet-Physics behaviour
 * a PlayerCamera is derived from Camera and behaves in very similar ways
 * additionally, a PlayerCamera's position is based on it's Bullet Bounding Box 
 * thus, a PlayerCamera cann collide with other Virtual Objects, and is influenced by gravity
 */
class PlayerCamera : public Camera{
protected:
	btCollisionShape* collisionShape; 	/**< bullet Collision Shape associated with this Player Camera (cylinder shape by default) */
	
	bool isRigid;						/**< true, if rigid body functionality is wanted in this Camera */
	btRigidBody* rigidBody; 			/**< Rigid Body, incase Gravity and other Physical Interaction is wanted */

	/** \brief auxillary method to create a Bullet Collision shape
	 * create a btCylinderShape as collision Shape
	 */
	void createCollisionShape();

	/** \brief auxillary method to create and register a Bullet Rigid Body which resembles this Camera
	 *
	 */
	void createRigidBody();


public:
	/** \brief constructor
	 *
	 * createRigidBody is false by default
	 */
	PlayerCamera();

	/** \brief destructor
	 *
	 */
	~PlayerCamera();

	/** \brief updates position
	 *
	 * updates Position by updating and reading the CollisionShape's Position
	 * @param deltaTime
	 */
	virtual void updatePosition(float deltaTime);

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

	/** \brief getter
	 *
	 * @return bullet rigid body (rigidBody)
	 */
	btRigidBody* 		getRigidBody();

	/** \brief getter
	 *
	 * @return bullet collision shape (collisionShape)
	 */
	btCollisionShape* 	getCollisionShape();
};

#endif
