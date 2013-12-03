#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>

using namespace std;

int lastID = 0;

//constructor
VirtualObject::VirtualObject(glm::mat4 modelMatrix){

	this-> modelMatrix = modelMatrix;
	id = lastID + 1;
	lastID = id;
	graphicsComponent.push_back(GraphicsComponent());
	physicsComponent = new PhysicsComponent(modelMatrix);
}

VirtualObject::~VirtualObject(){

	delete physicsComponent;
}

void VirtualObject::updateModelMatrix(){
	modelMatrix = physicsComponent->getModelMatrix();
}

glm::mat4 VirtualObject::getModelMatrix(){
	return modelMatrix;
}

vector<GraphicsComponent>* VirtualObject:: getGraphicsComponent(){
	return graphics;
}

//update modelmatrix (via bullet)
//altern. ueber listener pattern
