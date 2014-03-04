#include "UpdatePhysicsComponentListener.h"
#include "PhysicsComponent.h"
#include "Visuals/VirtualObject.h"

#include <iostream>

UpdatePhysicsComponentListener::UpdatePhysicsComponentListener(VirtualObject* virObj){
	this->vo = virObj;
}
void UpdatePhysicsComponentListener::update(){
	this->vo->updateModelMatrixViaPhysics();
}
