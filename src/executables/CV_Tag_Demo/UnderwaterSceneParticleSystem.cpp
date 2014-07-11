#include "UnderwaterSceneParticleSystem.h"
#include <time.h>

using namespace UnderwaterScene;

ParticleSystem::ParticleSystem(glm::vec3* center, float radius) {
	this->center = center;
	this->radius = radius;

	std::srand(time(NULL));	// rand dat
}

void ParticleSystem::update(float d_t) {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i]->update(d_t);
		testConstraint(particles[i]);
	}
}

void ParticleSystem::testConstraint(Particle* particle) {
	float distance = glm::length(glm::vec3(particle->getPosition() - *center));
	if (distance > radius) {
		moveToOppositeSide(particle);
	}

}

void ParticleSystem::moveToOppositeSide(Particle* particle) {
	glm::vec3 centerToParticle = glm::normalize(
			particle->getPosition() - *center);
	particle->setPosition(*center - (centerToParticle) * radius);
}

void ParticleSystem::addRandomParticle() {
	//srand (time(NULL)); seeding must be improved, so far it will remain non-random.
	glm::vec3 offset(0.0f, 0.0f, 0.0f);

	offset.x += ((((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f)
			- radius; // randomize a little bit by adding [-radius, radius] to the mix
	offset.y += ((((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f)
			- radius; // randomize a little bit by adding [-radius, radius] to the mix
	offset.z += ((((float) std::rand() / (float) RAND_MAX) * radius) * 2.0f)
			- radius; // randomize a little bit by adding [-radius, radius] to the mix

	Particle* randParticle = new Particle(*center + offset);

	addParticle(randParticle);
}

void ParticleSystem::addParticle(Particle* particle) {
	particles.push_back(particle);
}

void ParticleSystem::setParticleAmount(int amount) {
	while (getParticleAmount() > amount) {
		removeRandomParticle();
	}
	while (getParticleAmount() < amount) {
		addRandomParticle();
	}
}

void ParticleSystem::removeRandomParticle() {
	// idc, just remove the last one
	particles.pop_back();
}

void ParticleSystem::removeParticle(Particle* particle) {
	std::vector<Particle*> particles_new;
	for (unsigned int i = 0; i < particles.size(); i++) {
		if (particles[i] == particle) {
			continue;
		} else {
			particles_new.push_back(particles[i]);
		}
	}
	particles = particles_new;
}

/********** Getter & Setter ***************/

void ParticleSystem::setRadius(float radius) {
	this->radius = radius;
}

void ParticleSystem::setCenter(glm::vec3* center) {
	this->center = center;
}

glm::vec3* ParticleSystem::getCenter() {
	return center;
}

float ParticleSystem::getRadius() {
	return radius;
}

std::vector<Particle*> ParticleSystem::getParticles() {
	return particles;
}

int ParticleSystem::getParticleAmount() {
	int size = particles.size();
	return size;
}

#include "Visuals/RenderManager.h"
#include "IO/IOManager.h"

ParticlesRenderPass::ParticlesRenderPass(Shader* particles_shader,
		FrameBufferObject* fbo, ParticleSystem* particleSystem, GLint vao) {
	mFBO = fbo;
	mShader = particles_shader;
	mParticleSystem = particleSystem;
	mVAO = vao;

	clearColorBufferBit = true;
	clearDepthBufferBit = true;
	useDepthTest = false;
	useAlphaBlending = true;

	if (mFBO) {
		mViewPort_width = mFBO->getWidth();
		mViewPort_height = mFBO->getHeight();
	} else {
		mViewPort_width = IOManager::getInstance()->getWidth();
		mViewPort_height = IOManager::getInstance()->getHeight();
	}
}

void ParticlesRenderPass::render() {
	if (clearColorBufferBit) {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (clearDepthBufferBit) {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	RenderManager* rm = RenderManager::getInstance();

	notify("PRERENDER");
	std::vector<Particle*> particles = mParticleSystem->getParticles();
	rm->setCurrentVAO(mVAO);
	for (unsigned int i = 0; i < particles.size(); i++) {

		notify("PREUNIFORMUPLOAD");
		mShader->uploadUniform(
				glm::translate(glm::mat4(1.0f), particles[i]->getPosition()),
				"uniformModel");
		mShader->uploadUniform(rm->getCamera()->getViewMatrix(), "uniformView");
		;
		mShader->uploadUniform(rm->getPerspectiveMatrix(),
				"uniformPerspective");
		mShader->uploadUniform(1.0f, "uniformScale");
		mShader->uploadUniform(particles[i]->getPosition(),
				"uniformParticlePosition");
		notify("POSTUNIFORMUPLOAD");

		glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square
	}
	notify("POSTRENDER");
}
