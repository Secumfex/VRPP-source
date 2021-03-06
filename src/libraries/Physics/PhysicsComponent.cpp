#include <iostream>
#include "PhysicsComponent.h"

#include "PhysicWorld.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application/ApplicationStates.h"

#include "Visuals/VirtualObject.h"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btOptimizedBvh.h"
#include "LinearMath/btAlignedAllocator.h"
#include "BulletCollision/CollisionShapes/btTriangleInfoMap.h"

using namespace std;

PhysicsComponent::PhysicsComponent(){
	rigidBody = 0;
	hit = false;
}

PhysicsComponent::PhysicsComponent(PhysicsComponent* phy){
	rigidBody = phy->getRigidBody();
	hit = phy->getHit();
	glm::vec3 pos = phy->getPosition();
	this->setPosition(pos.x, pos.y, pos.z);
}
PhysicsComponent::PhysicsComponent(glm::vec3 min, glm::vec3 max, float mass, int collisionFlag) {

	glm::vec3 boxValue = max-min;

	float width = boxValue.x;
	float height = boxValue.y;
	float depth = boxValue.z;


	float x = min.x + width / 2.0f;
	float y = min.y + height / 2.0f;
	float z = min.z + depth / 2.0f;

	hit = false;

	rigidBody = addBox(width , height , depth, x, y, z, mass);
	rigidBody->setUserPointer(this);	// use bullet's user pointer to refer to this Object
	setCollisionFlag(collisionFlag);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float x, float y, float z, btTriangleMesh* btMesh, vector<GraphicsComponent*> mGraphComponent, btTriangleIndexVertexArray* btTIVA) {

	hit = false;

	rigidBody = addTriangleMesh(x,y,z, btMesh, mGraphComponent, btTIVA);
	rigidBody->setUserPointer(this);	// use bullet's user pointer to refer to this Object
	setCollisionFlag(1);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);

}

PhysicsComponent::PhysicsComponent(float radius, float x, float y, float z, float mass, int collisionFlag) {

	hit = false;

	rigidBody = addSphere(radius,x,y,z,mass);
	rigidBody->setUserPointer(this);	// use bullet's user pointer to refer to this Object
	setCollisionFlag(collisionFlag);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag) {
	hit = false;
	rigidBody = addBox(width,height,depth,x,y,z,mass);
	rigidBody->setUserPointer(this);	// use bullet's user pointer to refer to this Object
	setCollisionFlag(collisionFlag);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}


PhysicsComponent::PhysicsComponent(float x, float y, float z, glm::vec3 normal, float mass, int collisionFlag){
	hit = false;
	rigidBody = addPlane(x,y,z,normal,mass);
	rigidBody->setUserPointer(this);	// use bullet's user pointer to refer to this Object
	setCollisionFlag(collisionFlag);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
}

PhysicsComponent::PhysicsComponent(char* filename, float x, float y, float z){

	hit = false;
	rigidBody = addHeightfield(filename,x,y,z);
	setCollisionFlag(1);	//static object
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
	rigidBody->translate(trans);
	glm::vec3 origin = this->getPosition();
	this->setPosition(origin.x+pos.x,origin.y+pos.y,origin.z+pos.z);

//	btTransform transform = rigidBody -> getCenterOfMassTransform();
//	transform.setOrigin( transform.getOrigin() + trans );
//	rigidBody -> setCenterOfMassTransform(transform);
//
//	btVector3 position = transform.getOrigin();
//	this->setPosition( position.x(), position.y(), position.z() );

	/*
	btTransform transform = rigidBody->getWorldTransform();
	btVector3 origin2 = transform.getOrigin();
	transform.setIdentity();
	transform.setOrigin(origin2+trans);
	rigidBody->setWorldTransform(transform);
	*/
	//rigidBody->translate(trans);

}

void PhysicsComponent::scale(glm::vec3 scale, VirtualObject* vo){
	btVector3 scalevec = btVector3(scale.x, scale.y, scale.z);

		//vo->setModelMatrix(glm::scale(glm::mat4(1.0f), scale));


	this->rigidBody->getCollisionShape()->setLocalScaling(scalevec);
	update(vo);
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

	btBoxShape* box = new btBoxShape(btVector3(width/2.0f,height/2.0f,depth/2.0f));
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
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere);
	btRigidBody* body = new btRigidBody(info);
	body->setLinearFactor(btVector3(1,1,1));
	return body;
}

btRigidBody* PhysicsComponent::addPlane(float x, float y, float z, glm::vec3 normal, float mass){

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x ,y,z));
	//btVector3 normal = btVector3(u,v,w);

	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(normal.x,normal.y,normal.z),0);

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

btRigidBody* PhysicsComponent::addTriangleMesh(float x, float y, float z, btTriangleMesh* btMesh, vector<GraphicsComponent*> mGraphComponent, btTriangleIndexVertexArray* btTIVA){

	static btTriangleMesh* triangleMesh = btMesh;	//Var A
	static btTriangleIndexVertexArray* tIVA = btTIVA; //Var B

	static btRigidBody* staticBody = 0;

	bool useQuantizedAabbCompression = true;
	btBvhTriangleMeshShape* triangleShape = 0;
	triangleShape = new btBvhTriangleMeshShape(tIVA, useQuantizedAabbCompression);

	cout << "btBvhTriangleMeshShape created" << endl;

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(x, y, z));

	float mass = 0.0f;

	btDefaultMotionState* motionState = new btDefaultMotionState(trans);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motionState,triangleShape);
	staticBody = new btRigidBody(info);

	cout << "static rigidbody added" << endl;

	return staticBody;
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

		// in case the model is not symmetrical, the offset of the rigid body center of mass to the model space origin must be taken into account
		// to prevent applying a double model matrix offset
		const glm::mat4 centerOfMassOffset = vo->getCenterOfMassOffsetMatrix();

		// first move origin into center of mass, then apply rigid body model matrix
		vo->setModelMatrix( glm::make_mat4(mat) * centerOfMassOffset );
}
