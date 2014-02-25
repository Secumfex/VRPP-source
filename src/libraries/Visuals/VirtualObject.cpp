#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>

using namespace std;

int lastID = 0;


VirtualObject::VirtualObject() {
	modelMatrix = glm::mat4(); 	//loadidentity

	physicsComponent = new PhysicsComponent();
}

VirtualObject::VirtualObject(glm::vec3 min, glm::vec3 max){
	physicsComponent = new PhysicsComponent(min,max);

	physicsComponent->update();
	modelMatrix = physicsComponent->getModelMatrix();
}

VirtualObject::VirtualObject(float radius, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass);

	physicsComponent->update();
	modelMatrix = physicsComponent->getModelMatrix();
}

VirtualObject::VirtualObject(float width, float height, float depth, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass);

	physicsComponent->update();
	modelMatrix = physicsComponent->getModelMatrix();
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

vector<GraphicsComponent*> VirtualObject:: getGraphicsComponent(std::string tag){
	vector<GraphicsComponent*> cg_list;
	unsigned int i = 0;
	for (i = 1; i <= mGraphComponent.size(); ++i) {
		std::string temp = mGraphComponent[mGraphComponent.size()-i]->getMaterial()->getName();
		if(temp.find(tag) != std::string::npos )
			cg_list.push_back(mGraphComponent[mGraphComponent.size()-i]);
	}
	return cg_list;
}

void VirtualObject::setPhysicsComponent(){
	physicsComponent = new PhysicsComponent();
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

void VirtualObject::setPhysicComponent(float x, float y, float z, btVector3 normal, float mass){	//todo: change the type of normal
	physicsComponent = new PhysicsComponent(x,y,z,normal,mass);
}

glm::mat4 VirtualObject::getModelMatrix(){
	return modelMatrix;
}

void VirtualObject::setModelMatrix(glm::mat4 modelmatrix){
	modelMatrix = modelmatrix;
}

PhysicsComponent* VirtualObject::getPhysicsComponent(){
	return physicsComponent;
}
