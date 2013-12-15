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
//	cout<<"Getting VO and iterating queue-iterator."<<endl; // <-- REMOVE IN FINAL
	VirtualObject* vo = *currentFirstElement;
	currentFirstElement++;
	return vo;
}

//test if VO list is empty
bool RenderQueue::hasNext(){
	if(currentFirstElement == voList.end()){
//		cout<<"no more queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return false;
	}else{
//		cout<<"queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return true;
	}
}

void RenderQueue::resetQueue(){
	currentFirstElement = voList.begin();
}

/*
Working with all the VOs from voList. Thus, need to iterate the list. While doing so we need to extract GCs from each VO.
After extracting the GC vectors need to be sorted into the map using their tag. Currently no tag exists. in the map there
are several lists each containing vectors of GCs. Each list specifies a certain shader and each vector is extractet from a 
single VO.
*/
void RenderQueue::extractAndSort(){
	string shader = "DEFERRED_SHADING"; 
	VirtualObject* vo;
	vector<GraphicsComponent>* gcVector;
	map<string, vector<GraphicsComponent*> >::iterator i;
	GraphicsComponent gc;

	while(hasNext()){
		vo = getNextObject();
		gcVector = vo->getGraphicsComponent();
		for(gcIterator = gcVector->begin(); gcIterator != gcVector->end(); gcIterator++){
			cout<<"test"<<endl; //TO BE REMOVED
			gcStorage[shader]->push_back(*gcIterator);
		}
	}
	


}