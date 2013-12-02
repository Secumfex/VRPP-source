#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue(){

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
	cout<<"Getting VO and removing it from list."<<endl; // <-- REMOVE IN FINAL
	list<VirtualObject*>::iterator i = voList.begin();
	VirtualObject* vo = *i;
	voList.remove(vo);
	return vo;
}

//test if VO list is empty
bool RenderQueue::hasNext(){
	list<VirtualObject*>::iterator i = voList.begin();
	list<VirtualObject*>::iterator i_ = voList.end();
	if(*i == *i_){
		cout<<"VO list empty."<<endl; // <-- REMOVE IN FINAL
		return false;
	}else{
		cout<<"VO list has elements."<<endl; // <-- REMOVE IN FINAL
		return true;
	}
}