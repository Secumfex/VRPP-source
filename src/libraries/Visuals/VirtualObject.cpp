#include <iostream>
#include "VirtualObject.h"

#include <glm/glm.hpp>
#include "Application/ApplicationStates.h"


using namespace std;

int lastID = 0;


VirtualObject::VirtualObject() {
	modelMatrix = glm::mat4(); 	//loadidentity

	mCenterOfMassOffsetMatrix = glm::mat4(); 	//loadidentity

	physicsComponent = new PhysicsComponent();
}

VirtualObject::VirtualObject(VirtualObject* vo){
	unsigned int i;

	for (i = 0; i < vo->getGraphicsComponent().size(); ++i) {
		this->addGraphicsComponent(new GraphicsComponent(vo->getGraphicsComponent()[i]));
	}
	this->setModelMatrix(vo->getModelMatrix());
	this->setAnimation(new AnimationLoop(vo->getAnimation()));
	physicsComponent = new PhysicsComponent(vo->getPhysicsComponent());
	cout << "bla" << endl;
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
	//this->setModelMatrix(glm::scale(glm::mat4(1.0f), scale));

	physicsComponent->scale(scale, this);
	//updateModelMatrixViaPhysics();
	//this->setModelMatrix(modelMatrix);

	//modelMatrix = modelMatrix*glm::scale(glm::mat4(1.0f), scale);
	/*
	for(unsigned int i=0; i< mGraphComponent.size();i++){
		mGraphComponent[i]->setModelMatrixGc(glm::scale(glm::mat4(1.0f), scale));
	}
	 */

	/*
	  1) update the scaling on the btCollisionShape derived class
2) calculate new localinertia on that collision shape
3) call the setMassProps(mass,updatedLocalInertia) on btRigidBody
4) call the updateInertiaTensor on the btRigidBody
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

void VirtualObject::setPhysicsComponent(float x, float y, float z, btTriangleMesh btMesh, btTriangleIndexVertexArray* btTIVA){
	if(physicsComponent != NULL)
		physicsComponent->~PhysicsComponent();

	physicsComponent = new PhysicsComponent(x,y,z, btMesh, mGraphComponent, btTIVA);

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


void VirtualObject::setPhysicsComponent(float x, float y, float z, glm::vec3 normal, float mass, int collisionFlag){
	if(physicsComponent != NULL)
		physicsComponent->~PhysicsComponent();

	physicsComponent = new PhysicsComponent(x,y,z,normal,mass,collisionFlag);

}

glm::mat4 VirtualObject::getModelMatrix(){

	//TODO what was this supposed to do ?

	/* glm::mat4 gcmodelmatrix = glm::mat4(1.0f);
    unsigned int i = 0;
    for (i = 0; i< mGraphComponent.size();i++){
        gcmodelmatrix = mGraphComponent[i]->getModelMatrix() * gcmodelmatrix;

    }
    gcmodelmatrix = modelMatrix;
	 */
	return modelMatrix;
}

void VirtualObject::setModelMatrix(glm::mat4 modelmatrix){
	modelMatrix = modelmatrix;

	//TODO GC model matrices should not be effected, since they are "local", does everything still work as expected?

	//unsigned int i = 0;
	//for(i=0; i< mGraphComponent.size();i++){
	//	mGraphComponent[i]->setModelMatrixGc(modelmatrix);
	//}
}

PhysicsComponent* VirtualObject::getPhysicsComponent(){
	return physicsComponent;
}

const glm::mat4& VirtualObject::getCenterOfMassOffsetMatrix() const {
	return mCenterOfMassOffsetMatrix;
}

void VirtualObject::setCenterOfMassOffsetMatrix(
		const glm::mat4& centerOfMassOffsetMatrix) {
	mCenterOfMassOffsetMatrix = centerOfMassOffsetMatrix;}
void VirtualObject::setAnimation(AnimationLoop* animation){
	mAnimation = animation;
}
AnimationLoop* VirtualObject::getAnimation(){
	return mAnimation;
}
