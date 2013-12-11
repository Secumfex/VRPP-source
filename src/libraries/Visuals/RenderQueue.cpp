#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue(){
resetQueue();
}

RenderQueue::~RenderQueue(){
	
}

void RenderQueue::addGC(GraphicsComponent* gc){
	cout<<"Adding gc."<<endl; // <-- REMOVE IN FINAL
	voList.push_back(gc);
}

void RenderQueue::removeGC(GraphicsComponent* gc){
	cout<<"Removing gc."<<endl; // <-- REMOVE IN FINAL
	voList.remove(gc);
}

//extract the first gc from the list and remove it after extraction before returning the pointer
GraphicsComponent* RenderQueue::getNextGC(){
//	cout<<"Getting gc and iterating queue-iterator."<<endl; // <-- REMOVE IN FINAL
	GraphicsComponent* gc = *currentFirstElement;
	currentFirstElement++;
	return gc;
}

//test if gc list is empty
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