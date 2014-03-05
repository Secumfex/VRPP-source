#ifndef PHYSICWORLD_H_
#define PHYSICWORLD_H_

#include <glm/glm.hpp>
#include "Patterns/Singleton.h"
#include "btBulletDynamicsCommon.h"

/** \brief PhysicWorld
 *
 *  PhysicWorld is the shell for a bullet dynamic world. the real physic world which contains all rigid bodies of the virtual objects or rather
 *  their physic components is PhysicWorld->dynamicsWorld. PhysicWorld is Singleton to ensure that there is only one physic world at a time.
 */
class PhysicWorld : public Singleton<PhysicWorld> {
friend class Singleton<PhysicWorld>;

public:
	btBroadphaseInterface* broadphase;							/**< specifies the broadphase algorithm */
	btDefaultCollisionConfiguration* collisionConfiguration;	/**< fine tunes the algorithms used for the full (not broadphase) collision detection */
	btCollisionDispatcher* dispatcher;							/**< register a callback that filters overlapping broadphase proxies */
	btSequentialImpulseConstraintSolver* solver;				/**< causes the objects to interact properly */
	btDynamicsWorld* dynamicsWorld;								/**< bullet dynamic world */

	/** \brief constructor
	 *
	 * initializes the physics world
	 */
	PhysicWorld();

	/** \brief destructor
	 *
	 * clears the allocated memory, deletes dynamicsWorld, solver, collisionConfiguration, dispatcher, broadphase
	 */
	~PhysicWorld();

	/** \brief collision callback function
	 *
	 * is called if a collition between two rigidBodies happens.
	 * @param collisionPoint point where a collision is detected
	 * @param obj1,obj2 objects which are involved in the collision
	 * @param id1,id2 currently not used
	 * @param index1,index2 currently not used
	 * @return true,false currently not used
	 */
	static bool staticCollisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2);

	/** \brief function for ray-picking
	 *
	 * shoots a ray from mouse position into the world to find the first rigidBody which can be picked with the mouse.
	 * @param mouseX,mouseY current mouse position
	 * @param screenWidth,screenHeight screen resolution
	 * @param viewMatrix camera position and orientation
	 * @param projectionMatrix camera parameters
	 * @param outOrigin
	 * @param outDirection
	 * @return void
	 */
	void screenPosToWorldRay(double mouseX, double mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3& outOrigin, glm::vec3& outDirection);

};


#endif /* PHYSICWORLD_H_ */
