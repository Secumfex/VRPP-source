#include <iostream>
#include "PhysicsComponent.h"

#include "PhysicWorld.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

PhysicsComponent::PhysicsComponent(glm::mat4 modelMatrix) {

	this-> modelMatrix = modelMatrix;
	rigidBody =  0;
}

PhysicsComponent::PhysicsComponent(float radius, float x, float y, float z, float mass) {

	rigidBody = addSphere(radius,x,y,z,mass);
}

PhysicsComponent::~PhysicsComponent() {

	//dynamicWorld->removeCollisionObject(rigidBody);		//TODO muss noch der welt zugeordnet werden
	btMotionState* motionState = rigidBody->getMotionState();
	btCollisionShape* shape = rigidBody->getCollisionShape();
	delete shape;
	delete motionState;
	delete rigidBody;
}

glm::mat4 PhysicsComponent::getModelMatrix() {

	return modelMatrix;
}

btRigidBody* PhysicsComponent::addSphere(float radius, float x, float y, float z, float mass) {

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	btSphereShape* sphere = new btSphereShape(radius);

	btVector3 inertia(0,0,0);
	if(mass != 0.0){
		sphere->calculateLocalInertia(mass,inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere);
	btRigidBody* body = new btRigidBody(info);

	//dynamicsWorld->addRigidBody(body);		//TODO muss noch der welt zugeordnet werden

	return body;
}

//TODO update methode per listener pattern
void PhysicsComponent::updateModelMatrix() {

	btRigidBody* sphere = rigidBody;
	if(sphere->getCollisionShape()->getShapeType() != SPHERE_SHAPE_PROXYTYPE){
		return;
	}
	btTransform t;
	sphere->getMotionState()->getWorldTransform(t);
	float mat[16];
	t.getOpenGLMatrix(mat);

	this-> modelMatrix = glm::make_mat4(mat);
}

