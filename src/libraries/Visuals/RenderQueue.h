#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>
#include <map>

#include "VirtualObject.h"

using namespace std;

class RenderQueue {
public: 
	RenderQueue(); //create and reset RQ
	~RenderQueue();
	void addVirtualObject(VirtualObject* vo); //add VO to VO list
	void removeVirtualObject(VirtualObject* vo); //remove VO from list
	VirtualObject* getNextObject(); //iterate list
	bool hasNext(); //is voList empty?
	void resetQueue();	//resetting iterator to list begin
	void extractAndSort(); //extracts GCs from all VOs in VO list and sorts them into the gcStorage map
private:
	list<VirtualObject* >::iterator currentFirstElement;	//Aktuelles vorderstes Objekt
	list<VirtualObject*> voList;
	map<string, list<VirtualObject*> > gcStorage; //GC map sorted by shaders
};

#endif /* RENDERQUEUE_H */
