/*
 * UploadUniformListeners.cpp
 *
 *  Created on: 28.01.2014
 *      Author: Raphimulator
 */

#include "Visuals/UploadUniformListeners.h"

#include "Visuals/RenderManager.h"

UploadUniformModelMatrixListener::UploadUniformModelMatrixListener(std::string name){
	setName(name);
}

 void UploadUniformModelMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();

 	glm::mat4 model = currentVO->getModelMatrix();
 	shader->uploadUniform(model, "uniformModel");
 }

UploadUniformViewMatrixListener::UploadUniformViewMatrixListener(std::string name){
	setName(name);
}

 void UploadUniformViewMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	Camera* activeCamera = RenderManager::getInstance()->getCamera();

 	glm::mat4 view = activeCamera->getViewMatrix();
 	shader->uploadUniform(view, "uniformView");
 }

UploadUniformProjectionMatrixListener::UploadUniformProjectionMatrixListener(std::string name){
	setName(name);
}

 void UploadUniformProjectionMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();

 	glm::mat4 model = RenderManager::getInstance()->getProjectionMatrix();
 	shader->uploadUniform(model, "uniformProjection");
 }

UploadUniformInverseModelViewMatrixListener::UploadUniformInverseModelViewMatrixListener(std::string  name){
	setName(name);
}

 void UploadUniformInverseModelViewMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();
 	Camera* activeCamera = RenderManager::getInstance()->getCamera();

 	glm::mat4 model = currentVO->getModelMatrix();
 	glm::mat4 view = activeCamera->getViewMatrix();

 	glm::mat4 transposeInverseModelView = glm::transpose(glm::inverse(view * model));

 	shader->uploadUniform(transposeInverseModelView, "uniformInverse");
 }

UploadUniformPositionMapListener::UploadUniformPositionMapListener(std::string name){
	setName(name);
}

 void UploadUniformPositionMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

UploadUniformNormalMapListener::UploadUniformNormalMapListener(std::string name){
	setName(name);
}

 void UploadUniformNormalMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

UploadUniformColorMapListener::UploadUniformColorMapListener(std::string name){
	setName(name);
}

 void UploadUniformColorMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 UploadUniformDepthMapListener::UploadUniformDepthMapListener(std::string name){
 	setName(name);
 }

 void UploadUniformDepthMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 UploadUniformDiffuseMapListener::UploadUniformDiffuseMapListener(std::string name){
 	setName(name);
 }

 void UploadUniformDiffuseMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 UploadUniformBumpMapListener::UploadUniformBumpMapListener(std::string name){
 	setName(name);
 }

 void UploadUniformBumpMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }
