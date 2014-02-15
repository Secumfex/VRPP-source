#include <iostream>
#include "PhysicsComponent.h"

#include "PhysicWorld.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

PhysicsComponent::PhysicsComponent(){
	rigidBody = 0;
	modelMatrix = glm::mat4();
	hit = false;
}

PhysicsComponent::PhysicsComponent(glm::mat4 modelMatrix) {

	this-> modelMatrix = modelMatrix;
	rigidBody =  0;
	hit = false;
}

PhysicsComponent::PhysicsComponent(glm::vec3 min, glm::vec3 max) {

	glm::vec3 boxValue = max-min;

	float width = boxValue.x;
	float height = boxValue.y;
	float depth = boxValue.z;

	float x = width / 2;
	float y = height / 2;
	float z = depth / 2;

	int mass = 0;

	hit = false;

	rigidBody = addBox(width, height, depth, x, y, z, mass);
	addCollisionFlag(4);
	update();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float radius, float x, float y, float z, float mass) {

	hit = false;

	rigidBody = addSphere(radius,x,y,z,mass);
	addCollisionFlag(4);
	update();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass) {

	hit = false;
	rigidBody = addBox(width,height,depth,x,y,z,mass);
	addCollisionFlag(4);
	update();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float x, float y, float z, btVector3 normal, float mass){

	hit = false;
	rigidBody = addPlane(x,y,z,normal,mass);
	addCollisionFlag(4);
	update();
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::~PhysicsComponent() {

	PhysicWorld::getInstance()->dynamicsWorld->removeCollisionObject(rigidBody);
	btMotionState* motionState = rigidBody->getMotionState();
	btCollisionShape* shape = rigidBody->getCollisionShape();
	delete shape;
	delete motionState;
	delete rigidBody;
}

void PhysicsComponent::addCollisionFlag(int flag) {

	if(flag == 4) {
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	}
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

	return body;
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

	return body;
}

btRigidBody* PhysicsComponent::addPlane(float x, float y, float z, btVector3 normal, float mass){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));
	//btVector3 normal = btVector3(u,v,w);

	btStaticPlaneShape* plane = new btStaticPlaneShape(normal,0);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,plane);
	btRigidBody* body = new btRigidBody(info);

	return body;
}

glm::mat4 PhysicsComponent::getModelMatrix(){

	return modelMatrix;
}

btRigidBody* PhysicsComponent::getRigidBody(){

	return rigidBody;
}

void PhysicsComponent::setPosition(float x, float y, float z){

	btVector3 pos;
	pos.setX(x);
	pos.setY(y);
	pos.setZ(z);

	btTransform t;
	btRigidBody* body = rigidBody;
	body->getMotionState()->getWorldTransform(t);

	t.setOrigin(pos);
	body->getMotionState()->setWorldTransform(t);
}

glm::vec3 PhysicsComponent::getPosition(){

	btTransform t;
	btRigidBody* body = rigidBody;
	body->getMotionState()->getWorldTransform(t);

	btVector3 origin = t.getOrigin();

	glm::vec3 pos;
	pos.x = origin.getX();
	pos.y = origin.getY();
	pos.z = origin.getZ();

	return pos;
}

bool PhysicsComponent::getHit(){

	return hit;
}

void PhysicsComponent::setHit(bool hitState){

	hit = hitState;
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
	if(body->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE) {

		btTransform t;
		body->getMotionState()->getWorldTransform(t);
		float mat[16];
		t.getOpenGLMatrix(mat);

		this->modelMatrix = glm::make_mat4(mat);

	}
	else {
		return;
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
