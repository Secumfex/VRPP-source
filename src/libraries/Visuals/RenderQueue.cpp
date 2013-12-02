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