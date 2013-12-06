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
    GLint positionMapHandle = glGetUniformLocation(mProgramHandle, "ambient");

	GLfloat ambient = glGetUniformLocation(programHandle, "ambient");
	GLfloat diffuse = glGetUniformLocation(programHandle, "diffuse");
	GLfloat specular = glGetUniformLocation(programHandle, "specular");
	GLfloat specularTerm = glGetUniformLocation(programHandle, "specularTerm");
}

void Phong::fillShader(Material* mat, Mesh* mesh){

	glUniform3f(ambient, mat->mAmbColor);
}
