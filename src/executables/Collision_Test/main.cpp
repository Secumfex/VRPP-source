#include <iostream>
#include <glm/glm.hpp>

#include "btBulletDynamicsCommon.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include "Visuals/VirtualObject.h"

using namespace std;



int main() {

	PhysicWorld* world = new PhysicWorld();
	cout << "world created" << endl;



	return 0;
};
