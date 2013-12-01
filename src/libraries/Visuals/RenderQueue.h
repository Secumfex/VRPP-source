#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>

#include "VirtualObject.h"
#include "Visuals/RenderManager.h"

using namespace std;

class RenderQueue {
// List of VirtualObjects possibly via HashMap
private:
	list<VirtualObject*> voList;
};

#endif /* RENDERQUEUE_H */
