

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
#include "Tools/Geometry.h"

using namespace glm;

GLuint vbo;
GLuint MVPHandle;
GLuint shaderProgramHandle;

mat4 projectionMatrix;

GLFWwindow* window; 

RenderQueue* rq;
GraphicsComponent* currentGC;
VirtualObject* currentVO;

void RenderManager::setRenderQueue(RenderQueue* currentRQ){
    rq = currentRQ;
}

mat4 RenderManager::getProjectionMatrix(){
    return projectionMatrix;
}


//TODO
/*wir brauchen eine setCurrentGC(GraphicsComponent* gc)
und eine getCurrentGC()
die auf eine globale Pointer-variable im RenderManager zugreifen
sowas wie GraphicsComponent* currentGC
gesetzt wird der shit in der renderLoop, aber das machen wir später
erstmal wollen wir nur den Access haben

WENN wir das geschafft haben kommt Step2
dann machen wir uns noch eine currentVO globale variable, ebenfalls im RenderManager (auf raphis anfrage)
die getCurrentVO wird dann genauso aussehen wie die getCurrentGC, nur halt mit virtual object
die setCurrentVO wird stattdessen auf die jeweilige map in der RenderQueue zugreifen und kann direkt in der
setCurrentGC aufgerufen werden sobald die GC global gesetzt wurde

*/


VirtualObject* getCurrentVO(){
	return currentVO;
}

void setCurrentVO(){
	map<GraphicsComponent*, VirtualObject* > gc2voMap = rq->getGc2VoMap();
    currentVO = gc2voMap[currentGC];
}

GraphicsComponent* getCurrentGC(){
	return currentGC;
}

void setCurrentGC(GraphicsComponent* gc){
	currentGC = gc;
    setCurrentVO();
}




void RenderManager::setProjectionMatrix(mat4 _projectionMatrix){
    projectionMatrix = _projectionMatrix;
}

void RenderManager::setDefaultProjectionMatrix(){
    projectionMatrix = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
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
    glfwSetKeyCallback(window, keyCallback);

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

    //set default projectionMatrix
    setDefaultProjectionMatrix();

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

        notify("FRAMELISTENER");      //notify all listeners labeled FRAMELISTENER

        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);
        
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
}

void RenderManager::attachListenerOnNewFrame(Listener* listener){
    listener->setName("FRAMELISTENER"); //label this listener as framelistener
    attach(listener);                   //attach listener
}

void RenderManager::attachListenerOnWindowShouldClose(Listener* listener){
    listener->setName("WINDOWSHOULDCLOSELISTENER"); 
    attach(listener);                   
}
