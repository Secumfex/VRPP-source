#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>

using namespace std;

int lastID = 0;


VirtualObject::VirtualObject() {

	modelMatrix = glm::mat4(); 	//loadidentity

	id = lastID + 1;
	lastID = id;
	//graphicsComponent = new GraphicsComponent();
	physicsComponent = new PhysicsComponent(modelMatrix);

	float radius,x,y,z,mass = 1.0; 	//aus graphiccomponent bkommen (?) 1.0 zum test

	physicsComponent = new PhysicsComponent(radius,x,y,z,mass);
}

VirtualObject::VirtualObject(glm::mat4 modelMatrix) {
	this-> modelMatrix = modelMatrix;
	id = lastID + 1;
	lastID = id;

	physicsComponent = new PhysicsComponent(modelMatrix);
}

VirtualObject::~VirtualObject() {

	//delete graphicsComponent;
	delete physicsComponent;
}


void VirtualObject:: addGraphicsComponent(GraphicsComponent *graphcomp){
	mGraphComponent.push_back(graphcomp);
}

void VirtualObject::updateModelMatrix() {

	modelMatrix = physicsComponent->getModelMatrix();
}

vector<GraphicsComponent*> VirtualObject:: getGraphicsComponent(){
	return mGraphComponent;
}

glm::mat4 VirtualObject::getModelMatrix(){
	return modelMatrix;
}