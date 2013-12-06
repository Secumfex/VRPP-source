#include "Resource.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <GLFW/glfw3.h>




//---------------RESOURCE SCOPE--------------------


void Resource :: streamToVRAM(){ }

//---------------TEXTURE SCOPE--------------------

void Material :: streamToVRAM(){

}


//---------------MESH SCOPE--------------------

void Mesh :: streamToVRAM(){
}

void Mesh :: setVAO(GLuint vao){}
GLuint Mesh :: getVAO(){
	mVaoHandle;
}


Mesh::Mesh() { }
Mesh::~Mesh() { }
