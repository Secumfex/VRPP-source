#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <glm/glm.hpp>
#include <vector>

class VirtualObject{

public:

	//TODO Model Matrix
	glm::mat4 modelMatrix;

	int id;
	PhysicsComponent *physicsComponent;
	vector<GraphicsComponent> graphicsComponent;

	void updateModelMatrix();

	VirtualObject(glm::mat4 modelMatrix = glm::mat4());
	~VirtualObject();
};


#endif /* VIRTUALOBJECT_H */
