#include <iostream>
#include "GraphicsComponent.h"

using namespace std;

GraphicsComponent::GraphicsComponent(){
	mMaterial = new Material();
	mMesh = new Mesh();
	mTranparency = false;
	mEmission = false;
	mShadow = false;
	mDynamic = false;
	mAnimated = false;
	mGhostObject = new btGhostObject();
}

GraphicsComponent::GraphicsComponent(GraphicsComponent* gc){
	this->setAnimated(gc->hasAnimation());
	this->setDynamic(gc->isDynamic());
	this->setEmission(gc->hasEmission());
	this->setShadow(gc->hasShadow());
	this->setTransparency(gc->hasTransparency());
	mGhostObject = new btGhostObject();
	mGhostObject->setCollisionShape(gc->getGhostObject()->getCollisionShape());
	this->setModelMatrixGc(gc->getModelMatrix());

	this->setMesh(new Mesh(gc->getMesh()));
	this->setMaterial(new Material(gc->getMaterial()));

	unsigned int i;
	for (i = 0; i < gc->getBones().size(); ++i) {
	this->addBone(gc->getBones()[i]);
	}

}

GraphicsComponent::GraphicsComponent(Mesh* mesh, Material* material){
	mMesh = mesh;
	mMaterial = material;
	mEmission = false;
	mAnimated = false;
	mDynamic = false;
	mTranparency = false;
	mShadow = false;
	mGhostObject = new btGhostObject();
}
void GraphicsComponent::setMesh(Mesh* mesh){
	mMesh = mesh;
}
void GraphicsComponent::setMaterial(Material* material){
	mMaterial = material;
}

Mesh* GraphicsComponent::getMesh(){
	return mMesh;
}
Material* GraphicsComponent::getMaterial(){
	return mMaterial;
}

void GraphicsComponent::setDynamic(bool value){
	mDynamic=value;
}

bool GraphicsComponent::isDynamic(){
	return mDynamic;}

void GraphicsComponent::setModelMatrixGc(glm::mat4 matrix){
	modelMatrixGc=matrix;
	btTransform t;
	float * mat = glm::value_ptr(matrix);
	t.setFromOpenGLMatrix(mat);
	mGhostObject->setWorldTransform(t);
}

glm::mat4 GraphicsComponent::getModelMatrix(){
	return modelMatrixGc;}

void GraphicsComponent:: setEmission(bool value){
	mEmission = value;
}
void GraphicsComponent:: setShadow(bool value){
	mShadow = value;
}
void GraphicsComponent::setTransparency(bool value){
	mTranparency = value;
}

bool GraphicsComponent:: hasEmission(){
	return mEmission;
}
bool GraphicsComponent:: hasShadow(){
	return mShadow;
}
bool GraphicsComponent:: hasTransparency(){
	return mTranparency;
}

void GraphicsComponent:: setGhostObject(glm::vec3 min, glm::vec3 max){

	glm::vec3 midpoint = (min + max) * 0.5f;
	max = max - midpoint;
	btBoxShape* shape = new btBoxShape(btVector3(max.x, max.y, max.z));
	mGhostObject->setCollisionShape(shape);
	mGhostObject->setCollisionFlags(4);

	setModelMatrixGc(glm::mat4(1.0f));
	PhysicWorld::getInstance()->dynamicsWorld->addCollisionObject(mGhostObject);
}
btGhostObject* GraphicsComponent::getGhostObject(){
	return mGhostObject;
}
void GraphicsComponent::addBone(Bone* bone){
	mBones.push_back(bone);
}

vector<Bone*> GraphicsComponent::getBones(){
	return mBones;
}

void GraphicsComponent::setAnimated(bool animated){
	mAnimated = animated;
}

bool GraphicsComponent::hasAnimation(){
	return mAnimated;
}
