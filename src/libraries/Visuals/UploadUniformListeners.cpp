/*
 * UploadUniformListeners.cpp
 *
 *  Created on: 28.01.2014
 *      Author: Raphimulator
 */

#include "Visuals/UploadUniformListeners.h"

#include "Visuals/RenderManager.h"
#include "IO/IOManager.h"

UploadUniformModelMatrixListener::UploadUniformModelMatrixListener(std::string name){
	setName(name);
}

void UploadUniformModelMatrixListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();

	if (currentVO)
	{
		glm::mat4 model = currentVO->getModelMatrix();
		shader->uploadUniform(model, "uniformModel");
	}
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

UploadUniformPerspectiveMatrixListener::UploadUniformPerspectiveMatrixListener(std::string name){
	setName(name);
}

void UploadUniformPerspectiveMatrixListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glm::mat4 model = RenderManager::getInstance()->getPerspectiveMatrix();
	shader->uploadUniform(model, "uniformPerspective");
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

UploadUniformLightPerspectiveMatrixListener::UploadUniformLightPerspectiveMatrixListener(std::string  name){
	setName(name);
}

void UploadUniformLightPerspectiveMatrixListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glm::mat4 lightPerspectiveMatrix = RenderManager::getInstance()->getLightPerspectiveMatrix(0);

	shader->uploadUniform(lightPerspectiveMatrix, "uniformLightPerspective");
}

UploadUniformPositionMapListener::UploadUniformPositionMapListener(std::string name, FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}

void UploadUniformPositionMapListener::update(){
	FrameBufferObject* fbo = mSourceFBO;
	if(!fbo) {
		fbo = RenderManager::getInstance()->getCurrentFBO();
	}

	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glActiveTexture(GL_TEXTURE4);
	glEnable(GL_TEXTURE_2D);
	if (fbo){
		if (fbo->getPositionTextureHandle() != -1){
			fbo->bindPositionTexture();
			shader->uploadUniform(4,"positionMap");	//upload only if texture exists
		}
	}
}

UploadUniformNormalMapListener::UploadUniformNormalMapListener(std::string name, FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}

void UploadUniformNormalMapListener::update(){
	FrameBufferObject* fbo = mSourceFBO;
	if(!fbo) {
		fbo = RenderManager::getInstance()->getCurrentFBO();
	}Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glActiveTexture(GL_TEXTURE5);
	glEnable(GL_TEXTURE_2D);if (fbo){
		if (fbo->getNormalTextureHandle() != -1){
			fbo->bindNormalTexture();
			shader->uploadUniform(5,"normalMap"); //upload only if texture exists
		}
	}
}

UploadUniformColorMapListener::UploadUniformColorMapListener(std::string name, FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}

void UploadUniformColorMapListener::update(){
	FrameBufferObject* fbo = mSourceFBO;
	if(!fbo) {
		fbo = RenderManager::getInstance()->getCurrentFBO();
	}
	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glActiveTexture(GL_TEXTURE6);
	glEnable(GL_TEXTURE_2D);
	if (fbo){
		if (fbo->getColorTextureHandle() != -1){
			fbo->bindColorTexture();
			shader->uploadUniform(6,"colorMap"); //upload only if texture exists
		}
	}
}
UploadUniformShadowMapListener::UploadUniformShadowMapListener(std::string name, FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}
void UploadUniformShadowMapListener::update(){
	FrameBufferObject* fbo = mSourceFBO;
	if(!fbo) {
		fbo = RenderManager::getInstance()->getCurrentFBO();
	}
	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	glActiveTexture(GL_TEXTURE8);
	glEnable(GL_TEXTURE_2D);
	if (fbo){
		if (fbo->getShadowMapHandle() != -1){
			fbo->bindShadowMap();
			shader->uploadUniform(8,"shadowMap"); //upload only if texture exists
		}
	}
}
UploadUniformSpecularMapListener::UploadUniformSpecularMapListener(std::string name, FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}

void UploadUniformSpecularMapListener::update(){
	FrameBufferObject* fbo = mSourceFBO;
	if(!fbo) {
		fbo = RenderManager::getInstance()->getCurrentFBO();
	}
	Shader* shader = RenderManager::getInstance()->getCurrentShader();


	glActiveTexture(GL_TEXTURE7);
	glEnable(GL_TEXTURE_2D);
	if (fbo){
		if (fbo->getSpecularTextureHandle() != -1){
			fbo->bindSpecularTexture();
			shader->uploadUniform(7,"specularMap"); //upload only if texture exists
		}
	}
}

UploadUniformDepthMapListener::UploadUniformDepthMapListener(std::string name,FrameBufferObject* source_fbo){
	setName(name);
	mSourceFBO = source_fbo;
}

void UploadUniformDepthMapListener::update(){
	//TODO: implementieren (GBUFFER)
}



UploadUniformDiffuseTextureListener::UploadUniformDiffuseTextureListener(std::string name){
	setName(name);
}

void UploadUniformDiffuseTextureListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	gc->getMaterial()->getDiffuseMap()->bindTexture();

	shader->uploadUniform(0,"diffuseTexture");
}

UploadUniformNormalTextureListener::UploadUniformNormalTextureListener(std::string name){
	setName(name);
}

void UploadUniformNormalTextureListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	gc->getMaterial()->getNormalMap()->bindTexture();
	shader->uploadUniform(1,"normalTexture");
	glActiveTexture(GL_TEXTURE0);
}

UploadUniformShininessListener::UploadUniformShininessListener(std::string name){
	setName(name);
}

void UploadUniformShininessListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	shader->uploadUniform(gc->getMaterial()->getShininess(), "shininess");
}

void UploadUniformTransparencyListener::update(){

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	shader->uploadUniform(gc->getMaterial()->getTransparency(), "transparency");
}

