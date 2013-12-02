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
	void resetQueue();	//resetting iterator to list begin
private:
	list<VirtualObject* >::iterator currentFirstElement;	//Aktuelles vorderstes Objekt
	list<VirtualObject*> voList;
};

#endif /* RENDERQUEUE_H */
