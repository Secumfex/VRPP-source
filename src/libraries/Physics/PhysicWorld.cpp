#include <iostream>
#include <glm/glm.hpp>
#include "PhysicWorld.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

PhysicWorld::PhysicWorld() {

	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));

//	cout<<dynamicsWorld<<endl;

	gContactAddedCallback = staticCollisionCallbackFunc;
}

bool PhysicWorld::staticCollisionCallbackFunc(btManifoldPoint& collisionPoint, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2) {

	cout<<"collision"<<endl;

	return false;
}

void PhysicWorld::screenPosToWorldRay(double mouseX, double mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3& outOrigin, glm::vec3& outDirection){

	glm::vec4 rayStart_NDC (
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
			-1.0,
			1.0f
	);
	glm::vec4 rayEnd_NDC (
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
			0.0,
			1.0f
	);

	glm::mat4 InverseProjectionMatrix = glm::inverse(projectionMatrix);
	glm::mat4 InverseViewMatrix = glm::inverse(viewMatrix);

	glm::vec4 rayStart_camera = InverseProjectionMatrix * rayStart_NDC;
	rayStart_camera = rayStart_camera.w / rayStart_camera;
	glm::vec4 rayStart_world = InverseViewMatrix       * rayStart_camera;
	rayStart_world = rayStart_world.w / rayStart_world;
	glm::vec4 rayEnd_camera = InverseProjectionMatrix * rayEnd_NDC;
	rayEnd_camera = rayEnd_camera.w / rayEnd_camera;
	glm::vec4 rayEnd_world = InverseViewMatrix       * rayEnd_camera;
	rayEnd_world = rayEnd_world.w / rayEnd_world;

	glm::vec3 rayDirection_world(rayEnd_world - rayStart_world);
	rayDirection_world = glm::normalize(rayDirection_world);

	outDirection = outDirection*1000.0f;

	btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(outOrigin.x, outOrigin.y, outOrigin.z), btVector3(outDirection.x, outDirection.y, outDirection.z));
	PhysicWorld::getInstance()->dynamicsWorld->rayTest(btVector3(outOrigin.x, outOrigin.y, outOrigin.z), btVector3(outDirection.x, outDirection.y, outDirection.z), RayCallback);

	if(RayCallback.hasHit()) {
	    cout << "mesh: " << (int)RayCallback.m_collisionObject->getUserPointer() << endl;
	}
	else{
	    cout << "background" << endl;
	}
}

PhysicWorld::~PhysicWorld() {

	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}
