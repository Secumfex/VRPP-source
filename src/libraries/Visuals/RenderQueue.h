#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>

#include "VirtualObject.h"

using namespace std;

class RenderQueue {
public: 
	RenderQueue();
	~RenderQueue();
private:
	list<VirtualObject*> voList;
};

#endif /* RENDERQUEUE_H */