UploadUniformDiffuseColorListener::UploadUniformDiffuseColorListener(std::string name){
	setName(name);
}


void UploadUniformDiffuseColorListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();


	shader->uploadUniform(gc->getMaterial()->getDiffuse(), "diffuseColor");
}

UploadUniformAmbientColorListener::UploadUniformAmbientColorListener(std::string name){
	setName(name);
}

void UploadUniformAmbientColorListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	shader->uploadUniform(gc->getMaterial()->getAmbient(), "ambientColor");
}

UploadUniformSpecularColorListener::UploadUniformSpecularColorListener(std::string name){
	setName(name);
}

void UploadUniformSpecularColorListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();

	shader->uploadUniform(gc->getMaterial()->getSpecular(), "specularColor");
}

UploadUniformEmissiveColorListener::UploadUniformEmissiveColorListener(std::string name){
	setName(name);
}

void UploadUniformEmissiveColorListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	GraphicsComponent* gc = RenderManager::getInstance()->getCurrentGC();
	if (gc->hasEmission()){
		shader->uploadUniform(gc->getMaterial()->getEmission(), "emissiveColor");
	}else{
		shader->uploadUniform(glm::vec3(0.0, 0.0, 0.0) , "emissiveColor");
	}
}

UploadUniformBlurStrengthListener::UploadUniformBlurStrengthListener(std::string name){
	setName(name);
}

void UploadUniformBlurStrengthListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();

	shader->uploadUniform(shader->getBlurStrength(), "blurStrength");
}

UploadUniformResolutionXListener::UploadUniformResolutionXListener(std::string name){
	setName(name);
}

void UploadUniformResolutionXListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	FrameBufferObject* fbo = RenderManager::getInstance()->getCurrentFBO();
	if(!fbo)	//window is active
	{
		shader->uploadUniform(IOManager::getInstance()->getWidth(), "resX");
	}
	else{
		shader->uploadUniform(fbo->getWidth(), "resX");
	}
}
UploadUniformResolutionYListener::UploadUniformResolutionYListener(std::string name){
	setName(name);
}

void UploadUniformResolutionYListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	FrameBufferObject* fbo = RenderManager::getInstance()->getCurrentFBO();
	if(!fbo)	//window is active
	{
		shader->uploadUniform(IOManager::getInstance()->getHeight(), "resY");
	}
	else{
		shader->uploadUniform(fbo->getWidth(), "resY");
	}
}

UploadUniformWindowTimeListener::UploadUniformWindowTimeListener(std::string name)
{
	setName(name);
}

void UploadUniformWindowTimeListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	float time = IOManager::getInstance()->getWindowTime();
	shader->uploadUniform(time, "uniformTime");
}

UploadUniformVec3Listener::UploadUniformVec3Listener(std::string name, glm::vec3 vector, std::string uniform_name){
	setName(name);
	this->vector 	= new glm::vec3( vector );
	this->uniform_name 	= uniform_name;
}

UploadUniformVec3Listener::UploadUniformVec3Listener(std::string name, glm::vec3* vector, std::string uniform_name){
	setName(name);
	this->vector 	= vector;
	this->uniform_name 	= uniform_name;
}

void UploadUniformVec3Listener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( *vector, uniform_name);
}

UploadUniformFloatListener::UploadUniformFloatListener(std::string name, float value, std::string uniform_name){
	setName(name);
	this->value 	= new float(value);
	this->uniform_name 	= uniform_name;
}

UploadUniformFloatListener::UploadUniformFloatListener(std::string name, float* value, std::string uniform_name){
	setName(name);
	this->value 	= value;
	this->uniform_name 	= uniform_name;
}

void UploadUniformFloatListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( *value, uniform_name);
}

UploadUniformMat4Listener::UploadUniformMat4Listener(std::string name, glm::mat4 matrix, std::string uniform_name){
	setName(name);
	this->matrix 	= new glm::mat4( matrix );
	this->uniform_name 	= uniform_name;
}

UploadUniformMat4Listener::UploadUniformMat4Listener(std::string name, glm::mat4* matrix, std::string uniform_name){
	setName(name);
	this->matrix 	= matrix;
	this->uniform_name 	= uniform_name;
}

void UploadUniformMat4Listener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( *matrix, uniform_name);
}


UploadUniformIntListener::UploadUniformIntListener(std::string name, GLint value, std::string uniform_name){
	setName(name);
	this->value 		= new GLint( value );
	this->uniform_name 	= uniform_name;
}

UploadUniformIntListener::UploadUniformIntListener(std::string name, GLint* value, std::string uniform_name){
	setName(name);
	this->value 	= value;
	this->uniform_name 	= uniform_name;
}

void UploadUniformIntListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( *value, uniform_name);
}

UploadUniformTextureListener::UploadUniformTextureListener(std::string name, GLint unit, std::string uniform_name, GLuint texture_handle){
	setName(name);
	this->unit 	= unit;
	this->uniform_name 	= uniform_name;
	this->texture_handle = texture_handle;
}

void UploadUniformTextureListener::update(){
	glActiveTexture(GL_TEXTURE0 + unit);			// set active texture as target to load texture to
	glBindTexture(GL_TEXTURE_2D, texture_handle);	// load texture to active texture unit

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( unit, uniform_name);		// upload texture unit to shader uniform sampler2d variable
}

void UploadUniformTextureListener::setTextureHandle(GLuint texture_handle)
{
	this->texture_handle = texture_handle;
}

void UploadUniformTextureListener::setTextureUnit(GLint unit)
{
	this->unit = unit;
}

void UploadUniformTextureListener::setUniformName(std::string uniform_name)
{
	this->uniform_name = uniform_name;
}
