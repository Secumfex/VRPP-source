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

void setPhysicsComponent(){
	PhysicsComponent physicsComponent = new PhysicsComponent();

}

void setPhysicsComponent(glm::mat4 modelMatrix){
	PhysicsComponent physicsComponent = new PhysicsComponent(modelMatrix);
}

void setPhysicsComponent(glm::vec3 min, glm::vec3 max){
	PhysicsComponent physicsComponent = new PhysicsComponent(min, max);
}

void setPhysicsComponent(float radius, float x, float y, float z, float mass){
	PhysicsComponent physicsComponent = new PhysicsComponent(radius, x, y, z, mass);
}

void setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass){
	PhysicsComponent physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass);
}
