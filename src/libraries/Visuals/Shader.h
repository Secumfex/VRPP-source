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
#include "Visuals/UploadUniformListeners.h"
#include "Patterns/Subject.h"



class Shader : public Subject{

	//-----------------MEMBER FUNCTIONS-----------------
public:

	Shader();
	Shader(std::string vertexShader, std::string fragmentShader);
	virtual ~Shader();
	void setShaderName(std::string name);
	void uploadAllUniforms();
	void uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	std::string getShaderName();
	GLuint getProgramHandle();


	bool uploadUniform(glm::mat4 uniformMatrix, std::string uniformName);
	bool uploadUniform(glm::vec3 uniformVector, std::string uniformName);
	bool uploadUniform(GLfloat uniformVariable, std::string uniformName);
	bool uploadUniform(GLint uniformVariable, std::string uniformName);

	bool hasUniform(std::string uniformName);

	std::vector<std::string> getUniformNames();


	void useProgram();

	void render(GraphicsComponent *gc);

	void attachUniformListener(std::string uniform);

	void setBlurStrength(int strength);
	GLint getBlurStrength();

private:
	void makeShader(std::string vert, std::string frag);

	//-----------------MEMBER VARIABLES-----------------
protected:

	std::map<std::string, GLuint> mUniformHandles;

	std::vector<std::string> mUniformNames;

	std::string mShaderName;

	GLuint mProgramHandle;

	GLint blurStrength;

};

#endif /* SHADER_H_ */
