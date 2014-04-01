#include "Particle.h"

Particle::Particle( glm::vec3 position, glm::vec3 linear_velocity ){
	this->position = position;
	this->linear_velocity = linear_velocity;
}

void Particle::update(float d_t){
	position += linear_velocity * d_t;
}

void Particle::setPosition(glm::vec3 position){
	this->position = position;
}

void Particle::setLinearVelocity( glm::vec3 linear_velocity){
	this->linear_velocity = linear_velocity;
}

glm::vec3 Particle::getPosition(){
	return position;
}

glm::vec3 Particle::getLinearVelocity(){
	return linear_velocity;
}