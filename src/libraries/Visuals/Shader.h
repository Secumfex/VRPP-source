/*
 * Shader.h
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <Visuals/GraphicsComponent.h>
#include <string>
#include "Tools/ShaderTools.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>


class Shader {

	//-----------------MEMBER FUNCTIONS-----------------
public:

	Shader(string vertexShader, string fragmentShader);
	virtual ~Shader();
	void setShaderName(string name);
	void uploadUniforms(GraphicsComponent* graphcomp);
	void uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	std::string getShaderName();
	GLuint getProgramHandle();

	bool uploadUniform(glm::mat4 uniformMatrix, string uniformName);
	bool uploadUniform(glm::vec3 uniformVector, string uniformName);
	bool uploadUniform(GLfloat uniformVariable, string uniformName);
	bool uploadUniform(GLint uniformVariable, string uniformName);

	void useProgram();

	void render(GraphicsComponent *gc);

private:
	void makeShader(string vert, string frag);

	//-----------------MEMBER VARIABLES-----------------
protected:
	std::map<std::string, GLuint> mUniformHandles;

	std::string mShaderName;
	GLuint mProgramHandle;
};

#endif /* SHADER_H_ */
