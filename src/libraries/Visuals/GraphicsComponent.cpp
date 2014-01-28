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

void GraphicsComponent::setDynamic(bool dyn){
dynamic=dyn;
}
	
bool GraphicsComponent::getDynamic(){
return dynamic;}

	void GraphicsComponent::setModelMatrixGc(glm::mat4 matrix){
	modelMatrixGc=matrix;
	}

	glm::mat4 GraphicsComponent::getModelMatrix(){
	return modelMatrixGc;}

	void GraphicsComponent::setPivot(glm::vec3 piv){
	pivot=piv;}


	glm::vec3 GraphicsComponent::getPivot(){
	return pivot;}
