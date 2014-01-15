/*
 * main.cpp
 *
 *  Created on: 17.12.2013
 *      Author: Raphimulator
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <Visuals/VirtualObjectFactory.h>
#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"

int main() {
    // render window
    glfwInit();

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glewExperimental= GL_TRUE;
#endif


    GLFWwindow* window = glfwCreateWindow(800, 800, "Compositing", NULL, NULL);
    glfwMakeContextCurrent(window);
    glClearColor(1,0,0,0);

    // get framebuffer size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    //init opengl 3 extension
    glewInit();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;




    GLuint phongShaderHandle = ShaderTools::makeShaderProgram(
            SHADERS_PATH "/Phong/phong.vert",
            SHADERS_PATH "/Phong/phong.frag");
    glEnable(GL_DEPTH);

    GLuint modelHandle = glGetUniformLocation(phongShaderHandle, "uniformModel");
    GLuint viewHandle = glGetUniformLocation(phongShaderHandle, "uniformView");
    GLuint projectionHandle = glGetUniformLocation(phongShaderHandle, "uniformProjection");
    GLuint inverseHandle = glGetUniformLocation(phongShaderHandle, "uniformInverse");


    //der Order muss im System existieren
    	VirtualObjectFactory* voFactory = VirtualObjectFactory::getInstance();
    	VirtualObject* cow = voFactory->createVirtualObject(RESOURCES_PATH "/cow.obj");

    	using namespace glm;

        mat4 modelMatrix = mat4(1.0f);

        mat4 viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 projectionMatrix = perspective(40.0f, 4.0f / 3.0f, 0.1f, 100.f);

        mat4 inverseMatrix = transpose(inverse(modelMatrix * viewMatrix));

        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelMatrix));
        glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(inverseMatrix));

        glUseProgram(phongShaderHandle);

    	 while(!glfwWindowShouldClose(window)) {

    		 std::cout <<"das programm kommt bis zur schleife" <<std::endl;

    	        glfwMakeContextCurrent(window);

    	        unsigned int i = 0;
    	        for (i = 0; i < cow->getGraphicsComponent().size(); ++i) {
        	        glBindVertexArray(cow->getGraphicsComponent()[i]->getMesh()->getVAO());
        	        glDrawArrays(GL_TRIANGLES, 0, cow->getGraphicsComponent()[i]->getMesh()->getNumFaces() );
				}

    	        glfwSwapBuffers(window);
    	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	        glfwPollEvents();
    	 }
    	    glfwDestroyWindow(window);
    	    glfwTerminate();
    	    return 0;
}



