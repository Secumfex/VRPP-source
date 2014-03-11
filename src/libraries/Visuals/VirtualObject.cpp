#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>

#include "Visuals/RenderQueue.h"

using namespace std;

int lastID = 0;


VirtualObject::VirtualObject() {
	modelMatrix = glm::mat4(); 	//loadidentity

	physicsComponent = new PhysicsComponent();
}

VirtualObject::VirtualObject(glm::vec3 min, glm::vec3 max){
	physicsComponent = new PhysicsComponent(min,max);

	physicsComponent->update(this);
}

VirtualObject::VirtualObject(float radius, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass);

	physicsComponent->update(this);
}

VirtualObject::VirtualObject(float width, float height, float depth, float x, float y, float z, float mass){
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass);

	physicsComponent->update(this);
}

VirtualObject::~VirtualObject() {
	//delete graphicsComponent;
	delete physicsComponent;
}

void VirtualObject::translate(glm::vec3 trans){
	physicsComponent->translate(trans);
	updateModelMatrixViaPhysics();
	for(unsigned int i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(modelMatrix);
	}
}

void VirtualObject::scale(glm::vec3 scale){
	physicsComponent->scale(scale);
	updateModelMatrixViaPhysics();
	for(unsigned int i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(modelMatrix);
	}
}

void VirtualObject::updateModelMatrixViaPhysics() {
	physicsComponent->update(this);
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
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent();
}

void VirtualObject::setPhysicsComponent(glm::vec3 min, glm::vec3 max){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent(min, max);
}

void VirtualObject::setPhysicsComponent(float radius, float x, float y, float z, float mass){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass);
}

void VirtualObject::setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass);
}

void VirtualObject::setPhysicComponent(float x, float y, float z, btVector3& normal, float mass){	//todo: change the type of normal
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
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
