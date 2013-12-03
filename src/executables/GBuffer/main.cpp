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
#include "Visuals/Resource.h"

Mesh cube;
vector<glm::vec3> vertexData;
static void Load3DModel(){
    cube.getResource(RESOURCES_PATH "/cude.obj");//load 3D model in obj formate
    vertexData=cube.returnMesh();//return the vertex data of mesh
    
}

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
    GLuint simpleTextureProgramHandle = ShaderTools::makeShaderProgram(
                                                                       SHADERS_PATH "/GBuffer/screenFill.vert",
                                                                       SHADERS_PATH "/GBuffer/simpleTexture.frag");
    
    
    
    //load, compile and link final compositing program for a screen filling plane
    GLuint finalCompositingProgramHandle = ShaderTools::makeShaderProgram(
                                                                          SHADERS_PATH "/GBuffer/screenFill.vert",
                                                                          SHADERS_PATH "/GBuffer/finalCompositing.frag");
    
    GLint positionMapHandle = glGetUniformLocation(finalCompositingProgramHandle, "positionMap");
    GLint colorMapHandle = glGetUniformLocation(finalCompositingProgramHandle, "colorMap");
    GLint normalMapHandle = glGetUniformLocation(finalCompositingProgramHandle, "normalMap");
    GLint blurStrengthHandle = glGetUniformLocation(finalCompositingProgramHandle, "blurStrength");
    
    
    
    //load, compile and link GBuffer renderer
    GLuint gBufferProgramHandle = ShaderTools::makeShaderProgram(
                                                                 SHADERS_PATH "/GBuffer/GBuffer.vert",
                                                                 SHADERS_PATH "/GBuffer/GBuffer.frag");
    
    GLuint modelHandle = glGetUniformLocation(gBufferProgramHandle, "uniformModel");
    GLuint viewHandle = glGetUniformLocation(gBufferProgramHandle, "uniformView");
    GLuint projectionHandle = glGetUniformLocation(gBufferProgramHandle, "uniformProjection");
    
    
    
    //------------------------------------------------------
    Load3DModel();
    //------------------------------------------------------
    
    
    
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
    
    GLuint cubeVertexArrayHandle;
    {
        glGenVertexArrays(1, &cubeVertexArrayHandle);
        glBindVertexArray(cubeVertexArrayHandle);
        
        //we generate multiple buffers at a time
        GLuint vertexBufferHandles[3];
        glGenBuffers(3, vertexBufferHandles);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::positions), CubeGeometry::positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::uvCoordinates), CubeGeometry::uvCoordinates, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::normals), CubeGeometry::normals, GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    
    
    
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
    
    
    //-------------------------------------------------

    //----------------------------------------------------
    
    //load a fancy texture
    GLuint textureHandle = TextureTools::loadTexture(RESOURCES_PATH "/cubeTexture.jpg");
    
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
        glBindVertexArray(cubeVertexArrayHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        
        glUseProgram(gBufferProgramHandle);
        
        glViewport(0, 0, width, (height/4)*3);
        
        glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        
        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_1));
        glDrawArrays(GL_TRIANGLES, 0, 12*3); //DRAW FLOOR INTO FBO
        
        
        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_2));
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        
        //--------------------------------------------//
        //       Take the textures from the FBO       //
        //      to compose them on an image plane     //
        //--------------------------------------------//
        
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(screenFillVertexArrayHandle);
        
        glUseProgram(finalCompositingProgramHandle);
        
		glUniform1i(blurStrengthHandle, blurStrength);
        glViewport(0, 0, width, (height/4)*3);
        
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
        glUniform1i(positionMapHandle, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
        glUniform1i(normalMapHandle, 1);
        
        glActiveTexture(GL_TEXTURE2);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
        glUniform1i(colorMapHandle, 2);
        
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
        glUseProgram(simpleTextureProgramHandle);
        
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
