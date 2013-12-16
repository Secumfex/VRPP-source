#ifndef PHYSICWORLD_H_
#define PHYSICWORLD_H_

#include "btBulletDynamicsCommon.h"
//#include "bullet.h"

class PhysicWorld {
public:

	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	//void initPhysics();
	//void deleteLoc();
	PhysicWorld();
	~PhysicWorld();

	//bool collisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2);

};


#endif /* PHYSICWORLD_H_ */
