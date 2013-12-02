#include "RenderQueue.h"

RenderQueue::RenderQueue(){

}

RenderQueue::~RenderQueue(){
	
}

void RenderQueue::addVirtualObject(VirtualObject* vo){
	voList.push_back(vo);
}

void RenderQueue::removeVirtualObject(VirtualObject* vo){
	voList.remove(vo);
}

//extract the first VO from the list and remove it after extraction before returning the pointer
VirtualObject* RenderQueue::getNextObject(){
	list<VirtualObject*>::iterator i = voList.begin();
	VirtualObject* vo = *i;
	voList.remove(vo);
	return vo;
}
