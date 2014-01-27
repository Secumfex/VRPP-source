#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

int main(){
	// Initialize GFLW
	if( !glfwInit() )
	{
	    fprintf( stderr, "Failed to initialize GLFW\n" );
	    return -1;
	}

	glfwWindowHint(GLFW_STEREO, 4); // 4x antialiasing

	if( !glfwCreateWindow(1024,768,"Test",0,0))
	{
	    fprintf( stderr, "Failed to open GLFW window\n" );
	    glfwTerminate();
	    return -1;
	}

	// Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}

}
