#ifndef PHYSICWORLD_H_
#define PHYSICWORLD_H_

#include "btBulletDynamicsCommon.h"
#include "bullet.h"

class PhysicWorld {
public:

	btBroadphaseInterface *broadphase;
	btDefaultCollisionConfiguration *collisionConfiguration;
	btCollisionDispatcher *dispatcher;
	btSequentialImpulseConstraintSolver *solver;
	btDiscreteDynamicsWorld *dynamicsWorld;

	void initPhysics();
	void deleteLoc();
	PhysicWorld();
	~PhysicWorld();


};


#endif /* PHYSICWORLD_H_ */
