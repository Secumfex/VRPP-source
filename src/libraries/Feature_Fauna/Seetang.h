/*
 * Seetang.h
 *
 *  Created on: 25.03.2014
 *      Author: Flower
 */

#ifndef SEETANG_H_
#define SEETANG_H_
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "Physics\PhysicsComponent.h"
#include "btBulletDynamicsCommon.h"

class Seetang {

public:
	Seetang(vector<btRigidBody*> rbVec);
	btRigidBody* addSphere(float radius, float x, float y, float z, float mass);
	btRigidBody *rigidBody;
	vector<btRigidBody*> spheres;

private:

};

#endif /* SEETANG_H_ */
