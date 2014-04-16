/*
 * Boid.cpp
 *
 *  Created on: 16.04.2014
 *      Author: Raphimulator
 */

#include <Animation/Boid.h>

Boid::Boid(VirtualObject* vo) {
	mVirtualObject = vo;
}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

void Boid::setBaseMatrix(glm::mat4 mat){
mBaseMatrix = mat;
}
void Boid::setPosition(glm::vec3 pos){
	mPosition = pos;
}
void Boid::setVelocity(glm::vec3 vel){
	mVelocity = vel;
}
void Boid::setVirtualObject(VirtualObject* vo){
	mVirtualObject = vo;
}
VirtualObject* Boid::getVirtualObject(){
	return mVirtualObject;
}
glm::vec3 Boid::getPosition(){
	return mPosition;
}
glm::vec3 Boid::getVelocity(){
	return mVelocity;
}
glm::mat4 Boid::getBasePosition(){
	return mBaseMatrix;
}
