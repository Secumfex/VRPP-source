#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"
#include "Tools/Geometry.h"

#include "btBulletDynamicsCommon.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include "Visuals/VirtualObject.h"

using namespace std;

GLFWwindow* window;
int width, height;

GLuint programHandle;

GLuint modelHandle;
GLuint viewHandle;
GLuint projectionHandle;
GLuint inverseHandle;

GLuint lightPositionHandle;

VirtualObject* test1;
VirtualObject* test2;

PhysicWorld* world;

void initWindow(){

	glfwInit();

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glewExperimental= GL_TRUE;
#endif

    window = glfwCreateWindow(800, 800, "Collision-Test", NULL, NULL);
    glfwMakeContextCurrent(window);
    glClearColor(1,1,1,0);

    glfwGetFramebufferSize(window, &width, &height);

    glewInit();

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

void initPhysics(){

	world = new PhysicWorld;
	cout << "world created" << endl;
}

void initScene(){

	test1 = new VirtualObject();
	test2 = new VirtualObject();

	test1->setPhysicsComponent(20.0,2.0,2.0,2.0,2.0);
	test2->setPhysicsComponent(30.0,1.0,1.0,1.0,1.0);

	cout << "hit1: " << test1->physicsComponent->getHit() << endl;
	cout << "hit2: " << test2->physicsComponent->getHit() << endl;

	test1->physicsComponent->setHit(true);
	cout << "hit1: " << test1->physicsComponent->getHit() << endl;
}

void loop(){

	while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);

        glfwSwapBuffers(window);
        glfwPollEvents();
	}
}

int main() {

	initWindow();

	initPhysics();

	initScene();

	loop();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
};
