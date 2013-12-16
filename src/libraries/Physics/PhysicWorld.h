#ifndef PHYSICWORLD_H_
#define PHYSICWORLD_H_

#include "btBulletDynamicsCommon.h"

class PhysicWorld {
public:

	btBroadphaseInterface* broadphase;							/**< specifies the broadphase algorithm */
	btDefaultCollisionConfiguration* collisionConfiguration;	/**< fine tunes the algorithms used for the full (not broadphase) collision detection */
	btCollisionDispatcher* dispatcher;							/**< register a callback that filters overlapping broadphase proxies */
	btSequentialImpulseConstraintSolver* solver;				/**< causes the objects to interact properly */
	btDiscreteDynamicsWorld* dynamicsWorld;						/**< bullet dynamic world */

	//void initPhysics();
	//void deleteLoc();

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

	//bool collisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2);

};


#endif /* PHYSICWORLD_H_ */
