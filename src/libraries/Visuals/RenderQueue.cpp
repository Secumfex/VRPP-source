#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue(){
resetQueue();
}

RenderQueue::~RenderQueue(){
	
}

/** \brief adds a VO to the member list of VOs
*/
void RenderQueue::addVirtualObject(VirtualObject* vo){
	cout<<"Adding VO."<<endl; // <-- REMOVE IN FINAL
	voList.push_back(vo);
}

/** \brief removes a single VO from the member list of VOs
*/
void RenderQueue::removeVirtualObject(VirtualObject* vo){
	cout<<"Removing VO."<<endl; // <-- REMOVE IN FINAL
	voList.remove(vo);
}

/** \brief extract the first VO from the list and remove it after extraction before returning the pointer
* @return  returns the VO the iterator was pointing at 
*/
VirtualObject* RenderQueue::getNextObject(){
	cout<<"Getting VO and iterating queue-iterator."<<endl; // <-- REMOVE IN FINAL

	VirtualObject* vo = *currentFirstElement;
	currentFirstElement++;
	return vo;
}

/** \brief test if VO list is empty
*/
bool RenderQueue::hasNext(){
	if(currentFirstElement == voList.end()){
		cout<<"no more queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return false;
	}else{
		cout<<"queued Virtual Objects remaining."<<endl; // <-- REMOVE IN FINAL
		return true;
	}
}

/** \brief setting the iterator for the list of VOs to the start therefore resetting the RQ
*/
void RenderQueue::resetQueue(){
	currentFirstElement = voList.begin();
}

/** \brief extract VOs from voList, extract gc-vectors from the VOs, extract the gcs from the vectors, put them into a list in a map
* @param shader ID-string to one of which all GraphicsComponents will be sorted
* @param vo temporary VO pointer variable
* @param gcVector temporary storage for all GCs of each VO, one at a time
* @todo  map<VO, vec<GC> > works fine, map<GC, vec<VO> > however is causing issues and the latter is what we want
*/
void RenderQueue::sortByShaders(){
	resetQueue();
	string shader = "DEFERRED_SHADING"; 
	VirtualObject* vo;
	vector<GraphicsComponent> gcVector; 


	cout<<"Entering extractAndSort"<<endl; // <-- REMOVE IN FINAL

	while(hasNext()){
		vo = getNextObject();
		gcVector = *vo->getGraphicsComponent();
		for(gcIterator = gcVector.begin(); gcIterator != gcVector.end(); gcIterator++){
			cout<<"Adding GC to the map."<<endl; // <-- REMOVE IN FINAL

			gcStorage[shader].push_back(*gcIterator); /// shader --> GC
			gc2voMap[vo].push_back(*gcIterator); /// VO --> GC

			// vo2gcMap[*gcIterator].push_back(vo); <-- doesnt work yet
		}
	}
	


}