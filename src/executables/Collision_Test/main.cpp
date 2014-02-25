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
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

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

glm::mat4 sphere;
glm::mat4 sphereInverse;

//VOs and physic-world
VirtualObject* testPlane;
VirtualObject* test1;
VirtualObject* test2;
VirtualObject* testSphere;

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

static GLfloat vdata[12][3] = {
    {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
    {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
    {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static GLuint tindices[20][3] = {
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

void normalize(GLfloat *a) {
    GLfloat d=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    a[0]/=d; a[1]/=d; a[2]/=d;
}
/*
 * draws triangles for sphere
 */
void drawtri(GLfloat *a, GLfloat *b, GLfloat *c, int div, float r) {
    if (div<=0) {
        glNormal3fv(a); glVertex3f(a[0]*r, a[1]*r, a[2]*r);
        glNormal3fv(b); glVertex3f(b[0]*r, b[1]*r, b[2]*r);
        glNormal3fv(c); glVertex3f(c[0]*r, c[1]*r, c[2]*r);
    } else {
        GLfloat ab[3], ac[3], bc[3];
        for (int i=0;i<3;i++) {
            ab[i]=(a[i]+b[i])/2;
            ac[i]=(a[i]+c[i])/2;
            bc[i]=(b[i]+c[i])/2;
        }
        normalize(ab); normalize(ac); normalize(bc);
        drawtri(a, ab, ac, div-1, r);
        drawtri(b, bc, ab, div-1, r);
        drawtri(c, ac, bc, div-1, r);
        drawtri(ab, bc, ac, div-1, r);  //<--Comment this line and sphere looks really cool!
    }
}
/*
 * draws sphere
 */
void drawsphere(int ndiv, float radius) {
    glBegin(GL_TRIANGLES);
    for (int i=0;i<20;i++)
        drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], ndiv, radius);
    glEnd();
}


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

     { // Sphere

            sphere = scale(translate(mat4(1.0f), vec3(0.3f, 0.5f, -0.5f)), vec3(0.6f, 0.6f, 0.6f));
            sphereInverse = transpose(inverse(viewMatrix * sphere));
            }

    lightPosition = vec4(0, 10, 0, 1);

	//2 VOs
	//VOs per ressourceManager erstellen (also graphicComponent)
    testPlane = new VirtualObject;
	test1 = new VirtualObject;
	test2 = new VirtualObject;
	testSphere = new VirtualObject;

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

	float *fm4 = value_ptr(sphere);
	float radius = 1.2;
	float mass = 1.0;
	float x4 = fm4[0];
	float y4 = fm4[5];
	float z4 = fm4[10];


	float *fm3 = value_ptr(plane);
	float width3 = fm3[0];
	float height3 = fm3[5];
	float depth3 = fm3[10];
	float x3 = fm3[12];
	float y3 = fm3[13];
	float z3 = fm3[14];

	test1->setPhysicsComponent(width1, height1, depth1, x1, y1, z1, 0.3);
	test2->setPhysicsComponent(width2, height2, depth2, x2, 100.0+y2, z1, 1.0);
	testSphere->setPhysicsComponent(radius, x4, 150.0+y4, z4, mass);
	testPlane->setPhysicsComponent(width3, height3, depth3, x3, y3, z3, 0.0);

	cout << "hit1: " << test1->physicsComponent->getHit() << endl;
	cout << "hit2: " << test2->physicsComponent->getHit() << endl;
	cout << "hit3: " << testSphere->physicsComponent->getHit() << endl;

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

		testSphere->physicsComponent->update();
		sphere = testSphere->physicsComponent->getModelMatrix();
		sphereInverse = transpose(inverse(viewMatrix * sphere));

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

        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(sphere));
        glUniformMatrix4fv(inverseHandle, 1, GL_FALSE, value_ptr(sphereInverse));
        drawsphere(5,1);

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
