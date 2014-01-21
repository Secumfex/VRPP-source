/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader(string vertexShader, string fragmentShader) {

	string vertexshader = vertexShader ;
	string fragmentshader = fragmentShader ;

	makeShader(vertexShader, fragmentShader);
}

void Shader::makeShader(string vert, string frag){
	mProgramHandle = ShaderTools::makeShaderProgram(vert.c_str(),
			frag.c_str());
	setShaderName(vert + frag);
}

Shader::~Shader() {}

void Shader::setShaderName(string name){
	mShaderName = name;
}

std::string Shader::getShaderName(){
	return mShaderName;
}
GLuint Shader::getProgramHandle(){
	return mProgramHandle;
}

void Shader :: uploadUniforms(GraphicsComponent* graphcomp){
}

void Shader :: uploadUniform(glm::mat4 uniformMatrix, string uniformName){
	GLuint modelHandle = glGetUniformLocation(mProgramHandle, uniformName.c_str());
	if(modelHandle != -1)
		glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(uniformMatrix));
}

void Shader :: uploadUniform(glm::vec3 uniformVector, string uniformName){
	GLuint modelHandle = glGetUniformLocation(mProgramHandle, uniformName.c_str());
	if(modelHandle != -1)
	glUniform3f(modelHandle, uniformVector.x, uniformVector.y, uniformVector.z);
}
void Shader :: uploadUniform(GLfloat uniformVariable, string uniformName){
	GLuint modelHandle = glGetUniformLocation(mProgramHandle, uniformName.c_str());
	if(modelHandle != -1)
	glUniform1f(modelHandle, uniformVariable);
}
void Shader :: uploadUniform(GLint uniformVariable, string uniformName){
	GLuint modelHandle = glGetUniformLocation(mProgramHandle, uniformName.c_str());
	if(modelHandle != -1)
	glUniform1i(modelHandle, uniformVariable);
}

void Shader ::useProgram(){
	glUseProgram(mProgramHandle);
}

void Shader ::render(GraphicsComponent *gc){
	glBindVertexArray(gc->getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, gc->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
}
