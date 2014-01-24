#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue(){
resetQueue();
}

RenderQueue::~RenderQueue(){
	
}

/** \brief returns a pointer to this RenderQueue
*/
RenderQueue* RenderQueue::getRenderQueue(){
	return this;
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

//Alternativ einfach nur sort Methode (alle auskommentieren Zeilen einfügen -> weniger Maps

//void RenderQueue::sorteGC2map(){
//	resetQueue();
//	string shader = "DEFERRED_SHADING";
//	string texture = "TEX_ID";
//	VirtualObject* vo;
//	vector<GraphicsComponent* > gcVector;
//
//
//	cout<<"Entering extractAndSort"<<endl; // <-- REMOVE IN FINAL
//
//	while(hasNext()){
//		vo = getNextObject();
//		gcVector = vo->getGraphicsComponent();
//		for(unsigned int i = 0; i < gcVector.size(); i++){
//			cout<<"Adding GC to the map."<<endl; // <-- REMOVE IN FINAL
//
//			gcStorage[shader].push_back(gcVector[i]); /// shader --> GC
//			gcStorage[texture].push_back(gcVector[i]); ///texture --> GC
//			gc2voMap[vo].push_back(gcVector[i]); /// VO --> GC
//
//
//			vo2gcMap[gcVector[i]] = vo;
//		}
//	}
//}

void RenderQueue::sortByShaders(){
	resetQueue();
	string shader = "DEFERRED_SHADING";
	VirtualObject* vo;
	vector<GraphicsComponent* > gcVector; 


	cout<<"Entering extractAndSort"<<endl; // <-- REMOVE IN FINAL

	while(hasNext()){
		vo = getNextObject();
		gcVector = vo->getGraphicsComponent();
		for(unsigned int i = 0; i < gcVector.size(); i++){
			cout<<"Adding GC to the map."<<endl; // <-- REMOVE IN FINAL

			gcStorage[shader].push_back(gcVector[i]); /// shader --> GC
			gc2voMap[vo].push_back(gcVector[i]); /// VO --> GC

			vo2gcMap[gcVector[i]] = vo;
		}
	}
}
	
void RenderQueue::sortByTextures(){
	resetQueue();
	string texID = "tex_stone";
	VirtualObject* vo;
	vector<GraphicsComponent* > gcTexVector;


	cout<<"Entering extractAndSort"<<endl; // <-- REMOVE IN FINAL

	while(hasNext()){
		vo = getNextObject();
		gcTexVector = vo->getGraphicsComponent();
		for(unsigned int i = 0; i < gcTexVector.size(); i++){
			cout<<"Adding GC to the TextureMap."<<endl; // <-- REMOVE IN FINAL

			gcTexStorage[texID].push_back(gcTexVector[i]); /// texture --> GC
			gcTex2voMap[vo].push_back(gcTexVector[i]); /// VO --> GC

			vo2gcTexMap[gcTexVector[i]] = vo;
		}
	}
}

void RenderQueue::sortByFlags(){
	
}
