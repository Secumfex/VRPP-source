#include <iostream>
#include "PhysicWorld.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

//gContactAddedCallback = collisionCallbackFunc;

PhysicWorld::PhysicWorld() {

	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));

	cout<<dynamicsWorld<<endl;

	gContactAddedCallback = staticCollisionCallbackFunc;
}

bool PhysicWorld::staticCollisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2) {

	cout<<"collision"<<endl;

	return false;
}

PhysicWorld::~PhysicWorld() {

	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}
