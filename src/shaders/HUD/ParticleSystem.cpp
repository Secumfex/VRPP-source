#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(glm::vec3* center, float radius){
	this->center = center;
	camOld = *center;
	camNew = camOld;
	this->radius = radius;

	std::srand (time(NULL));	// rand dat
}


void ParticleSystem::update(float d_t){
	camOld = camNew;
	camNew = *center;
	oldToNew = camNew - camOld;
	if(camOld != camNew)
		for (unsigned int i = 0; i < particles.size(); i ++){
			updateHUDPosition( particles[i] );
		}
}


void ParticleSystem::updateHUDPosition( Particle* particle ){
//	glm::vec3 centerToParticle = glm::normalize( particle->getPosition() - *center );
//	std::cout<<"Old:  x: "<<camOld.x<<",    "<<"y: "<<camOld.y<<",    "<<"z: "<<camOld.z<<endl;
//	std::cout<<"New:  x: "<<camNew.x<<",    "<<"y: "<<camNew.y<<",    "<<"z: "<<camNew.z<<endl;
//	std::cout<<"TO:   x: "<<oldToNew.x<<",    "<<"y: "<<oldToNew.y<<",    "<<"z: "<<oldToNew.z<<endl;
//	std::cout<<"POld:  x: "<<particle->getPosition().x<<",    "<<"y: "<<particle->getPosition().y<<",    "<<"z: "<<particle->getPosition().z<<endl;
	particle->setPosition( particle->getPosition() + oldToNew );
//	std::cout<<"PNew:  x: "<<particle->getPosition().x<<",    "<<"y: "<<particle->getPosition().y<<",    "<<"z: "<<particle->getPosition().z<<endl;
}


void ParticleSystem::addRandomParticle(){
	glm::vec3 offset(0.0f, 0.0f, 0.0f);

	offset.x += ( (((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f ) - radius; // randomize a little bit by adding [-radius, radius] to the mix
	offset.y += ( (((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f ) - radius; // randomize a little bit by adding [-radius, radius] to the mix
	offset.z += ( (((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f ) - radius; // randomize a little bit by adding [-radius, radius] to the mix
		
	Particle* randParticle = new Particle( *center + offset );

	addParticle( randParticle );
}


void ParticleSystem::addParticle( Particle* particle ){
	particles.push_back( particle );
}

void ParticleSystem::setParticleAmount(int amount){
	while ( getParticleAmount() > amount){
		removeRandomParticle();
	}
	while ( getParticleAmount()	< amount ){
		   addRandomParticle();
	}
}


void ParticleSystem::removeRandomParticle(){
	// idc, just remove the last one
	particles.pop_back();
}


void ParticleSystem::removeParticle( Particle* particle ){
	std::vector< Particle* > particles_new;
	for ( unsigned int i = 0; i < particles.size(); i++ ){
		if (particles[i] == particle){
			continue;
		}else{
			particles_new.push_back( particles[i] ); 
		}
	}
	particles = particles_new;
}

/********** Getter & Setter ***************/

void ParticleSystem::setRadius(float radius){
	this->radius = radius;
}

void ParticleSystem::setCenter(glm::vec3* center){
	this->center = center;
}

glm::vec3* ParticleSystem::getCenter(){
	return center;
}

float ParticleSystem::getRadius(){
	return radius;
}

std::vector< Particle* > ParticleSystem::getParticles(){
	return particles;
}

int ParticleSystem::getParticleAmount(){
	int size = particles.size(); 
	return size;
}
