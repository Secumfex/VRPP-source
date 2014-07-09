/*
 * Shader.cpp
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Shader.h>

#include <Visuals/RenderManager.h>

Shader::Shader(std::vector<const char*> shaders){

	const char* vert = 0;
	const char* geom = 0;
	const char* frag = 0;

	if(shaders.size() == 2){
		vert = shaders[0];
		frag = shaders[1];
	}
	else if(shaders.size() == 3){
		vert = shaders[0];
		geom =shaders[1];
		frag = shaders[2];
	}

	GLuint vertexShaderHandle;
	GLuint geometryShaderHandle;
	GLuint fragmentShaderHandle;

	mProgramHandle = glCreateProgram();

	if(vert != 0){
		vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
		const GLint source_size = strlen(vert);
		glShaderSource(vertexShaderHandle, 1, &vert, &source_size);
		glCompileShader(vertexShaderHandle);
		ShaderTools::checkShader(vertexShaderHandle);
        glAttachShader(mProgramHandle, vertexShaderHandle);
	}
	if(geom != 0){
		geometryShaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
		const GLint source_size = strlen(geom);
		glShaderSource(geometryShaderHandle, 1, &geom, &source_size);
		glCompileShader(geometryShaderHandle);
		ShaderTools::checkShader(geometryShaderHandle);
        glAttachShader(mProgramHandle, geometryShaderHandle);
	}
	if(frag != 0){
		fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		const GLint source_size = strlen(frag);
		glShaderSource(fragmentShaderHandle, 1, &frag, &source_size);
		glCompileShader(fragmentShaderHandle);
		ShaderTools::checkShader(fragmentShaderHandle);
        glAttachShader(mProgramHandle, fragmentShaderHandle);
	}

    glLinkProgram(mProgramHandle);

	blurStrength = 0.0f;

	getShaderInfo();

}

Shader::Shader(std::string vertexShader, std::string fragmentShader) {

	std::string vertexshader = vertexShader ;
	std::string fragmentshader = fragmentShader ;
	makeShader(vertexShader, fragmentShader);

	blurStrength = 0.0f;

	int total = -1;

	glGetProgramiv( mProgramHandle, GL_ACTIVE_UNIFORMS, &total );

	getShaderInfo();

}

void Shader::getShaderInfo(){
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


	total = glGetFragDataLocation(mProgramHandle, "colorOutput");
	if(total != -1){
		mOutputs.push_back("colorOutput");
		glBindFragDataLocation(mProgramHandle, total, "colorOutput");
	}
	total = glGetFragDataLocation(mProgramHandle, "normalOutput");
	if(total != -1){
		mOutputs.push_back("normalOutput");
		glBindFragDataLocation(mProgramHandle, total, "normalOutput");
	}
	total = glGetFragDataLocation(mProgramHandle, "positionOutput");
	if(total != -1){
		mOutputs.push_back("positionOutput");
		glBindFragDataLocation(mProgramHandle, total, "positionOutput");
	}
	total = glGetFragDataLocation(mProgramHandle, "specularOutput");
	if(total != -1){
		mOutputs.push_back("specularOutput");
		glBindFragDataLocation(mProgramHandle, total, "specularOutput");
	}
}

void Shader::useMinimalColorOutput(){
}

void Shader::makeShader(std::string vert, std::string frag){
	mProgramHandle = ShaderTools::makeShaderProgram(vert.c_str(),
			frag.c_str());
	setShaderName(vert + frag);
}

Shader::~Shader() {
	glDeleteProgram(mProgramHandle);
	for (list<Listener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
	 delete &it;
}
}

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
		if (mActiveUniformsMat4[uniformName] != uniformMatrix)
		{
			glUniformMatrix4fv(mUniformHandles[uniformName], 1, GL_FALSE, glm::value_ptr(uniformMatrix));
			mActiveUniformsMat4[uniformName] = uniformMatrix;
		}
		return true;
	}else
		return false;
}

bool Shader :: uploadUniform(glm::vec3 uniformVector, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
		if (mActiveUniformsVec3[uniformName] != uniformVector)
		{
			glUniform3f(mUniformHandles[uniformName], uniformVector.x, uniformVector.y, uniformVector.z);
			mActiveUniformsVec3[uniformName] = uniformVector;
		}
		return true;
	}else
		return false;
}
bool Shader::uploadUniform(GLfloat uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
		if ( mActiveUniformsFloat[uniformName] != uniformVariable)
		{
			glUniform1f(mUniformHandles[uniformName], uniformVariable);
			mActiveUniformsFloat[uniformName] = uniformVariable;
		}
		return true;
	}else
		return false;
}
bool Shader::uploadUniform(GLint uniformVariable, std::string uniformName){
	if(mUniformHandles.find(uniformName)!=mUniformHandles.end()){
		if (mActiveUniformsInt[uniformName] != uniformVariable)
		{
			glUniform1i(mUniformHandles[uniformName], uniformVariable);
			mActiveUniformsInt[uniformName] = uniformVariable;
		}
		return true;
	}else
		return false;
}

void Shader::useProgram(){
	glUseProgram(mProgramHandle);
}

void Shader::render(GraphicsComponent *gc){
	RenderManager::getInstance()->setCurrentVAO(gc->getMesh()->getVAO() );
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
	else if(uniform == "uniformPerspective"){
		attach(new UploadUniformPerspectiveMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "uniformInverse"){
		attach(new UploadUniformInverseModelViewMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "uniformLightPerspective"){
		attach(new UploadUniformLightPerspectiveMatrixListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "positionMap"){
		attach(new UploadUniformPositionMapListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "normalMap"){
		attach(new UploadUniformNormalMapListener(std::string("UNIFORMUPLOADLISTENER")));}
	else if(uniform == "colorMap"){
		attach(new UploadUniformColorMapListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "shadowMap"){
		attach(new UploadUniformShadowMapListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform == "specularMap"){
		attach(new UploadUniformSpecularMapListener("UNIFORMUPLOADLISTENER"));}
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
	else if(uniform == "uniformTime"){
		attach(new UploadUniformWindowTimeListener("UNIFORMUPLOADLISTENER"));}
	else if(uniform.find("uniformBoneTransform") != std::string::npos){
		attach(new UploadUniformBoneTransformationListener("UNIFORMUPLOADLISTENER", uniform));}
	else {
		std::cout << "WARNING: Uniform \"" << uniform << "\" is not a default uniform name." << std:: endl;
	}
}
