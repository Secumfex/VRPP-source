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

//global handles
GLFWwindow* window;
int width, height;

GLuint programHandle;

GLuint modelHandle;
GLuint viewHandle;
GLuint projectionHandle;
GLuint inverseHandle;

GLuint lightPositionHandle;

//VOs and physic-world
VirtualObject* test1;
VirtualObject* test2;

PhysicWorld* world;

//GLUquadricObj* quad;

/*
 * init of glfw window and handles
 */
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

/*
 * init of physic-world
 */
void initPhysics(){

	world = new PhysicWorld;
	cout << "world created" << endl;
}

/*
 * renders a sphere
 */
void renderSphere(VirtualObject* vo){

	btRigidBody* sphere=vo->physicsComponent->getRigidBody();

	//hit test
	if(!vo->physicsComponent->getHit()){

		glColor3f(1,0,0);
	}
	else {

		glColor3f(0,1,0);
	}

	//aktuelle modelMatrix holen. spaeter anders, da glm::mat4 und nicht float[]
	float r=((btSphereShape*)sphere->getCollisionShape())->getRadius();
	btTransform t;
	sphere->getMotionState()->getWorldTransform(t);
	float mat[16];
	t.getOpenGLMatrix(mat);

	//TODO sphere zeichnen, mit radius
	glPushMatrix();
		glMultMatrixf(mat);
		//gluSphere(quad,r,20,20);		//geht nicht, da ja kein glu/glut mehr
	glPopMatrix();
}

/*
 * init of VOs and its components
 */
void initScene(){

	//2 VOs
	test1 = new VirtualObject();
	test2 = new VirtualObject();

	//with sphere rigidBodies
	test1->setPhysicsComponent(20.0,2.0,2.0,2.0,2.0);
	test2->setPhysicsComponent(30.0,1.0,1.0,1.0,1.0);

	cout << "hit1: " << test1->physicsComponent->getHit() << endl;
	cout << "hit2: " << test2->physicsComponent->getHit() << endl;

	//setter test
	test1->physicsComponent->setHit(true);
	cout << "hit1: " << test1->physicsComponent->getHit() << endl;

	//how much collisionObjects are in the physics-world
	int objNum = PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects();
	cout << objNum << endl;
}

/*
 * render the scene
 */
void loop(){

	while(!glfwWindowShouldClose(window)){

		//TODO VOs kollidieren lassen

		//simulation in physics world laufen lassen
		PhysicWorld::getInstance()->dynamicsWorld->stepSimulation(1/120.f,10);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);

        //render the 2 VOs
        renderSphere(test1);
        renderSphere(test2);

        glfwSwapBuffers(window);
        glfwPollEvents();
	}
}

/*
 * main
 */
int main() {

	initWindow();

	initPhysics();

	initScene();

	loop();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
};
