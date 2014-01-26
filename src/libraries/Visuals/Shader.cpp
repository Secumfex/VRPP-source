/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader(std::string vertexShader, std::string fragmentShader) {

	std::string vertexshader = vertexShader ;
	std::string fragmentshader = fragmentShader ;

	makeShader(vertexShader, fragmentShader);

	int total = -1;

	glGetProgramiv( mProgramHandle, GL_ACTIVE_UNIFORMS, &total );

	unsigned int i= 0;

	for(i=0; i<total; ++i)  {
	    int name_len=-1, num=-1;
	    GLenum type = GL_ZERO;
	    char name[100];
	    glGetActiveUniform( mProgramHandle, GLuint(i), sizeof(name)-1,
	        &name_len, &num, &type, name );
	    name[name_len] = 0;
	    GLuint location = glGetUniformLocation( mProgramHandle, name );

	    mUniformHandles.insert(pair<string, GLuint>(name, location));
	}

}

void Shader::makeShader(std::string vert, std::string frag){
	mProgramHandle = ShaderTools::makeShaderProgram(vert.c_str(),
			frag.c_str());
	setShaderName(vert + frag);
}

Shader::~Shader() {}

void Shader::setShaderName(std::string name){
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

bool Shader :: uploadUniform(glm::mat4 uniformMatrix, std::string uniformName){

	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
		glUniformMatrix4fv(mUniformHandles[uniformName], 1, GL_FALSE, glm::value_ptr(uniformMatrix));
		return true;
	}else
		return false;
}

bool Shader :: uploadUniform(glm::vec3 uniformVector, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
	glUniform3f(mUniformHandles[uniformName], uniformVector.x, uniformVector.y, uniformVector.z);
	return true;
	}else
		return false;
}
bool Shader :: uploadUniform(GLfloat uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
	glUniform1f(mUniformHandles[uniformName], uniformVariable);
	return true;
	}else
		return false;
}
bool Shader :: uploadUniform(GLint uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
	glUniform1i(mUniformHandles[uniformName], uniformVariable);
	return true;
	}else
		return false;
}

void Shader ::useProgram(){
	glUseProgram(mProgramHandle);
}

void Shader ::render(GraphicsComponent *gc){
	glBindVertexArray(gc->getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, gc->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
}
