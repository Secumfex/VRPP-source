#include <iostream>
#include "PhysicsComponent.h"

#include "PhysicWorld.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Visuals/VirtualObject.h"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

using namespace std;

PhysicsComponent::PhysicsComponent(){
	rigidBody = 0;
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
	addCollisionFlag(8);	//momentan noch fest, muesste eig auch zusaetzlicher input wert sein
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float radius, float x, float y, float z, float mass) {

	hit = false;

	rigidBody = addSphere(radius,x,y,z,mass);
	addCollisionFlag(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass) {

	hit = false;
	rigidBody = addBox(width,height,depth,x,y,z,mass);
	addCollisionFlag(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float x, float y, float z, btVector3& normal, float mass){	//todo: change the type of normal

	hit = false;
	rigidBody = addPlane(x,y,z,normal,mass);
	addCollisionFlag(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(char* filename, float x, float y, float z){

	hit = false;
	rigidBody = addHeightfield(filename,x,y,z);
	addCollisionFlag(1);	//static object
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);

	/*
	FILE* heightfieldFile;
	//char* path = "test/";		//pfad zum entspr. ordner
	//char* temp = path + filename;		//char+char
	heightfieldFile = fopen(filename,"r");
	//btHeightfieldTerrainShape* heightmap = new btHeightfieldTerrainShape();
	 */

}

PhysicsComponent::~PhysicsComponent() {

	if(rigidBody != 0){
		PhysicWorld::getInstance()->dynamicsWorld->removeCollisionObject(rigidBody);
		btMotionState* motionState = rigidBody->getMotionState();
		btCollisionShape* shape = rigidBody->getCollisionShape();
		delete shape;
		delete motionState;
		delete rigidBody;
	}

	else
		delete rigidBody;


}

void PhysicsComponent::translate(glm::vec3 pos){
	btVector3 trans = btVector3(pos.x, pos.y, pos.z);

	this->rigidBody->translate(trans);
}

void PhysicsComponent::scale(glm::vec3 scale){
	btVector3 scalevec = btVector3(scale.x, scale.y, scale.z);

		rigidBody->getCollisionShape()->setLocalScaling(scalevec);
}

void PhysicsComponent::addCollisionFlag(int flag) {
	switch( flag)
	  { case 1: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT); break;
	    case 2: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); break;
	    case 4: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE); break;
	    case 8: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK); break;
	    case 16: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CHARACTER_OBJECT); break;
	    case 32: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT); break;
	    case 64: rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DISABLE_SPU_COLLISION_PROCESSING); break;}
}

void PhysicsComponent::setCollisionFlag(int flag){
	switch( flag)
	  { case 1: rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT); break;
		case 2: rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT); break;
		case 4: rigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE); break;
		case 8: rigidBody->setCollisionFlags(btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK); break;
		case 16: rigidBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT); break;
		case 32: rigidBody->setCollisionFlags(btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT); break;
		case 64: rigidBody->setCollisionFlags(btCollisionObject::CF_DISABLE_SPU_COLLISION_PROCESSING); break;}
}

btRigidBody* PhysicsComponent::addBox(float width, float height, float depth, float x, float y, float z, float mass){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	btBoxShape* box = new btBoxShape(btVector3(width,height,depth));

	btVector3 inertia;
	if(mass != 0.0) {
		box->calculateLocalInertia(mass,inertia);
	}
	box->calculateLocalInertia(mass,inertia);



	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,box, inertia);

	btRigidBody* body = new btRigidBody(info);
	body->setLinearFactor(btVector3(1,1,1));
	return body;
}

btRigidBody* PhysicsComponent::addSphere(float radius, float x, float y, float z, float mass) {

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

btRigidBody* PhysicsComponent::addPlane(float x, float y, float z, btVector3& normal, float mass){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x ,y,z));
	//btVector3 normal = btVector3(u,v,w);

	btStaticPlaneShape* plane = new btStaticPlaneShape(normal,0);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,plane);
	btRigidBody* body = new btRigidBody(info);
	body->setLinearFactor(btVector3(1,1,1));
	return body;
}

btRigidBody* PhysicsComponent::addHeightfield(char* filename, float x, float y, float z){

	int width,length;

	FILE* heightfieldFile;
	//char* path = "test/";		//pfad zum entspr. ordner
	//char* temp = path + filename;		//char+char
	heightfieldFile = fopen(filename,"r");

	char* heightfieldData;
	btScalar heightScale;
	btScalar minHeight,maxHeight;
	int upAxis;
	PHY_ScalarType heightDataType;
	bool flipQuadEdges;
	btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(width, length, heightfieldData, heightScale, minHeight, maxHeight, upAxis, heightDataType, flipQuadEdges);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	float mass = 0.0;	//damit dann static

	btDefaultMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,groundShape);
	btRigidBody* body = new btRigidBody(info);
	return body;
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

void PhysicsComponent::update(VirtualObject* vo){

	btRigidBody* body = rigidBody;


		btTransform t;
		body->getMotionState()->getWorldTransform(t);
		float mat[16];
		t.getOpenGLMatrix(mat);

		vo->setModelMatrix(glm::make_mat4(mat));
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
