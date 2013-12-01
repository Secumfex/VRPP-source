

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

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"
#include "Tools/Geometry.h"

#include "Visuals/FrameListener.h"

GLuint vbo;
GLuint ibo;

GLuint MVPHandle;
GLuint shaderProgramHandle;

GLFWwindow* window; 

using namespace glm;


//glfw error-callback
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
}

void RenderManager::manageShaderProgram(){

	shaderProgramHandle = ShaderTools::makeShaderProgram(
                                                                 SHADERS_PATH "/RenderManagerApp/RenderManagerApp.vert",
                                                                 SHADERS_PATH "/RenderManagerApp/RenderManagerApp.frag");

	glUseProgram(shaderProgramHandle);
}

void RenderManager::renderLoop(){
    std::cout<<"Render loop reached successfully."<<std::endl;

    MVPHandle = glGetUniformLocation(shaderProgramHandle, "uniformMVP");

    while(!glfwWindowShouldClose(window)){
        notify();
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}


RenderManager::~RenderManager(){ 

}

RenderManager::RenderManager(){
    attach(new FrameListener());
}