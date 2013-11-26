#include <iostream>
#include "VirtualObject.h"

using namespace std;

int lastID = 0;

//constructor
VirtualObject::VirtualObject(){

	modelMatrix;
	id = lastID + 1;
	lastID = id;
	graphicsComponent = new GraphicsComponent();
	physicsComponent = new PhysicsComponent();
}

VirtualObject::~VirtualObject(){

	delete graphicsComponent;
	delete physicsComponent;
}

//update modelmatrix (via bullet)
//altern. ueber listener pattern
