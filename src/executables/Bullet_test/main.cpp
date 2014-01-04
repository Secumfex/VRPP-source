#include <iostream>
#include <glm/glm.hpp>

#include "btBulletDynamicsCommon.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include "Visuals/VirtualObject.h"

using namespace std;

bool collisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2) {

	cout<<"collision"<<endl;

	return false;
}

int main() {

	PhysicWorld* world = new PhysicWorld();
	cout << "world created" << endl;

	gContactAddedCallback = collisionCallbackFunc;

	VirtualObject* test1 = new VirtualObject();
	cout << test1 << endl;

	cout << test1->physicsComponent->getModelMatrix()[0][1]<< endl;

	return 0;
};
