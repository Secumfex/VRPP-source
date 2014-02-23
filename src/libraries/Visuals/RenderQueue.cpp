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

void RenderQueue::addShader(Shader* sh){
	cout<<"Adding Shader to shaderList."<<endl;
	shaderList.push_back(sh);
}

/** \brief adds a VO to the member list of VOs, also maps GC->VO and vice versa
*/
void RenderQueue::addVirtualObject(VirtualObject* vo){
	cout<<"Adding VO."<<endl; // <-- REMOVE IN FINAL
	voList.push_back(vo);

	vector<GraphicsComponent* > gcVector; 

	gcVector = vo->getGraphicsComponent();

	for(unsigned int i = 0; i < gcVector.size(); i++){
		cout<<"Sort: GC->VO, VO->GC"<<endl; // <-- REMOVE IN FINAL

		vo2gcMap[vo].push_back(gcVector[i]); /// VO --> GC
		gc2voMap[gcVector[i]] = vo;
		gcList.push_back(gcVector[i]);
	}
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

/** \brief getter for GCs sorted by flags
*/
map<string, vector<GraphicsComponent* > > RenderQueue::getGcFlagStorage(){
	return gcFlagStorage;
}

/** \brief getter for GCs sorted by shaders
*/
map<string, vector<GraphicsComponent* > > RenderQueue::getGcShaderStorage(){
	return gcShaderStorage;
}

/** \brief getter for GCs sorted by textures
*/
map<string, vector<GraphicsComponent* > > RenderQueue::getGcTexStorage(){
	return gcTexStorage;
}

/** \brief getter for GC->VO map
*/
map<GraphicsComponent*, VirtualObject* > RenderQueue::getGc2VoMap(){
	return gc2voMap;
}

/** \brief getter for VO->GC map
*/
map<VirtualObject*, vector<GraphicsComponent* > > RenderQueue::getVo2GcMap(){
	return vo2gcMap;
}

list<VirtualObject*> RenderQueue::getVirtualObjectList(){
	return voList;
}

void RenderQueue::sortByAttributes(){
	resetQueue();

	GraphicsComponent* gc;
	Shader* sh;

	for(unsigned int i = 0; i < gcList.size(); i++){
		cout<<"Entering sortByAttributes loop"<<endl;
		for(unsigned int j = 0; j < shaderList.size(); j++){
			
		}
	}



}

void RenderQueue::sortByShaders(){
	resetQueue();
	string shader = "DEFERRED_SHADING";
	VirtualObject* vo;
	vector<GraphicsComponent* > gcVector; 


	cout<<"Entering sortByShaders"<<endl; // <-- REMOVE IN FINAL

	while(hasNext()){
		vo = getNextObject();
		gcVector = vo->getGraphicsComponent();
		for(unsigned int i = 0; i < gcVector.size(); i++){
			cout<<"Adding GC to the map."<<endl; // <-- REMOVE IN FINAL

			gcShaderStorage[shader].push_back(gcVector[i]); /// shader --> GC
			vo2gcMap[vo].push_back(gcVector[i]); /// VO --> GC

			gc2voMap[gcVector[i]] = vo;
		}
	}
}
	
void RenderQueue::sortByTextures(){
	resetQueue();
	string texID = "tex_stone";
	VirtualObject* vo;
	vector<GraphicsComponent* > gcTexVector;


	cout<<"Entering sortByTextures"<<endl; // <-- REMOVE IN FINAL

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
	resetQueue();
	string sString = "SHADOW";
	string eString = "EMISSION";
	string tString = "TRANSPARENCY";

	VirtualObject* vo;

	vector<GraphicsComponent* > gcFlagVector;

	cout<<"entering sortByFlags"<<endl; // <-- REMOVE IN FINAL

	while(hasNext()){
		vo = getNextObject();
		gcFlagVector = vo->getGraphicsComponent();
		for(unsigned int i = 0; i < gcFlagVector.size(); i++){
			cout<<"Adding GC to the FlagMap."<<endl;
			
			if(gcFlagVector[i]->hasEmission()){
				gcFlagStorage[eString].push_back(gcFlagVector[i]);
			}

			if(gcFlagVector[i]->hasShadow()){
				gcFlagStorage[sString].push_back(gcFlagVector[i]);
			}

			if(gcFlagVector[i]->hasTransparency()){
				gcFlagStorage[tString].push_back(gcFlagVector[i]);
			}
		}
	}
}

