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

#include "Visuals/Shader.h"

#include "Visuals/VirtualObjectFactory.h"



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
    glClearColor(1,1,1,0);
    
    // get framebuffer size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    //init opengl 3 extension
    glewInit();
    
    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    
    
    //load, compile and link simple texture rendering program for a screen filling plane
    
    Shader *simpeTexShader = new Shader(SHADERS_PATH "/GBuffer/screenFill.vert",
            							SHADERS_PATH "/GBuffer/simpleTexture.frag");
    
    Shader *finalCompShader = new Shader(	SHADERS_PATH "/GBuffer/screenFill.vert",
    										SHADERS_PATH "/GBuffer/finalCompositing.frag");
    
    Shader *gbufferShader = new Shader(		SHADERS_PATH "/GBuffer/GBuffer.vert",
											SHADERS_PATH "/GBuffer/GBuffer.frag");


    
    cout << "GBufferHandle " << gbufferShader->getProgramHandle() << endl;
    

    //--------------------------------------------//
    //        Create a Vertex Array Object        //
    //         to render a triangle that          //
    //           fills the whole screen           //
    //--------------------------------------------//
    
    GLuint screenFillVertexArrayHandle;
    {
        glGenVertexArrays(1, &screenFillVertexArrayHandle);
        glBindVertexArray(screenFillVertexArrayHandle);
        
        GLuint vertexBufferHandle;
        glGenBuffers(1, &vertexBufferHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
        
        //        3 :.
        //          :   .
        //          :      .
        //        1 :_________.
        //          |         |  .
        //          |    +    |     .
        //          |_________|........
        //       -1/-1        1        3
        
        GLfloat vertices[] = {-1, -1,   3, -1,   -1,  3};
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
    
    
    
    //--------------------------------------------//
    //        Create a Vertex Array Object        //
    //         containing several buffers         //
    //             to render a cube               //
    //--------------------------------------------//
    
VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();
VirtualObject *cube = voFactory->createVirtualObject(RESOURCES_PATH "/cow.obj");
    
    
    //--------------------------------------------//
    //         Create a Framebuffer Object        //
    //--------------------------------------------//
    
    GLuint framebufferHandle;
    GLuint positionTextureHandle;
    GLuint normalTextureHandle;
    GLuint colorTextureHandle;
    GLuint depthbufferHandle;
    {
        glGenFramebuffers(1, &framebufferHandle);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
        
        //the geometry buffer
        glGenTextures(1, &positionTextureHandle);
        glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, (height/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        //the normal buffer
        glGenTextures(1, &normalTextureHandle);
        glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, (height/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        //the color buffer
        glGenTextures(1, &colorTextureHandle);
        glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, (height/4.0)*3, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        //the depth buffer
        glGenRenderbuffers(1, &depthbufferHandle);
        glBindRenderbuffer(GL_RENDERBUFFER, depthbufferHandle);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, (height/4.0)*3); //800x600
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbufferHandle);
        
        //set color attachments
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTextureHandle, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTextureHandle, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTextureHandle, 0);
        
        //set the list of draw buffers.
        GLenum drawBufferHandles[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, drawBufferHandles);
    }
    
    //rotation of the cube
    float angle = 0.0f;
    float rotationSpeed = 1.0f;
	int blurStrength = 4;
    
    while(!glfwWindowShouldClose(window)) {
        
        glfwMakeContextCurrent(window);
        
        using namespace glm;
        
        //rotation angle
        angle = fmod((float)(angle+rotationSpeed*glfwGetTime()), (float)(pi<float>()*2.0f));
        glfwSetTime(0.0);
        
        //scale a cube into a flat plane
        mat4 modelCube_1 = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));
        
        //nice rotation of a small cube
        mat4 modelCube_2 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
        
        //setting up the camera parameters
        mat4 viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 projectionMatrix = perspective(40.0f, 4.0f / 3.0f, 0.1f, 100.f);
        
        //--------------------------------------------//
        //        Render the scene into the FBO       //
        //--------------------------------------------//
        
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        glEnable(GL_DEPTH_TEST);
        glBindVertexArray(cube->getGraphicsComponent()[0]->getMesh()->getVAO());
        glBindTexture(GL_TEXTURE_2D, cube->getGraphicsComponent()[0]->getMaterial()->getDiffuseMap()->getTextureHandle());
        
        glUseProgram(gbufferShader->getProgramHandle());
        
        glViewport(0, 0, width, (height/4)*3);
        
        

        gbufferShader->uploadUniform(viewMatrix,"uniformView");
        gbufferShader->uploadUniform(projectionMatrix,"uniformProjection");

        gbufferShader->uploadUniform(modelCube_1,"uniformModel");
        glDrawElements(GL_TRIANGLES, cube->getGraphicsComponent()[0]->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
        
        
        gbufferShader->uploadUniform(modelCube_2,"uniformModel");
        glDrawElements(GL_TRIANGLES, cube->getGraphicsComponent()[0]->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
        
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        
        //--------------------------------------------//
        //       Take the textures from the FBO       //
        //      to compose them on an image plane     //
        //--------------------------------------------//
        
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(screenFillVertexArrayHandle);
        
        glUseProgram(finalCompShader->getProgramHandle());
        

	    finalCompShader->uploadUniform(blurStrength,"blurStrength");
        glViewport(0, 0, width, (height/4)*3);
        
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
	    finalCompShader->uploadUniform(0,"positionMap");
        
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
	    finalCompShader->uploadUniform(1,"normalMap");
        
        glActiveTexture(GL_TEXTURE2);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
	    finalCompShader->uploadUniform(2,"colorMap");
        
        glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO MAIN FRAME
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glActiveTexture(GL_TEXTURE0);
        
        //--------------------------------------------//
        //       Render small views at the top to     //
        //      show all the components of the FBO    //
        //--------------------------------------------//
        glDisable(GL_DEPTH_TEST);
        
        glBindVertexArray(screenFillVertexArrayHandle);
        glUseProgram(simpeTexShader->getProgramHandle());
        
        glViewport(0, (height/4)*3, width/3, height/4);
        glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-LEFT VIEWPORT
        
        glViewport(width/3, (height/4)*3, width/3, height/4);
        glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-CENTER VIEWPORT
        
        glViewport((width/3)*2, (height/4)*3, width/3, height/4);
        glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-RIGHT VIEWPORT
        
        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    
};
