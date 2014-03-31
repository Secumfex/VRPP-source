#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <glm/glm.hpp>
#include <stdlib.h>

#include <Patterns/Subject.h>
#include <vector>

#include "Particle.h"

class ParticleSystem : public Subject {
private:
	std::vector< Particle* > particles;
	
	glm::vec3* center;
	float radius;	

	void testConstraint( 	 Particle* particle );
	void moveToOppositeSide( Particle* particle );
public:
	ParticleSystem( glm::vec3* center = new glm::vec3( 0.0f, 0.0f, 0.0f), float radius = 1.0f );
	void update(float d_t);

	void addRandomParticle();
	void addParticle(		 Particle* particle);
	
	void removeRandomParticle();
	void removeParticle(	 Particle* particle);

	/*Getter & Setter*/
	void setRadius(float radius);
	void setCenter(glm::vec3* center);

	glm::vec3* 	getCenter();
	float 		getRadius();
	std::vector< Particle* > getParticles();
	int getParticleAmount();
};

#endif