/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader(string directory, string shaderName) {

	string vertexshader = SHADERS_PATH + directory + shaderName + ".vert";
	string fragmentshader = SHADERS_PATH + directory + shaderName + ".frag";
	mProgramHandle = ShaderTools::makeShaderProgram(vertexshader.c_str(),
			fragmentshader.c_str());
	mShaderName = shaderName;
}

Shader::~Shader() {}

std::string Shader::getShaderName(){
	return mShaderName;
}
GLuint Shader::getProgramHandle(){
	return mProgramHandle;
}

void Shader :: uploadUniforms(GraphicsComponent* graphcomp){
}

void Shader :: uploadModelMatrix(glm::mat4 modelMatrix){
	GLuint modelHandle = glGetUniformLocation(mProgramHandle, "uniformModel");
	if(modelHandle != -1)
		glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Shader :: uploadViewMatrix (glm::mat4 viewMatrix){
	GLuint viewHandle = glGetUniformLocation(mProgramHandle, "viewModel");
	if(viewHandle != -1)
		glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Shader :: uploadProjectionMatrix (glm::mat4 projectionMatrix){
	GLuint projectionHandle = glGetUniformLocation(mProgramHandle, "projectionModel");
	if(projectionHandle != -1)
		glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Shader :: uploadInverseMatrix (glm::mat4 modelMatrix, glm::mat4 viewMatrix){
	GLuint inverseHandle = glGetUniformLocation(mProgramHandle, "inverseModel");
	if(inverseHandle != -1){
		glm::mat4 inverseMatrix = glm::transpose(glm::inverse(modelMatrix * viewMatrix));
		glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, glm::value_ptr(inverseMatrix));
	}
}

