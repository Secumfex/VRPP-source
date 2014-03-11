

#include "Visuals/RenderManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Visuals/RenderQueue.h"

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"
//#include "Tools/Geometry.h"

using namespace glm;


void RenderManager::setRenderQueue(RenderQueue* currentRQ){
	mRenderqueue = currentRQ;
}

glm::mat4 RenderManager::getPerspectiveMatrix(){
	return mFrustum->getPerspectiveMatrix();
}

//TODO
/*wir brauchen eine setCurrentGC(GraphicsComponent* gc)
und eine getCurrentGC()
die auf eine globale Pointer-variable im RenderManager zugreifen
sowas wie GraphicsComponent* mCurrentGC
gesetzt wird der shit in der renderLoop, aber das machen wir sp�ter
erstmal wollen wir nur den Access haben

WENN wir das geschafft haben kommt Step2
dann machen wir uns noch eine currentVO globale variable, ebenfalls im RenderManager (auf raphis anfrage)
die getCurrentVO wird dann genauso aussehen wie die getCurrentGC, nur halt mit virtual object
die setCurrentVO wird stattdessen auf die jeweilige map in der RenderQueue zugreifen und kann direkt in der
setCurrentGC aufgerufen werden sobald die GC global gesetzt wurde

 */

void RenderManager::setCurrentGC(GraphicsComponent* gc){
	mCurrentGC = gc;
}

void RenderManager::setCurrentShader(Shader* shader){
	mCurrentShader = shader;
}

void RenderManager::setCurrentFBO(FrameBufferObject* fbo){
	mCurrentFBO = fbo;
}

void RenderManager::setCamera(Camera* camera){
	mCamera = camera;
}

void RenderManager::setPerspectiveMatrix(float fovy, float aspect, float near, float far){
	if(mFrustum==NULL)
		std::cout << "ERROR: Cannot set Perspective Matrix. RenderManager does not know a Frustum, yet." << std:: endl;
	mFrustum->setPerspectiveMatrix(fovy, aspect, near, far);
}

void RenderManager::setDefaultPerspectiveMatrix(){
	//    PerspectiveMatrix = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}

VirtualObject* RenderManager::getCurrentVO(){
	map<GraphicsComponent*, VirtualObject* > gc2voMap = mRenderqueue->getGc2VoMap();
	VirtualObject* myCurrentVO = gc2voMap[mCurrentGC];

	return myCurrentVO;
}

void RenderManager::setCurrentFrustum(Frustum* frustum){
	mFrustum = frustum;
}
void RenderManager::setLightPosition (glm::vec3 pos, int index){
if(mLightPositions.empty())
	createFourLightsources();
if(index < 0 || index > 3)
	return;

}

FrameBufferObject* RenderManager::getCurrentFBO(){
	return mCurrentFBO;
}


GraphicsComponent* RenderManager::getCurrentGC(){
	return mCurrentGC;
}

Shader* RenderManager::getCurrentShader(){
	return mCurrentShader;
}
Camera* RenderManager::getCamera(){
	//TODO: ordentlich Kamera uebergeben
	return mCamera;
}

RenderQueue* RenderManager::getRenderQueue(){
	return mRenderqueue;
}

GLFWwindow* RenderManager::getWindow(){
	return window;
}

Frustum* RenderManager::getCurrentFrustum(){
	return mFrustum;
}

glm::mat4 RenderManager::getLightPerspectiveMatrix(int index){
	glm::vec3 eye = mCamera->getPosition();
	glm::vec3 center = mCamera->getViewDirection() - eye;

	glm::mat4 persp = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(mLightPositions[index], center, vec3(0.0, 1.0, 0.0));

	return  persp * view;
}

//glfw error-callback function
void errorCallback(int error, const char* description){
	fputs(description, stderr);
}

//key callback, will be removed when there is I/O functionality
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){

		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void RenderManager::libInit(){

	std::cout<<"Initializing glew/glfw libraries.."<<std::endl;
	glfwSetErrorCallback(errorCallback);

	if(!glfwInit()){
		exit(EXIT_FAILURE);
	};

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glewExperimental= GL_TRUE;
#endif

	window = glfwCreateWindow(800, 600, "GLFW TUT", NULL, NULL);

	if(!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glewInit();
	glClearColor(0,0,0,0);

	// print out some info about the graphics drivers
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	//set default PerspectiveMatrix
	setDefaultPerspectiveMatrix();

}

void RenderManager::manageShaderProgram(){

	shaderProgramHandle = ShaderTools::makeShaderProgram(
			SHADERS_PATH "/RenderManagerApp/RenderManagerApp.vert",
			SHADERS_PATH "/RenderManagerApp/RenderManagerApp.frag");

	glUseProgram(shaderProgramHandle);
}

void RenderManager::renderLoop(){
	//   std::cout<<"Render loop reached successfully."<<std::endl;

	MVPHandle = glGetUniformLocation(shaderProgramHandle, "uniformMVP");

	if(!glfwWindowShouldClose(window)){ //if window is not about to close
		glfwMakeContextCurrent(window);
		glClear(GL_COLOR_BUFFER_BIT);

		notify("FRAMELISTENER");      //notify all listeners labeled FRAMELISTENER

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	else{
		glfwTerminate();
		notify("WINDOWSHOULDCLOSELISTENER"); //else notify Listeners labled WINDOWSHOULDCLOSELISTENER
	}
}


RenderManager::~RenderManager(){ 

}

RenderManager::RenderManager(){
	mCamera = 0;
	mRenderqueue = 0;   //must be set from outside

	mCurrentGC = 0;
	mCurrentFBO = 0;
	mCurrentShader = 0;

}

void RenderManager::attachListenerOnNewFrame(Listener* listener){
	listener->setName("FRAMELISTENER"); //label this listener as framelistener
	attach(listener);                   //attach listener
}

void RenderManager::attachListenerOnWindowShouldClose(Listener* listener){
	listener->setName("WINDOWSHOULDCLOSELISTENER");
	attach(listener);
}

void RenderManager::createFourLightsources(){
	mLightPositions.push_back(vec3(20, 20, 20));
	mLightPositions.push_back(vec3(-20, 20, 20));
	mLightPositions.push_back(vec3(20, 20, -20));
	mLightPositions.push_back(vec3(-20, 20, -20));
}
