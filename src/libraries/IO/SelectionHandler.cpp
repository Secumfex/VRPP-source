#include "SelectionHandler.h"

#include "Physics/PhysicWorld.h"

SelectionHandler::SelectionHandler(PhysicWorld* pw){
	if (pw != 0){
		this->physicWorld = pw;
	}else{
		physicWorld = PhysicWorld::getInstance();
	}
	currentSelection = 0;
}

bool SelectionHandler::somethingIsSelected(){
	if (currentSelection != 0){
		return true;
	}
	else{
		return false;
	}
}

void SelectionHandler::trySelection(glm::vec3& from, glm::vec3& to){
	btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(from.x, from.y, from.z), btVector3(to.x, to.y, to.z));
	physicWorld->dynamicsWorld->rayTest(btVector3(from.x, from.y, from.z), btVector3(to.x, to.y, to.z), RayCallback);

	if(RayCallback.hasHit()) {
	    currentSelection = RayCallback.m_collisionObject;
	}
	else{
		currentSelection = 0;
	}
	notify("TRY_SELECTION_LISTENER");
}

const btCollisionObject* SelectionHandler::getCurrentSelection(){
	return currentSelection;
}

void SelectionHandler::handleSelection(){
	notify("HANDLE_SELECTION_LISTENER");
}

void SelectionHandler::attachListenerOnHandleSelection(Listener* listener){
	listener->setName("HANDLE_SELECTION_LISTENER");
	attach(listener);
}

void SelectionHandler::attachListenerOnTrySelection(Listener* listener){
	listener->setName("TRY_SELECTION_LISTENER");
	attach(listener);
}