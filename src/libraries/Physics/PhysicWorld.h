#ifndef PHYSICWORLD_H_
#define PHYSICWORLD_H_

//#include "btBulletDynamicsCommon.h"
#include "bullet.h"

class PhysicWorld {
public:

	btBroadphaseInterface *broadphase;
	btDefaultCollisionConfiguration *collisionConfiguration;
	btCollisionDispatcher *dispatcher;
	btSequentialImpulseConstraintSolver *solver;
	btDiscreteDynamicsWorld *dynamicsWorld;

	PhysicWorld();
	~PhysicWorld();

	//void initPhysics();
	//void deleteLoc();
};


#endif /* PHYSICWORLD_H_ */
