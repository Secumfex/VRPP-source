/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

Shader::Shader(){


	mProgramHandle = ShaderTools::makeShaderProgram();

	blurStrength = 0.0f;

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


	    mUniformHandles.insert(std::pair<std::string, GLuint>(name, location));
	    mUniformNames.push_back(name);
	    attachUniformListener(name);
}
}
Shader::Shader(std::string vertexShader, std::string fragmentShader) {

	std::string vertexshader = vertexShader ;
	std::string fragmentshader = fragmentShader ;

	makeShader(vertexShader, fragmentShader);

	blurStrength = 0.0f;

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


	    mUniformHandles.insert(std::pair<std::string, GLuint>(name, location));
	    mUniformNames.push_back(name);
	    attachUniformListener(name);
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

void Shader :: uploadAllUniforms(){
notify("UNIFORMUPLOADLISTENER");
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
bool Shader::uploadUniform(GLfloat uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
	glUniform1f(mUniformHandles[uniformName], uniformVariable);
	return true;
	}else
		return false;
}
bool Shader::uploadUniform(GLint uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
	glUniform1i(mUniformHandles[uniformName], uniformVariable);
	return true;
	}else
		return false;
}

void Shader::useProgram(){
	glUseProgram(mProgramHandle);
}

void Shader::render(GraphicsComponent *gc){
	glBindVertexArray(gc->getMesh()->getVAO());
	glDrawElements(GL_TRIANGLES, gc->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
}


bool Shader::hasUniform(std::string uniformName){

	unsigned int i = 0;
	for (i = 0; i < mUniformNames.size(); ++i) {
		if(uniformName == mUniformNames[i])
			return true;
	}
	return false;
}


std::vector<std::string> Shader::getUniformNames(){
return std::vector<std::string>(mUniformNames);

}

void Shader::setBlurStrength(int strength){
	blurStrength = strength;
}

GLint Shader::getBlurStrength(){
	return blurStrength;
}

void Shader::attachUniformListener(std::string uniform){

	if(uniform == "uniformModel"){
		attach(new UploadUniformModelMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "uniformView"){
		attach(new UploadUniformViewMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "uniformProjection"){
		attach(new UploadUniformProjectionMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "uniformInverse"){
		attach(new UploadUniformInverseModelViewMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "positionMap"){
		attach(new UploadUniformPositionMapListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "normalMap"){
		attach(new UploadUniformNormalMapListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "colorMap"){
		attach(new UploadUniformColorMapListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "materialMap"){
		attach(new UploadUniformMaterialMapListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "depthMap"){
		attach(new UploadUniformDepthMapListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "diffuseTexture"){
		attach(new UploadUniformDiffuseTextureListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "normalTexture"){
		attach(new UploadUniformNormalTextureListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "ambientColor"){
		attach(new UploadUniformAmbientColorListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "diffuseColor"){
		attach(new UploadUniformDiffuseColorListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "specularColor"){
		attach(new UploadUniformSpecularColorListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "shininess"){
		attach(new UploadUniformShininessListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "emissiveColor"){
		attach(new UploadUniformEmissiveColorListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "resX"){
			attach(new UploadUniformResolutionXListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "resY"){
			attach(new UploadUniformResolutionYListener("UNIFORMUPLOADLISTENER"));}
	else {
		std::cout << "ERROR: Uniform \"" << uniform << "\" is not a valid uniform name." << std:: endl;
	}
}
