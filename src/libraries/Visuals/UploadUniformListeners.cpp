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
	 FrameBufferObject* fbo = RenderManager::getInstance()->getCurrentFBO();
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();

	 glActiveTexture(GL_TEXTURE4);
	 glEnable(GL_TEXTURE_2D);
	 fbo->bindPositionTexture();
	 shader->uploadUniform(4,"positionMap");
	 fbo->unbindTexture();
	 glActiveTexture(GL_TEXTURE0);
 }

UploadUniformNormalMapListener::UploadUniformNormalMapListener(std::string name){
	setName(name);
}

 void UploadUniformNormalMapListener::update(){
	 FrameBufferObject* fbo = RenderManager::getInstance()->getCurrentFBO();
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();

	 glActiveTexture(GL_TEXTURE5);
	 glEnable(GL_TEXTURE_2D);
	 fbo->bindNormalTexture();
	 shader->uploadUniform(5,"normalMap");
	 fbo->unbindTexture();
	 glActiveTexture(GL_TEXTURE0);
 }

UploadUniformColorMapListener::UploadUniformColorMapListener(std::string name){
	setName(name);
}

 void UploadUniformColorMapListener::update(){
	 FrameBufferObject* fbo = RenderManager::getInstance()->getCurrentFBO();
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();

	 glActiveTexture(GL_TEXTURE6);
	 glEnable(GL_TEXTURE_2D);
	 fbo->bindColorTexture();
	 shader->uploadUniform(6,"colorMap");
	 fbo->unbindTexture();
	 glActiveTexture(GL_TEXTURE0);
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
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 glActiveTexture(GL_TEXTURE0);
	 glEnable(GL_TEXTURE_2D);
	 gc->getMaterial()->getDiffuseMap()->bindTexture();
	 shader->uploadUniform(0,"diffuseMap");
	 gc->getMaterial()->getDiffuseMap()->unbindTexture();
 }

 UploadUniformBumpMapListener::UploadUniformBumpMapListener(std::string name){
 	setName(name);
 }

 void UploadUniformBumpMapListener::update(){
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 glActiveTexture(GL_TEXTURE1);
	 glEnable(GL_TEXTURE_2D);
	 gc->getMaterial()->getNormalMap()->bindTexture();
	 shader->uploadUniform(1,"normalMap");
	 gc->getMaterial()->getNormalMap()->unbindTexture();
	 glActiveTexture(GL_TEXTURE0);
 }

 UploadUniformShininessListener::UploadUniformShininessListener(std::string name){
 	setName(name);
 }

 void UploadUniformShininessListener::update(){
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 shader->uploadUniform(gc->getMaterial()->getSpecularTerm(), "uniformShininess");
 }

 UploadUniformDiffuseColorListener::UploadUniformDiffuseColorListener(std::string name){
 	setName(name);
 }

 void UploadUniformDiffuseColorListener::update(){
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 shader->uploadUniform(gc->getMaterial()->getDiffuse(), "uniformDiffuseColor");
 }

 UploadUniformAmbientColorListener::UploadUniformAmbientColorListener(std::string name){
 	setName(name);
 }

 void UploadUniformAmbientColorListener::update(){
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 shader->uploadUniform(gc->getMaterial()->getAmbient(), "uniformAmbientColor");
 }

 UploadUniformSpecularColorListener::UploadUniformSpecularColorListener(std::string name){
 	setName(name);
 }

 void UploadUniformSpecularColorListener::update(){
	 Shader* shader = RenderManager::getInstance()->getCurrentShader();
	 GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	 shader->uploadUniform(gc->getMaterial()->getSpecular(), "uniformSpecularColor");
 }
