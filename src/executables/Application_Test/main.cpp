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

#include "Application/Application.h"
#include "Visuals/RenderManager.h"

//global handles should be known by RenderManager 
GLFWwindow* window;
int width, height;

//related to shader program creation
GLuint programHandle;

//related to GBuffer uniform Variables creation
GLuint modelHandle;
GLuint viewHandle;
GLuint projectionHandle;
GLuint inverseHandle;

GLuint lightPositionHandle;

//related to VertexArrayObject Creation
GLuint cubeVertexArrayHandle;
GLuint textureHandle;

void initRenderer(){
    // render window
    glfwInit();
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glewExperimental= GL_TRUE;
#endif
    
    window = glfwCreateWindow(800, 800, "VR Project", NULL, NULL);
    glfwMakeContextCurrent(window);
    glClearColor(1,1,1,0);
    
    // get framebuffer size
    
    glfwGetFramebufferSize(window, &width, &height);
    
    //init opengl 3 extension
    glewInit();
    
    //load, compile and link phong shader program
    programHandle = ShaderTools::makeShaderProgram(
                                                                       SHADERS_PATH "/Phong/phong.vert",
                                                                       SHADERS_PATH "/Phong/phong.frag");    
    
    modelHandle = glGetUniformLocation(programHandle, "uniformModel");
    viewHandle = glGetUniformLocation(programHandle, "uniformView");
    projectionHandle = glGetUniformLocation(programHandle, "uniformProjection");
    inverseHandle = glGetUniformLocation(programHandle, "uniformInverse");
    lightPositionHandle = glGetUniformLocation(programHandle, "uniformInverse");
   
    //--------------------------------------------//
    //        Create a Vertex Array Object        //
    //         containing several buffers         //
    //             to render a cube               //
    //--------------------------------------------//
    
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
    
    //load a fancy texture
    textureHandle = TextureTools::loadTexture(RESOURCES_PATH "/cubeTexture.jpg");
    
}

void renderLoop(){
    //rotation of the cube
    float angle = 0.0f;
    float rotationSpeed = 1.0f;



    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)) {
        
        using namespace glm;

        //hardcoded light position
        vec4 lightPosition = vec4(0, 10, 0, 1);
        

        //setting up the camera parameters
        mat4 viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        mat4 projectionMatrix = perspective(40.0f, 1.0f, 0.1f, 100.f);

        //rotation angle
        angle = fmod((float)(angle + rotationSpeed * glfwGetTime()), pi<float>() * 2.0f);
        glfwSetTime(0.0);
        
        //scale a cube into a flat plane
        mat4 modelCube_1 = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));
        //compute transponsed inverse model matrix
        mat4 inverseModel_1 = transpose(inverse(viewMatrix * modelCube_1));
            
        
        //nice rotation of a small cube
        mat4 modelCube_2 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
        //compute transponsed inverse model matrix
        mat4 inverseModel_2 = transpose(inverse(viewMatrix * modelCube_2));
        
        //--------------------------------------------//
        //        Render the Scene                    //
        //--------------------------------------------//
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
 
        glBindVertexArray(cubeVertexArrayHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        
        glUseProgram(programHandle);
        
        glViewport(0, 0, width, height);
        
        glUniform3fv(lightPositionHandle, 1, value_ptr(lightPosition));

        glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        
        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_1));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(inverseModel_1));
        glDrawArrays(GL_TRIANGLES, 0, 12*3); //DRAW FLOOR
        
        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_2));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(inverseModel_2));
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        
        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

//The actual program
int main() {

    //enter VRState
    VRState* vr = new VRState();
    Application::getInstance()->setState(vr);
    
    //init window and shader handles
    vr->initRenderer();
    initRenderer(); //this should be done by VRState

    //init Virtual Objects for the scene
    vr->initScene();

    //init Physics engine
    vr->initPhysics();

    //enter RenderLoop;
    RenderManager::getInstance()->renderLoop();
    renderLoop();   //this should be done by RenderManager
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    
};
