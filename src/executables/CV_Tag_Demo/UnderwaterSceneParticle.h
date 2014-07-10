#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

namespace UnderwaterScene
{

class Particle {
private:
	glm::vec3 position;
	glm::vec3 linear_velocity;
public:
	Particle( glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 linear_velocity = glm::vec3( 0.0f, 0.0f, 0.0f ) );
	void update( float d_t );

	void setPosition( glm::vec3 position );
	void setLinearVelocity( glm::vec3 linear_velocity );

	glm::vec3 getPosition();
	glm::vec3 getLinearVelocity();
};

}
#endif
