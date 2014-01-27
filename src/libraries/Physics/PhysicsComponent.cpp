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
	addCollisionFlag(4);
	update();
}

PhysicsComponent::PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass) {

	rigidBody = addBox(width,height,depth,x,y,z,mass);
	addCollisionFlag(4);
	update();
}

PhysicsComponent::~PhysicsComponent() {

	//dynamicWorld->removeCollisionObject(rigidBody);		//TODO muss noch der welt zugeordnet werden
	btMotionState* motionState = rigidBody->getMotionState();
	btCollisionShape* shape = rigidBody->getCollisionShape();
	delete shape;
	delete motionState;
	delete rigidBody;
}

glm::mat4 PhysicsComponent::getModelMatrix(){

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

btRigidBody* PhysicsComponent::addBox(float width, float height, float depth, float x, float y, float z, float mass){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	btBoxShape* box = new btBoxShape(btVector3(width/2.0,height/2.0,depth/2.0));

	btVector3 inertia(0,0,0);
	if(mass != 0.0) {
		box->calculateLocalInertia(mass,inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,box);
	btRigidBody* body = new btRigidBody(info);

	//dynamicsWorld->addRigidBody(body);		//TODO muss noch der welt zugeordnet werden

	return body;
}

void PhysicsComponent::addCollisionFlag(int flag) {

	if(flag == 4) {
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	}
}

void PhysicsComponent::initFrameListener(){
/**
 * @todo instead:
 * 	write a "UpdatePhysicsComponentListener" class as a derivative of Listener
 * 	as members, it receives a simple PhysicsComponent pointer
 * 	in its update() method it calls pc->update()
 * alternatively, leave PhysicsComponent as it is ( a Listener itself )
 *  it may be attached to the RenderLoop just the way it is
 *  how ever, bear in mind that it can only be attached to a single Subject
 */
//	Listener* frameListener;
//	frameListener->setName("FRAMELISTENER");
//	frameListener->update();
}

void PhysicsComponent::update(){

	btRigidBody* body = rigidBody;
	if(body->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE){

		btTransform t;
		body->getMotionState()->getWorldTransform(t);
		float mat[16];
		t.getOpenGLMatrix(mat);

		this-> modelMatrix = glm::make_mat4(mat);
	}
	if(body->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {

		btTransform t;
		body->getMotionState()->getWorldTransform(t);
		float mat[16];
		t.getOpenGLMatrix(mat);

		this-> modelMatrix = glm::make_mat4(mat);
	}
	else {
		return;
	}
}
