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
	void sortByShaders(); //extracts GCs from all VOs in VO list and sorts them into the gcStorage map
private:
	list<VirtualObject* >::iterator currentFirstElement; ///< VO pointer used with voList
//	vector<GraphicsComponent>::iterator gcIterator; ///< iterator for gc-vectors
	list<VirtualObject*> voList; ///< list of VOs
	map<string, vector<GraphicsComponent* > > gcStorage; ///< GC map sorted by shaders
	map<VirtualObject*, vector<GraphicsComponent* > > gc2voMap; ///< each GC is assigned to some VO
	map<GraphicsComponent*, VirtualObject*> vo2gcMap; ///< each VO is assigned to some GC
};

#endif /* RENDERQUEUE_H */
