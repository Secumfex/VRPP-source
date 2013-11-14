
#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"

class VirtualObject{
public:

	//TODO Model Matrix

	PhysicsComponent physicsComponent;
	GraphicsComponent graphicsComponent;

	void render();
};


#endif
