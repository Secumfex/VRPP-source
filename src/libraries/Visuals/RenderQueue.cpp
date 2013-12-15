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

void RenderQueue::extractAndSort(VirtualObject* vo){
	string shader = "fuckyeah"; //TESTSTRING, WILL BE REMOVED SOON
	if(gcStorage.find(shader) == gcStorage.end()){
		//no list for that shader exists in the map
	}else{
		//a list exists and we need to insert the gc-vector
	}
}