#include <iostream>
#include <string.h>

#include "Visuals/RenderManager.h"
#include "Patterns/Listener.h"

//Test if the RenderManager is being accessed properly
int main() {

	//Testing Render Queue
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VirtualObject* vo1 = new VirtualObject();
	VirtualObject* vo2 = new VirtualObject();
	VirtualObject* vo3 = new VirtualObject();
	VirtualObject* vo4 = new VirtualObject();
	VirtualObject* vo5 = new VirtualObject();

	RenderQueue* rq = new RenderQueue();

	rq->addVirtualObject(vo1);
	rq->addVirtualObject(vo2);
	rq->addVirtualObject(vo3);
	rq->addVirtualObject(vo4);
	rq->addVirtualObject(vo5);

	rq->removeVirtualObject(vo3);

	vo3 = rq->getNextObject();
	vo3 = rq->getNextObject();
	vo3 = rq->getNextObject();
	bool hasNext = rq->hasNext();
	vo3 = rq->getNextObject();
	hasNext = rq->hasNext();

	//RenderManager Pointer via Singleton
	RenderManager* rm = RenderManager::getInstance();

	rm->libInit();
	rm->manageShaderProgram();
	rm->renderLoop();

	return 0;
};
