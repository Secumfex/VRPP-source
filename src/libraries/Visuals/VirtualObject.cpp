#include <iostream>
#include "VirtualObject.h"

using namespace std;

int lastID = 0;

//constructor
VirtualObject::VirtualObject(){

	modelMatrix;
	updateModelMatrix();
	id = lastID + 1;
	lastID = id;
	graphicsComponent = GraphicsComponent();
	physicsComponent = PhysicsComponent();
}

//draw object
void VirtualObject::render(){

	//TODO

}

//update modelmatrix (via bullet)
void VirtualObject::updateModelMatrix(){

	//TODO

}
