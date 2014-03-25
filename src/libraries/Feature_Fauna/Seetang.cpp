/*
 * Seetang.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Flower
 */
#include <iostream>
#include "Seetang.h"


using namespace std;

btRigidBody *rigidBody_tmp;
Seetang::Seetang(vector<btRigidBody*> rbVec){

	for(btRigidBody i = rbVec.front(); i < rbVec.end(); i++){
		rbVec[i] = addSphere(10.0, 0.0, 0.0, 0.0, 0.0);
	}

}

btRigidBody* addSphere(float radius, float x, float y, float z, float mass) {

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	btSphereShape* sphere = new btSphereShape(radius);

	btVector3 inertia;
	if(mass != 0.0){
		sphere->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
	btRigidBody* body = new btRigidBody(info);
	body->setLinearFactor(btVector3(1,1,1));
	return body;
}
