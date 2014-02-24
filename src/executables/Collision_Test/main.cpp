#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
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

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

// light
glm::vec4 lightPosition;

// Floor and 2 Cubes
GLuint cubeVertexArrayHandle;

glm::mat4 plane;
glm::mat4 planeInverse;

glm::mat4 cube1;
glm::mat4 cube1Inverse;

glm::mat4 cube2;
glm::mat4 cube2Inverse;

//VOs and physic-world
VirtualObject* testPlane;
VirtualObject* test1;
VirtualObject* test2;

PhysicWorld* world;

//unsere Camera verwenden wenn moeglich (also den vom i/o-team)

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
 */ /*
void renderSphere(VirtualObject* vo){

	//unseren renderManager benutzen wenn moeglich (also den vom renter-team)

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
} */

/*
 * init of VOs and its components
 */
void initScene(){

	using namespace glm;

    {
        {   glGenVertexArrays(1, &cubeVertexArrayHandle);
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

    {
            viewMatrix = lookAt(vec3(0.0f, 1.0f, -6.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
            projectionMatrix = perspective(40.0f, 1.0f, 0.1f, 100.f);
        }

    {
            plane = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));
            planeInverse = transpose(inverse(viewMatrix * plane));
      }

    { // Cube1

            cube1 = scale(translate(mat4(1.0f), vec3(0.2f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
            cube1Inverse = transpose(inverse(viewMatrix * cube1));
            }

     { // Cube2

            cube2 = scale(translate(mat4(1.0f), vec3(0.4f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
            cube2Inverse = transpose(inverse(viewMatrix * cube2));
            }

    lightPosition = vec4(0, 10, 0, 1);

	//2 VOs
	//VOs per ressourceManager erstellen (also graphicComponent)
    testPlane = new VirtualObject;
	test1 = new VirtualObject;
	test2 = new VirtualObject;

	//with box rigidBodies

	float *fm1 = value_ptr(cube1);
	float width1 = fm1[0];
	float height1 = fm1[5];
	float depth1 = fm1[10];
	float x1 = fm1[0];
	float y1 = fm1[5];
	float z1 = fm1[10];

	float *fm2 = value_ptr(cube2);
	float width2 = fm2[0];
	float height2 = fm2[5];
	float depth2 = fm2[10];
	float x2 = fm2[0];
	float y2 = fm2[5];
	float z2 = fm2[10];

	float *fm3 = value_ptr(plane);
	float width3 = fm3[0];
	float height3 = fm3[5];
	float depth3 = fm3[10];
	float x3 = fm3[12];
	float y3 = fm3[13];
	float z3 = fm3[14];

	test1->setPhysicsComponent(width1, height1, depth1, x1, y1, z1, 0.3);
	test2->setPhysicsComponent(width2, height2, depth2, x2, 100.0+y2, z1, 1.0);
	testPlane->setPhysicsComponent(width3, height3, depth3, x3, y3, z3, 0.0);

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

	using namespace glm;

	while(!glfwWindowShouldClose(window)){

		//TODO VOs kollidieren lassen
		//eig egal, fallen ja so auch einfach nach unten

		//simulation in physics world laufen lassen
		//TODO stepSimulation per listener (PhysicWorldSimulationListener)
		PhysicWorld::getInstance()->dynamicsWorld->stepSimulation(1/120.f,10);

		test1->physicsComponent->update();
		cube1 = test1->physicsComponent->getModelMatrix();
		cube1Inverse = transpose(inverse(viewMatrix * cube1));

		test2->physicsComponent->update();
		cube2 = test2->physicsComponent->getModelMatrix();
		cube2Inverse = transpose(inverse(viewMatrix * cube2));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));

        glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));

        ////////////////////////////////////////////////////////////////////////////

        glBindVertexArray(cubeVertexArrayHandle);   //Using Cube-Materials from VRAM

        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(plane));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(planeInverse));
        glDrawArrays(GL_TRIANGLES, 0, 12*3); //DRAW FLOOR

        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(cube1));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(cube1Inverse));
        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(cube2));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(cube2Inverse));
        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        ///////////////////////////////////////////////////////////////////////////

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
