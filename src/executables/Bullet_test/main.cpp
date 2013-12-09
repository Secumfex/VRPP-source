#include <iostream>
#include <glm/glm.hpp>

//#include "btBulletDynamicsCommon.h"
//#include "bullet.h"						//!!error, sobald irgendwo bullet includiert wird!!
//#include "Physics/PhysicWorld.h"
//#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
//#include "Visuals/VirtualObject.h"

using namespace std;
/*
void initPhysics() {

	btBroadphaseInterface *broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
	btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));
}
*/
int main() {

	//PhysicWorld *world = new PhysicWorld();
	//initPhysics();
	cout<<"world created"<<endl;

	//VirtualObject *test1 = new VirtualObject();

	return 0;
};
