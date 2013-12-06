/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader() {
	// TODO Auto-generated constructor stub

}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

//TODO: dafuer sorgen dass man keinen Shader erstellen kann, sondern nur Kinder

char* Shader::getShaderPath(){
	return mShaderPath;
}
void Shader::setShaderHandle(GLuint handle){}
GLuint Shader::getShaderHandle(){
	return mShaderHandle;
}
