/*
 * UploadUniformListeners.cpp
 *
 *  Created on: 28.01.2014
 *      Author: Raphimulator
 */

#include "Visuals/UploadUniformListeners.h"


 void UploadUniformModelMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();

 	glm::mat4 model = currentVO->getModelMatrix();
 	shader->uploadUniform(model, "uniformModel");
 }

 void UploadUniformViewMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	Camera* activeCamera = RenderManager::getInstance()->getCamera();

 	glm::mat4 view = activeCamera->getViewMatrix();
 	shader->uploadUniform(view, "uniformView");
 }

 void UploadUniformProjectionMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();

 	glm::mat4 model = RenderManager::getInstance()->getProjectionMatrix();
 	shader->uploadUniform(model, "uniformProjection");
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

 void UploadUniformPositionMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 void UploadUniformNormalMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 void UploadUniformColorMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 void UploadUniformDepthMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 void UploadUniformDiffuseMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }

 void UploadUniformBumpMapListener::update(){
	 //TODO: implementieren (GBUFFER)
 }
