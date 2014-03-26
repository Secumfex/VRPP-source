#include <iostream>
#include "Seetang.h"


using namespace std;

btRigidBody *rigidBody_tmp;
btRigidBody *rigidBody;
Seetang::Seetang(){

	vector<btRigidBody*> rbVec;
	rbVec.size()=4;
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

glm::mat4 Seetang::getViewMatrix(){
	return mViewMatrix;
}

btRigidBody* Seetang::getRigidBody(){
	return btRigidBody;
}

void Seetang::MVMultiplikation(){
	rigidBody *= getViewMatrix();

}
