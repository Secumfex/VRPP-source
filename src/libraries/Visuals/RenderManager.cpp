

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

GLuint vbo;
GLuint ibo;

GLuint MVPHandle;
GLuint shaderProgramHandle;

GLFWwindow* window; 

using namespace glm;

//RenderManager::RenderManager(){
//}

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

//void RenderManager :: renderLoop(){
	//std::cout<<"renderLoop()..."<<std::endl; 
//}

//TODO filling Buffer with queued objects
static void createVertexBuffer(){
    GLfloat vertices[] = {-1.0,-0.6,0.0, 1.0,-0.6,0.0, 0.0,0.3,0.0};
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

//TODO filling buffer with indices of queued object-vertices
static void createIndexBuffer(){
    GLuint indices[] = {0, 1, 2};
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

static void manageShaderProgram(){

	shaderProgramHandle = ShaderTools::makeShaderProgram(
                                                                 SHADERS_PATH "/RenderManagerApp/RenderManagerApp.vert",
                                                                 SHADERS_PATH "/RenderManagerApp/RenderManagerApp.frag");

	glUseProgram(shaderProgramHandle);
}

static void loop(){

	std::cout<<"Render loop reached successfully."<<std::endl;

    MVPHandle = glGetUniformLocation(shaderProgramHandle, "uniformMVP");

    while(!glfwWindowShouldClose(window)){

        glfwMakeContextCurrent(window);

        glClear(GL_COLOR_BUFFER_BIT);

        static float scaleFloat = 0.0f;
        scaleFloat += 0.001;

        mat4 modelMatrix = rotate(scale(mat4(1.0f), vec3(2.0f+sinf(scaleFloat), 2.0f+sinf(scaleFloat), 0.0f)), 
        	30*scaleFloat, vec3(0.0f, 0.0f, 1.0f));
        mat4 viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 projectionMatrix = perspective(40.0f, 16.0f / 9.0f, 0.1f, 100.f);

        mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

        GLfloat transformation[] = {
            1.2+sin(scaleFloat), 0.0, 0.0, 0.0,
            0.0, 1.2+sin(scaleFloat), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };

        glUniformMatrix4fv(MVPHandle, 1, GL_TRUE, value_ptr(MVPMatrix));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void RenderManager::renderLoop() { 
	std::cout<<"renderLoop()..."<<std::endl;   

    libInit();

    createVertexBuffer();

    createIndexBuffer();

    manageShaderProgram();

    loop();

    glfwTerminate();

};