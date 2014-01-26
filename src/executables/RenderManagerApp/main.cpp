#include <iostream>
#include <string.h>

#include "Application/Application.h"
#include "Application/ApplicationStates.h"
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

	rq->sortByShaders();

	vo3 = rq->getNextObject();
	vo3 = rq->getNextObject();
	vo3 = rq->getNextObject();
	bool hasNext = rq->hasNext();
	vo3 = rq->getNextObject();
	hasNext = rq->hasNext();

	rq->resetQueue();		//reset queue-iterator to first element
	while (rq->hasNext()){
		vo3 = rq->getNextObject();
	}

	//run Application (and thus: init Rendermanager and enter renderloop)
	Application* myApp = Application::getInstance();
	myApp->addState(new VRState());
	myApp->run();

	return 0;
};
