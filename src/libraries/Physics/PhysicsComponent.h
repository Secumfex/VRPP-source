#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <glm/glm.hpp>

using namespace std;

class PhysicsComponent{

private:

	glm::mat4 modelMatrix;

public:

	glm::mat4 getModelMatrix();

	PhysicsComponent(glm::mat4 modelMatrix);
	~PhysicsComponent();

};

#endif
