#include <iostream>
#include "GraphicsComponent.h"

using namespace std;

GraphicsComponent::GraphicsComponent(){
	mMaterial = new Material();
	mMesh = new Mesh();
	mTranparency = false;
	mEmission = false;
	mShadow = false;
	mAABB_Min = glm::vec3(0.0, 0.0, 0.0);
	mAABB_Max = glm::vec3(0.0, 0.0, 0.0);
}

GraphicsComponent::GraphicsComponent(Mesh* mesh, Material* material){
	mMesh = mesh;
	mMaterial = material;
	mTranparency = false;
	mEmission = false;
	mShadow = false;
	mAABB_Min = glm::vec3(0.0, 0.0, 0.0);
	mAABB_Max = glm::vec3(0.0, 0.0, 0.0);
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
void GraphicsComponent:: setBoundingBox(glm::vec3 min, glm::vec3 max){
	mAABB_Min = min;
	mAABB_Max = max;
}
glm::vec3 GraphicsComponent:: getBoundingBox_Min(){
	return mAABB_Min;
}
glm::vec3 GraphicsComponent:: getBoundingBox_Max(){
	return mAABB_Max;
}

