#include "PlaceHolderListeners.h"
#include <iostream>

RenderloopPlaceHolderListener::RenderloopPlaceHolderListener() {
	rm = RenderManager::getInstance();
}

void RenderloopPlaceHolderListener::update() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 800, 600);

	//activate the current shader
	currentShader = rm->getCurrentShader();
	if (currentShader != 0) {
		currentShader->useProgram();
	}

	//get renderQueue
	currentRenderQueue = rm->getRenderQueue();

	//render GCs with current Shader
	if (currentRenderQueue != 0) {
		voList = currentRenderQueue->getVirtualObjectList(); //get List of all VOs in RenderQueue
		//for every VO
		for (std::list<VirtualObject*>::iterator i = voList.begin();
				i != voList.end(); ++i) {	//get GCs of VO
			currentGCs = (*i)->getGraphicsComponent();
			//for every GC
			for (unsigned int j = 0; j < currentGCs.size(); j++) {
				rm->setCurrentGC(currentGCs[j]);
				rm->getCurrentVO();

				//tell Shader to upload all Uniforms
				currentShader->uploadAllUniforms();
				//render the GC
				currentShader->render(currentGCs[j]);
			}

		}
	}
}

SetDefaultShaderListener::SetDefaultShaderListener(Shader* shader) {
	rm = RenderManager::getInstance();
	this->shader = shader;
}

void SetDefaultShaderListener::update() {
	rm->setCurrentShader(shader);
}

/******************* FEATURE UNDER WATER *********************/
UnderwaterScene::SetClearColorListener::SetClearColorListener(float r, float g,
		float b, float a) {
	this->clearColorVec3 = new glm::vec3(r, g, b);
	this->clearColorVec4 = 0;
	this->a = a;
}

UnderwaterScene::SetClearColorListener::SetClearColorListener(
		glm::vec3* clearColor, float a) {
	this->clearColorVec3 = clearColor;
	this->clearColorVec4 = 0;
	this->a = a;
}

UnderwaterScene::SetClearColorListener::SetClearColorListener(
		glm::vec4* clearColor) {
	this->clearColorVec4 = clearColor;
	this->clearColorVec3 = 0;
	this->a = a;
}

void UnderwaterScene::SetClearColorListener::update() {
	if (clearColorVec4 == 0) {
		glClearColor(clearColorVec3->x, clearColorVec3->y, clearColorVec3->z,
				a);
	} else {
		glClearColor(clearColorVec4->r, clearColorVec4->g, clearColorVec4->b,
				clearColorVec4->a);
	}
}

UnderwaterScene::UnderOrAboveWaterListener::UnderOrAboveWaterListener(
		Camera* cam, float* sea_level_y, Listener* EnterWaterListener,
		Listener* ExitWaterListener) {
	this->cam = cam;
	this->sea_level_y = sea_level_y;
	this->EnterWaterListener = EnterWaterListener;
	this->ExitWaterListener = ExitWaterListener;
	underwater = false;
}

void UnderwaterScene::UnderOrAboveWaterListener::update() {
	if (cam->getPosition().y < *(this->sea_level_y)) {
		if (!underwater) {
			if (EnterWaterListener != 0) {
				EnterWaterListener->update();
			}
			underwater = true;
		}
	} else {
		if (underwater) {
			if (ExitWaterListener != 0) {
				ExitWaterListener->update();
			}
			underwater = false;
		}
	}
}

UnderwaterScene::UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(
		Camera* cam, Camera* cam_target, float* water_height) {
	this->water_height = water_height;
	this->cam_source = cam;
	this->cam_target = cam_target;
}

UnderwaterScene::UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(
		Camera* cam, Camera* cam_target, float water_height) {
	this->water_height = new float(water_height);
	this->cam_source = cam;
	this->cam_target = cam_target;
}

void UnderwaterScene::UpdateReflectedCameraPositionListener::update() {
	glm::vec3 reflected_campos = cam_source->getPosition();
	glm::vec3 reflected_center = cam_source->getPosition()
			+ cam_source->getViewDirection();
	reflected_campos.y = 2.0f * *water_height - reflected_campos.y;
	reflected_center.y = 2.0f * *water_height - reflected_center.y;
	(*cam_target).setPosition(reflected_campos);
	(*cam_target).setCenter(reflected_center);
}

UnderwaterScene::UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(
		std::string name, float* t, float frequency, float phase,
		std::string uniform_name) {
	this->t = t;
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

UnderwaterScene::UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(
		std::string name, float t, float frequency, float phase,
		std::string uniform_name) {
	this->t = new float(t);
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

void UnderwaterScene::UploadUniformSinusWaveListener::update() {
	float sinus = std::sin((*t) * frequency + phase);

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform(sinus, uniform_name);
}
UnderwaterScene::UpdateParticleSystemListener::UpdateParticleSystemListener(
		ParticleSystem* particleSystem, float* t) {
	this->particleSystem = particleSystem;
	this->t = t;
}

void UnderwaterScene::UpdateParticleSystemListener::update() {
	particleSystem->update(*t);
}

UnderwaterScene::KeepOffsetListener::KeepOffsetListener(VirtualObject* vo,
		glm::vec3* target, glm::vec3* offset) {

	this->vo = vo;
	this->target = target;
	this->offset = offset;

	if (!offset) {
		offset = new glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void UnderwaterScene::KeepOffsetListener::update() {
	glm::vec3 targetPosition = *target + *offset;
	vo->getPhysicsComponent()->setPosition(targetPosition.x, targetPosition.y,
			targetPosition.z);
	vo->updateModelMatrixViaPhysics();
}
