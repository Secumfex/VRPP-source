#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>

#include "GraphicsComponent.h"

using namespace std;

class RenderQueue {
public: 
	RenderQueue();
	~RenderQueue();
	void addGC(GraphicsComponent* gc);
	void removeGC(GraphicsComponent* gc);
	GraphicsComponent* getNextGC();
	bool hasNext();
	void resetQueue();	//resetting iterator to list begin
private:
	list<GraphicsComponent* >::iterator currentFirstElement;	//Aktuelles vorderstes Objekt
	list<GraphicsComponent*> voList;
};

#endif /* RENDERQUEUE_H */
