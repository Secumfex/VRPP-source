
#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <vector>

class VirtualObject{
public:

	//TODO Model Matrix

	PhysicsComponent physicsComponent;
	vector<GraphicsComponent> graphicsComponent;

	void render();
};


#endif
