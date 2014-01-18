#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Tools/ShaderTools.h"
#include "Visuals/VirtualObjectFactory.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>


bool shutdown = false;
int closefunc() {
    shutdown = true;
    return 0;
}
    //====================== NEW ======================//
    //  we now get error messages in the console if    //
    //  an error occures during shader compilation.    //
    //=================================================//
void checkShader(GLuint shaderHandle) {
    GLint status;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shaderHandle, infoLogLength, NULL, infoLog);

        std::cout << "ERROR: Unable to compile shader" << std::endl << infoLog << std::endl;
        delete[] infoLog;
    } else {
        std::cout << "SUCCESS: Shader compiled" << std::endl;
    }
}

int main() {
    //render window
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 500, "Resource_Test", NULL, NULL);
    glfwMakeContextCurrent(window);


    //init opengl 3 extensions
    glewInit();
    glClearColor(0, 0, 0, 1);


    //link shader programs
    GLuint programHandle = ShaderTools::makeShaderProgram(
            SHADERS_PATH "/Phong_Test/phong.vert",
            SHADERS_PATH "/Phong_Test/phong.frag");


    //get uniform location from program
    GLuint uniformModelHandle = glGetUniformLocation(programHandle, "uniformModel");
    GLuint uniformViewHandle = glGetUniformLocation(programHandle, "uniformView");
    GLuint uniformNormalHandle = glGetUniformLocation(programHandle, "uniformInverse");
    GLuint uniformProjectionHandle = glGetUniformLocation(programHandle, "uniformProjection");


    //====================== NEW ======================//
    //        we generate two buffers at a time        //
    //=================================================//
    GLuint vertexBufferHandles[2];
    glGenBuffers(3, vertexBufferHandles);


    //KUUUUUUUUUUUUHHHH
    VirtualObjectFactory *voFac = new VirtualObjectFactory();

    VirtualObject *cube = voFac->createVirtualObject(RESOURCES_PATH "/cube.obj");

    VirtualObject *cow = voFac->createVirtualObject(RESOURCES_PATH "/cow.obj");

    cout << cow->getGraphicsComponent()[0]->getMaterial()->getDiffuseMap()->getTexName() << endl;
    cout << cube->getGraphicsComponent()[0]->getMaterial()->getDiffuseMap()->getTexName() << endl;
    cout << cow->getGraphicsComponent()[0]->getMaterial()->getDiffuseMap()->getTextureHandle() << endl;
    cout << cube->getGraphicsComponent()[0]->getMaterial()->getDiffuseMap()->getTextureHandle() << endl;

        cout << cow->getGraphicsComponent()[0]->getMesh()->getNumVertices() << endl;
        cout << cube->getGraphicsComponent()[0]->getMesh()->getNumVertices() << endl;

        cout << "VAO " <<cow->getGraphicsComponent()[0]->getMesh()->getVAO() << endl;
        cout << "VAO " <<cube->getGraphicsComponent()[0]->getMesh()->getVAO() << endl;

        cout << "Indices " <<cow->getGraphicsComponent()[0]->getMesh()->getNumIndices() << endl;
        cout << "Indices " <<cube->getGraphicsComponent()[0]->getMesh()->getNumIndices() << endl;

    float angle = 0.0;


    while(!shutdown) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //use the linked shaders from now on
        glUseProgram(programHandle);


            //====================== NEW ======================//
            //      we now use glm to do the matrix stuff      //
            //=================================================//
            using namespace glm;

            //rotation angle
            angle = fmod(angle + 0.0001f, pi<float>() * 2.0f);

            //compute model matrix
            mat4 modelMatrix = rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(uniformModelHandle, 1, GL_FALSE, value_ptr(modelMatrix));

            //compute view matrix
            mat4 viewMatrix = lookAt(vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(uniformViewHandle, 1, GL_FALSE, value_ptr(viewMatrix));

            //compute projection matrix
            mat4 projectionMatrix = perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.f);
            glUniformMatrix4fv(uniformProjectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));

            //compute normal matrix
            mat4 normalMatrix = transpose(inverse(viewMatrix * modelMatrix));
            glUniformMatrix4fv(uniformNormalHandle, 1, GL_FALSE, value_ptr(normalMatrix));


        glBindVertexArray(cow->getGraphicsComponent()[0]->getMesh()->getVAO());
        glDrawElements(GL_TRIANGLES, cow->getGraphicsComponent()[0]->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);

//        glBindVertexArray(cube->getGraphicsComponent()[0]->getMesh()->getVAO());
//        glDrawArrays(GL_TRIANGLES, 0, cube->getGraphicsComponent()[0]->getMesh()->getNumVertices());
        cout<< "hitler ist scheisse" << endl;
        //show what's been drawn
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
};

