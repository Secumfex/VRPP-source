#include "UpdatePhysicsComponentListener.h"
#include "PhysicsComponent.h"

#include <iostream>

UpdatePhysicsComponentListener::UpdatePhysicsComponentListener(PhysicsComponent* physicsComponent){
	this->physicsComponent = physicsComponent;
}
void UpdatePhysicsComponentListener::update(){
	this->physicsComponent->update();
}
