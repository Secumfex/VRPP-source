#include "UpdatePhysicsComponentListener.h"
#include "PhysicsComponent.h"

#include <iostream>

UpdatePhysicsComponentListener::Listener(PhysicsComponent* physicsComponent){
	this->physicsComponent = physicsComponent;
}
void UpdatePhysicsComponentListener::update(){
	physicsComponent->update();
}
