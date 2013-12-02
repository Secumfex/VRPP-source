#include <iostream>
#include "PhysicsComponent.h"

#include <glm/glm.hpp>

using namespace std;

PhysicsComponent::PhysicsComponent(glm::mat4 modelMatrix){

	this-> modelMatrix = modelMatrix;

}

//listener pattern bei kollision

PhysicsComponent::~PhysicsComponent(){

}

glm::mat4 PhysicsComponent::getModelMatrix(){

	return modelMatrix;
}

