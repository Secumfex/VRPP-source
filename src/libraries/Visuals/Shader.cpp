/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader() {}

Shader::~Shader() {}

//TODO: dafuer sorgen dass man keinen Shader erstellen kann, sondern nur Kinder

std::string Shader::getShaderName(){
	return mShaderName;
}
void Shader::setProgramHandle(GLuint handle){}
	GLuint Shader::getProgramHandle(){
	return mProgramHandle;
}
	GLuint Shader:: getProgramHandle(){
		return mProgramHandle;
	}

/**-----------PHONG SHADER----------*/

Phong:: Phong(){

	mProgramHandle = ShaderTools::makeShaderProgram(SHADERS_PATH "/Phong/phong.vert",
                                                   SHADERS_PATH "/Phong/phong.frag");

	modelHandle = glGetUniformLocation(mProgramHandle, "uniformModel");
	viewHandle = glGetUniformLocation(mProgramHandle, "viewModel");
	inverseHandle = glGetUniformLocation(mProgramHandle, "inverseModel");
	projectionHandle = glGetUniformLocation(mProgramHandle, "projectionModel");
}

void Phong::uploadUniforms(GraphicsComponent* graphcomp){
}

void Phong::uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glm::mat4 inverseMatrix = glm::value_ptr(glm::transpose(glm::inverse(modelMatrix * viewMatrix)));
	glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, inverseMatrix);
}
