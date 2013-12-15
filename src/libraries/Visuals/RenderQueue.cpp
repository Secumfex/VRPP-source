#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue(){
resetQueue();
}

RenderQueue::~RenderQueue(){
	
}

void RenderQueue::addVirtualObject(VirtualObject* vo){
	cout<<"Adding VO."<<endl; // <-- REMOVE IN FINAL
	voList.push_back(vo);
}

void RenderQueue::removeVirtualObject(VirtualObject* vo){
	cout<<"Removing VO."<<endl; // <-- REMOVE IN FINAL
	voList.remove(vo);
}

//extract the first VO from the list and remove it after extraction before returning the pointer
VirtualObject* RenderQueue::getNextObject(){
	cout<<"Getting VO and iterating queue-iterator."<<endl; // <-- REMOVE IN FINAL
	VirtualObject* vo = *currentFirstElement;
	currentFirstElement++;
	return vo;
}

//test if VO list is empty
bool RenderQueue::hasNext(){
	if(currentFirstElement == voList.end()){
		cout<<"no more queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return false;
	}else{
		cout<<"queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return true;
	}
}

void RenderQueue::resetQueue(){
	currentFirstElement = voList.begin();
}

//extract VOs from voList, extract gc-vectors from the VOs, extract the gcs from the vectors and throw them into a list in a map
void RenderQueue::sortByShaders(){
	resetQueue();
	string shader = "DEFERRED_SHADING"; 
	VirtualObject* vo;
	vector<GraphicsComponent>* gcVector = new vector<GraphicsComponent>;


	cout<<"Entering extractAndSort"<<endl;

	while(hasNext()){
		vo = getNextObject();
		gcVector = vo->getGraphicsComponent();
		for(gcIterator = gcVector->begin(); gcIterator != gcVector->end(); gcIterator++){
			cout<<"Adding GC to the map."<<endl; //TO BE REMOVED
			gcStorage[shader]->push_back(*gcIterator); //<---!!! Hier liegt das Problem
		}
	}
	


}