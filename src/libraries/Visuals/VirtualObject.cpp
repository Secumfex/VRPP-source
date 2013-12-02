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
	graphicsComponent = new GraphicsComponent();
	physicsComponent = new PhysicsComponent(modelMatrix);
}

VirtualObject::~VirtualObject(){

	delete graphicsComponent;
	delete physicsComponent;
}

void VirtualObject::updateModelMatrix(){
	modelMatrix = physicsComponent->getModelMatrix();
}

//update modelmatrix (via bullet)
//altern. ueber listener pattern
