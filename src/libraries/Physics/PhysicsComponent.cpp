#include <iostream>
#include "PhysicsComponent.h"

#include "PhysicWorld.h"
#include <glm/glm.hpp>
#include <windows.h>
#include <glm/gtc/type_ptr.hpp>

#include "Application/ApplicationStates.h"

#include "Visuals/VirtualObject.h"
#include "Visuals/GraphicsComponent.h"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "Tools/stb_image.h"

using namespace std;

PhysicsComponent::PhysicsComponent(){
	rigidBody = 0;
	hit = false;
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
	setCollisionFlag(collisionFlag);	//momentan noch fest, muesste eig auch zusaetzlicher input wert sein
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

PhysicsComponent::PhysicsComponent(string filename, float x, float y, float z, VirtualObject* vo){

	hit = false;
	//rigidBody = addHeightfield(filename,x,y,z);
	rigidBody = addHeightfield2(x,y,z,vo);
	addCollisionFlag(1);	//static object
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rigidBody);
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

//btRigidBody* PhysicsComponent::addHeightfield(char* filename, int width, int height, float x, float y, float z){	//for use of preferred constructor
//btRigidBody* PhysicsComponent::addHeightfield(char* filename, int width, int length, float x, float y, float z){	//for use of legacy constructor
btRigidBody* PhysicsComponent::addHeightfield(string filename, float x, float y, float z){

	cout << "addHeightfield called" << endl;	//zum test
	FILE* heightfieldFile;
	char* filenameCHAR = RESOURCES_PATH"/Heightfield/heightfield128x128.raw";
	int width,length = 128;
	//BYTE* heightfieldData;
	//unsigned char* heightfieldData = new unsigned char[width*length];		//for 1. load methode
	float* heightfieldData = new float[width*length];

	/* for 2. load methode
	int width, length, bytesPerPixel;
	unsigned char* heightfieldData = stbi_load(filename.c_str(), &width, &length, &bytesPerPixel, 0);
	if(heightfieldData == NULL){
		cout << "ERROR: Unable to open image "  << filename << endl;
	}
	cout << "width: " << width << " length: " << length<< " bytesPerPixel: " << bytesPerPixel << endl;
	*/

	// for 1. load methode
	for(int i=0; i<width*length; i++){
		heightfieldData[i] = 0;
	}


	heightfieldFile = fopen(filenameCHAR,"r");
	if(heightfieldFile){
		int numBytes = fread(heightfieldData,1,width*length,heightfieldFile);
		if(!numBytes){
			cout << "couldn't read heightfieldData at " << filename << endl;
		}
	}

	//fread(heightfieldData,1,width*height,heightfieldFile);	//for use of preferred constructor
	fclose(heightfieldFile);		//for 1. load methode

	//float heightScale = 0.2;									//for use of preferred constructor
	//btScalar minHeight = 0;		//min hoehe						//for use of preferred constructor
	btScalar maxHeight = 100;		//max hoehe
	//int upAxis = 1;			//y-axis as "up"				//for use of preferred constructor
	int upIndex = 1;	//y-axis as "up"						//for use of legacy constructor
	//PHY_ScalarType heightDataType = PHY_FLOAT;				//for use of preferred constructor
	bool useFloatData = true;									//for use of legacy constructor
	bool flipQuadEdges = false;

	//btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(width, length, heightfieldData, heightScale, minHeight, maxHeight, upAxis, heightDataType, flipQuadEdges);	//for use of preferred constructor
	btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(width, length, heightfieldData, maxHeight, upIndex, useFloatData, flipQuadEdges);	//for use of legacy constructor

	groundShape->setUseDiamondSubdivision(true);

	btVector3 localScaling(10,10,10);
	localScaling[upIndex]=1.f;						//for use of legacy constructor
	//localScaling[upAxis]=1.f;						//for use of preferred constructor
	groundShape->setLocalScaling(localScaling);

	x,y,z = 0;	//zum test

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	float mass = 0.0;	//damit dann static

	btVector3 inertia;
	if(mass != 0.0){
		groundShape->calculateLocalInertia(mass, inertia);
	}

	btDefaultMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,groundShape);
	btRigidBody* body = new btRigidBody(info);
	cout << "heightMap phComp erstellt" << endl;	//zum test
	//stbi_image_free(heightfieldData);
	return body;
}

btRigidBody* PhysicsComponent::addHeightfield2(float x, float y, float z, VirtualObject* vo){

	vector<GraphicsComponent*> GCs = vo->getGraphicsComponent();
	int numTriangles = GCs[0]->getMesh()->getNumFaces();
	int triangleBase;
	int triangleStride = 3;
	int numVertex = GCs[0]->getMesh()->getNumVertices();
	vector<glm::vec3> temp2 = GCs[0]->getMesh()->getVertices();
	btScalar vertexBase;
	int vertexStride = 3*sizeof(int);

	btTriangleIndexVertexArray* TIVA = new btTriangleIndexVertexArray(numTriangles,&triangleBase,triangleStride,numVertex,&vertexBase,vertexStride);

	bool	useQuantizedAabbCompression = true;
	btBvhTriangleMeshShape* groundShape = new btBvhTriangleMeshShape(TIVA,useQuantizedAabbCompression);

	btVector3 localScaling(10,10,10);
	groundShape->setLocalScaling(localScaling);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));

	float mass = 0.0;	//damit dann static

	btVector3 inertia;
	if(mass != 0.0){
		groundShape->calculateLocalInertia(mass, inertia);
	}
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
