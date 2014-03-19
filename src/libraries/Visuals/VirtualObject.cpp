#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>
#include "Application/ApplicationStates.h"


using namespace std;

int lastID = 0;


VirtualObject::VirtualObject() {
	modelMatrix = glm::mat4(); 	//loadidentity

	physicsComponent = new PhysicsComponent();
}

VirtualObject::VirtualObject(glm::vec3 min, glm::vec3 max, float mass, int collisionFlag){
	physicsComponent = new PhysicsComponent(min,max, mass,collisionFlag);

	physicsComponent->update(this);

}

VirtualObject::VirtualObject(float radius, float x, float y, float z, float mass, int collisionFlag){
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass, collisionFlag);

	physicsComponent->update(this);
}

VirtualObject::VirtualObject(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag){
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass, collisionFlag);

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


		/*
	physicsComponent->translate(trans);

	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(trans.x, trans.y, trans.z));
	for(unsigned int i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(modelMatrix);
	}
	*/
}

void VirtualObject::scale(glm::vec3 scale){
	/*
	physicsComponent->scale(scale);
	//updateModelMatrixViaPhysics();

	modelMatrix = glm::scale(glm::mat4(1.0f), scale);
	for(unsigned int i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(modelMatrix);
	}
	*/
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
	for (i = 0; i < mGraphComponent.size(); ++i) {
		std::string temp = mGraphComponent[i]->getMaterial()->getName();
		if(temp.find(tag) != std::string::npos )
			cg_list.push_back(mGraphComponent[i]);
	}
	return cg_list;
}

void VirtualObject::setPhysicsComponent(){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent();
}

void VirtualObject::setPhysicsComponent(glm::vec3 min, glm::vec3 max, float mass, int collisionFlag){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();

	physicsComponent = new PhysicsComponent(min, max, mass,collisionFlag);
}

void VirtualObject::setPhysicsComponent(float radius, float x, float y, float z, float mass, int collisionFlag){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent(radius, x, y, z, mass,collisionFlag);
}

void VirtualObject::setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();
	physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass,collisionFlag);

}


void VirtualObject::setPhysicComponent(float x, float y, float z, glm::vec3 normal, float mass, int collisionFlag){
	if(physicsComponent != NULL)
	physicsComponent->~PhysicsComponent();

	physicsComponent = new PhysicsComponent(x,y,z,normal,mass,collisionFlag);

}

glm::mat4 VirtualObject::getModelMatrix(){
	return modelMatrix;
}

void VirtualObject::setModelMatrix(glm::mat4 modelmatrix){
	modelMatrix = modelmatrix;
	unsigned int i = 0;
	for(i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(modelmatrix);
	}
}

PhysicsComponent* VirtualObject::getPhysicsComponent(){
	return physicsComponent;
}
