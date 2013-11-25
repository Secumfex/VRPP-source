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

//TODO filling Buffer with queued objects
static void createVertexBuffer(){
    GLfloat vertices[] = {-1.0,-1.0,0.0, 0.0,-1.0,1.0, 1.0,-1.0,0.0, 0.0,1.0,0.0};
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

//TODO filling buffer with indices of queued object-vertices
static void createIndexBuffer(){
    GLuint indices[] = {0, 3, 1,
                        1, 3, 2,
                        2, 3, 0,
                        0, 1, 2 };
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

//adding a shader (attaching to program)
static void addShader(GLuint shaderProgram, const char* pShaderText, GLuint shaderType){
    GLuint shaderObject = glCreateShader(shaderType);

    if (shaderObject == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shaderType);
        exit(0);
    }

    const char* p[1];
    p[0] = pShaderText;
    GLint lengths[1];
    lengths[0] = strlen(pShaderText);

    glShaderSource(shaderObject, 1, p, lengths);   
    glCompileShader(shaderObject);

    //compilation successful? (not in final version)
    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObject, sizeof(InfoLog), NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
    }

    glAttachShader(shaderProgram, shaderObject);
}