#ifndef UNDERWATERSCENEPARTICLESYSTEM_H
#define UNDERWATERSCENEPARTICLESYSTEM_H

#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

#include <Patterns/Subject.h>
#include <vector>

#include "UnderwaterSceneParticle.h"
#include "Visuals/RenderPass.h"

namespace UnderwaterScene
{
	class ParticleSystem : public Subject {
	private:
		std::vector< UnderwaterScene::Particle* > particles;

		glm::vec3* center;
		float radius;

		void testConstraint( 	 UnderwaterScene::Particle* particle );
		void moveToOppositeSide( UnderwaterScene::Particle* particle );
	public:
		ParticleSystem( glm::vec3* center = new glm::vec3( 0.0f, 0.0f, 0.0f), float radius = 1.0f );
		void update(float d_t);

		void addRandomParticle();
		void addParticle(		 UnderwaterScene::Particle* particle);
		void setParticleAmount (int amount);

		void removeRandomParticle();
		void removeParticle(	 UnderwaterScene::Particle* particle);

		/*Getter & Setter*/
		void setRadius(float radius);
		void setCenter(glm::vec3* center);
	
		glm::vec3* 	getCenter();
		float 		getRadius();
		std::vector< UnderwaterScene::Particle* > getParticles();
		int getParticleAmount();
	};
	
	/**
	 * A Render Pass specifically for Particlesystems
	 * note that there is no regular shader-uniform-upload call, so most uniforms must be uploaded manually
	 */
	class ParticlesRenderPass : public RenderPass
	{
	private:
		GLint mVAO;
		UnderwaterScene::ParticleSystem* mParticleSystem;
	public:
		/** \brief
		 * @param particle_shader shader to be used to render particles
		 * @param fbo framebufferobject to be used as render target
		 * @param particleSystem particle system to be rendered
		 * @param vao vertex array object to be used as particle geometry
		 */
		ParticlesRenderPass(Shader* particle_shader, FrameBufferObject* fbo, UnderwaterScene::ParticleSystem* particleSystem, GLint vao);
		void render();
	};

	class ParticlesGBufferRenderPass : public GBufferRenderPass
	{
		//TODO like above, but rendering into Draw Buffers and using the FBO's native Depth Buffer, instead of a uniform Texture
	};

} // namespace UnderwaterScene
#endif
