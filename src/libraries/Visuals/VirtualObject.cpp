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

	physicsComponent = new PhysicsComponent();

	float radius,x,y,z,mass = 1.0; 	//aus graphiccomponent bkommen (?) 1.0 zum test


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

void VirtualObject::updateModelMatrix() {
	modelMatrix = physicsComponent->getModelMatrix();
}

void VirtualObject:: addGraphicsComponent(GraphicsComponent *graphcomp){
	mGraphComponent.push_back(graphcomp);
}

vector<GraphicsComponent*> VirtualObject:: getGraphicsComponent(){
	return mGraphComponent;
}

void VirtualObject::setPhysicsComponent(){
	physicsComponent = new PhysicsComponent();
}

void VirtualObject::setPhysicsComponent(glm::mat4 modelMatrix){
	physicsComponent = new PhysicsComponent(modelMatrix);
}

void VirtualObject::setPhysicsComponent(glm::vec3 min, glm::vec3 max){
	physicsComponent = new PhysicsComponent(min, max);
}

void VirtualObject::setPhysicsComponent(float radius, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass);
}

void VirtualObject::setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass);

}

glm::mat4 VirtualObject::getModelMatrix(){
	return modelMatrix;
}

void VirtualObject::setModelMatrix(glm::mat4 modelmatrix){
	modelMatrix = modelmatrix;
}
