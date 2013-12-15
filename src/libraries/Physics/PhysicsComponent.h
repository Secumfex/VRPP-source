#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"

using namespace std;

class PhysicsComponent{
private:
	glm::mat4 modelMatrix;

	btRigidBody *rigidBody;

public:
	glm::mat4 getModelMatrix();

	btRigidBody* addSphere(float radius, float x, float y, float z, float mass);
	btRigidBody* addBox(float width, float height, float depth, float x, float y, float z, float mass);
	void updateModelMatrix();

	PhysicsComponent(glm::mat4 modelMatrix);
	PhysicsComponent(float radius, float x, float y, float z, float mass);
	PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass);
	~PhysicsComponent();
};

#endif
