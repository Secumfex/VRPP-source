#include <iostream>
#include "GraphicsComponent.h"

using namespace std;

GraphicsComponent::GraphicsComponent(){
	mMaterial = new Material();
	mMesh = new Mesh();
}

GraphicsComponent::GraphicsComponent(Mesh* mesh, Material* material){
	mMesh = mesh;
	mMaterial = material;
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
