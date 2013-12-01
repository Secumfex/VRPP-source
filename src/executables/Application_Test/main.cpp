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

GLuint programHandle;

GLuint modelHandle;
GLuint viewHandle;
GLuint projectionHandle;
GLuint inverseHandle;

GLuint lightPositionHandle;

//Virtual Object related values
GLuint cubeVertexArrayHandle;

float ange_cube;
float rotationSpeed;

glm::vec4 lightPosition;
        
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::mat4 modelCube_1;
glm::mat4 inverseModel_1;

glm::mat4 modelCube_2; 
glm::mat4 inverseModel_2;

/* fills member variables of RenderManager 
*        the GLFW Window
*        the Shader Program Handles
*/
void initRenderer(){
    // Init GLFW
    glfwInit();
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glewExperimental= GL_TRUE;
#endif
    
    //Create a Window
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

    glEnable(GL_DEPTH_TEST);
    glUseProgram(programHandle);
}

/* inits Physics specific stuff
*        start Physics-Engine
*        gravity, etc.
*/
void initPhysics(){
    rotationSpeed = 1.0f;
}

/* fills RenderQueue of RenderManager 
*        Create Virtual Objects consisting of Vertex Arrays streamed to VRAM (vertices, normals, uvcoordinates)
*        Create ViewMatrix in IOManager::ViewMatrix
*        Init Model-Matrices of Virtual Objects (via PhysicsComponent)
*        
*/
void initScene(){ 
    using namespace glm;
    //////////////////////// Load used Materials to VRAM /////////////////
    {  
        {   //This should be streamed to GPU by Mesh::streamToVRAM()
            glGenVertexArrays(1, &cubeVertexArrayHandle);
            glBindVertexArray(cubeVertexArrayHandle);
        
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
    }

    /////////////////////////// Init View-Matrix of IOManager ///////////////////////////////////
    {
        viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        projectionMatrix = perspective(40.0f, 1.0f, 0.1f, 100.f);
    }

    /////////////////////// Create some Objects and attach them to RenderQueue /////////////////
    {
        //Floor-Object
        {  
            modelCube_1 = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));
            inverseModel_1 = transpose(inverse(viewMatrix * modelCube_1));
        }
        { //Rotating-Cube-Object
            
            ange_cube = 0.0f; //start rotation of the cube
            modelCube_2 = scale(translate(rotate(mat4(1.0f), degrees(ange_cube), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
            inverseModel_2 = transpose(inverse(viewMatrix * modelCube_2));
        }
    }

    lightPosition = vec4(0, 10, 0, 1);        //hardcoded light position
}

/*renders the scene
*        update virtual objects
*        render RenderQueue Objects*/
void renderLoop(){
    using namespace glm;
    while(!glfwWindowShouldClose(window)) {
        ///////////////  Update Objects via Physics Engine//////////////////
        {   ange_cube = fmod((float)(ange_cube + rotationSpeed * glfwGetTime()), pi<float>() * 2.0f);
            glfwSetTime(0.0);
            modelCube_2 = scale(translate(rotate(mat4(1.0f), degrees(ange_cube), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
            inverseModel_2 = transpose(inverse(viewMatrix * modelCube_2));
        }
        /////////////// Begin Rendering             ////////////////////////
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, width, height);
            glUniform3fv(lightPositionHandle, 1, value_ptr(lightPosition));

            glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
            glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
                
             ///////  Render Objects of RenderQueue  /////
            {
                glBindVertexArray(cubeVertexArrayHandle);   //Using Cube-Materials from VRAM
        
                glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_1));
                glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(inverseModel_1));
                glDrawArrays(GL_TRIANGLES, 0, 12*3); //DRAW FLOOR
        
                glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelCube_2));
                glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(inverseModel_2));
                glDrawArrays(GL_TRIANGLES, 0, 12*3);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

//The actual program
int main() {
    //enter VRState
    VRState* vr = new VRState();
    Application* app = Application::getInstance();
    app->setState(vr);
    
    vr->initRenderer();
    initRenderer();

    vr->initPhysics();
    initPhysics();

    vr->initScene();
    initScene();

    RenderManager::getInstance()->renderLoop();
    renderLoop();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
};
