#include "RenderManager.h"

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

GLuint vbo;
GLuint ibo;

GLuint MVPHandle;
GLFWwindow* window; 

using namespace glm;

//glfw error-callback
void errorCallback(int error, const char* description){
    fputs(description, stderr);
}

//key callback, will be removed when there is I/O functionality
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void libInit(){
    glfwSetErrorCallback(errorCallback);

    //if init returns zero, cancel, if it returns 1 all runs fine, actually that's just glfwInit()
    if(!glfwInit()){
        exit(EXIT_FAILURE);
    };

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

void RenderManager :: renderLoop(){
	std::cout<<"renderLoop()..."<<std::endl; 
}