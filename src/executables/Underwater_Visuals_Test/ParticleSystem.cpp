#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(glm::vec3* center, float radius){
	this->center = center;
	this->radius = radius;

	std::srand (time(NULL));	// rand dat
}


void ParticleSystem::update(float d_t){
	for (unsigned int i = 0; i < particles.size(); i ++){
		particles[i]->update( d_t );
		testConstraint( particles[i] );
	}
}


void ParticleSystem::testConstraint(Particle* particle){
	float distance = glm::length( glm::vec3( particle->getPosition() - *center ) );
	if ( distance > radius ){
		moveToOppositeSide ( particle );
	}

}


void ParticleSystem::moveToOppositeSide( Particle* particle ){
	glm::vec3 centerToParticle = particle->getPosition() - *center;
	particle->setPosition( *center - ( centerToParticle * 0.9f) );
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
