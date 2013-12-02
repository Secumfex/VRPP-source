#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>

#include "VirtualObject.h"

using namespace std;

class RenderQueue {
public: 
	RenderQueue();
	~RenderQueue();
	void addVirtualObject(VirtualObject* vo);
	void removeVirtualObject(VirtualObject* vo);
	VirtualObject* getNextObject();
	bool hasNext();
private:
	list<VirtualObject*> voList;
};

#endif /* RENDERQUEUE_H */
