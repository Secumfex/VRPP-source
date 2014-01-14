#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <glm/glm.hpp>
#include <vector>


class VirtualObject{

private:

	glm::mat4 modelMatrix;
	int id;
	vector<GraphicsComponent*> mGraphComponent;


public:

	glm::mat4 getModelMatrix();
	vector<GraphicsComponent*> getGraphicsComponent();
	
	PhysicsComponent *physicsComponent;
	void addGraphicsComponent(GraphicsComponent *graphcomp);


	void updateModelMatrix();

	VirtualObject(glm::mat4 modelMatrix = glm::mat4());
	~VirtualObject();
};


#endif /* VIRTUALOBJECT_H */
