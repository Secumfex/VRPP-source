#include "PlaceHolderListeners.h"
#include <iostream>

AnimateClearColorListener::AnimateClearColorListener(float* delta_time_source){
	if(delta_time_source != 0){
		this->delta_time_source == delta_time_source;
	}
	else{
		this->delta_time_source = 0;
	}
	t = 0.0;
}

void AnimateClearColorListener::update(){
		float r = std::sin(1.0*t) * 0.5;
		float g = std::sin(2.0*t+0.3) * 0.5;
		float b = std::sin(3.0*t+0.7) * 0.5;
		glClearColor(r,g,b,1.0);
		if (delta_time_source != 0){
			t+= *delta_time_source;
		}
		else{
			t+= 0.0001;
		}
	}

AlternativeRenderloopListener::AlternativeRenderloopListener(){
		rm = RenderManager::getInstance();
	}


#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using namespace glm;

void AlternativeRenderloopListener::update(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, 800, 600);


		//activate the current shader
		currentShader = rm->getCurrentShader();
		if (currentShader != 0){
			currentShader->useProgram();
		}

		//get renderQueue
		currentRenderQueue = rm->getRenderQueue();


		//render GCs with current Shader
		if ( currentRenderQueue != 0 ){
			voList = currentRenderQueue->getVirtualObjectList();	//get List of all VOs in RenderQueue
			//for every VO
			for (std::list<VirtualObject* >::iterator i = voList.begin(); i != voList.end(); ++i) {	//get GCs of VO
				currentGCs = (*i)->getGraphicsComponent();
					//for every GC
					for (unsigned int j = 0; j < currentGCs.size(); j++){
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

SetAlternativeDefaultRenderManagerPointersListener::SetAlternativeDefaultRenderManagerPointersListener(){
	rm = RenderManager::getInstance();
}

void SetAlternativeDefaultRenderManagerPointersListener::update(){
	Shader* shader = new Shader( SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag");
	rm->setCurrentShader(shader);
}

AnimateRotatingModelMatrixListener::AnimateRotatingModelMatrixListener(VirtualObject* vo){
	this->vo = vo;
	angle = 0.0;
}

void AnimateRotatingModelMatrixListener::update(){
    //rotation angle
    angle = fmod((float)(angle+0.001), (float)(pi<float>()*2.0f));

	glm::mat4 new_modelMatrix = glm::translate(glm::rotate(glm::mat4(1.0f), glm::degrees(angle), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.5f, -0.5f));

	vo->setModelMatrix(new_modelMatrix);
}

AnimateSinusModelMatrixListener::AnimateSinusModelMatrixListener(VirtualObject* vo){
	this->vo = vo;
	t = 0.0;
	old_sinus = 0.0;
}

void AnimateSinusModelMatrixListener::update(){
	t+= 0.001;
	float new_sinus = std::sin(t);
	float delta_sinus = new_sinus - old_sinus;

	glm::mat4 new_modelMatrix = glm::translate(vo->getModelMatrix(), glm::vec3(delta_sinus*1.5, 0.0, 0.0));

	vo->setModelMatrix(new_modelMatrix);

    old_sinus = new_sinus;
}

SetCameraDirectionListener::SetCameraDirectionListener(Camera* cam, glm::vec3 direction){
	this->cam = cam;
	this->direction = direction;
}

void SetCameraDirectionListener::update(){
	cam->setDirection(direction);
}

SetCameraPositionListener::SetCameraPositionListener(Camera* cam, glm::vec3 position){
	this->cam 			= cam;
	this->position = position + glm::vec3(0.0, 1.0, 0.0);
}

void SetCameraPositionListener::update(){
	cam->setPosition(cam->getPosition()+position);
}


#include <stdlib.h>
#include <time.h>

CreateVirtualObjectListener::CreateVirtualObjectListener(string path, glm::vec3 position, ApplicationState* state, float random_offset, VirtualObjectFactory::BodyType bodyType, float mass){
	this->state = state;
	this->position = position;
	this->path = path;
	this->random_offset = random_offset;
	std::srand (time(NULL));	// rand dat
	this->bodyType = bodyType;
	this->mass = mass;
}

#include "Physics/UpdatePhysicsComponentListener.h"

void CreateVirtualObjectListener::update(){
	VirtualObject* vo = state->createVirtualObject(path, bodyType, mass);		// create new Virtual Object
	if (random_offset != 0.0){
		glm::vec3 randPos = position;
		randPos.x += ( (((float) std::rand() / (float) RAND_MAX) * random_offset) * 2.0 ) - random_offset; // randomize a little bit by adding [-random_offset, random_offset] to the mix
		randPos.y += ( (((float) std::rand() / (float) RAND_MAX) * random_offset) * 2.0 ) - random_offset; // randomize a little bit by adding [-random_offset, random_offset] to the mix
		randPos.z += ( (((float) std::rand() / (float) RAND_MAX) * random_offset) * 2.0 ) - random_offset; // randomize a little bit by adding [-random_offset, random_offset] to the mix
		vo->translate(randPos);
	}
	else{
		vo->translate(position);	// assign PhysicsComponent
	}
//	state->		attachListenerOnBeginningProgramCycle(  new UpdatePhysicsComponentListener(			vo));	// update PhysicsComponent on every program cycle iteration
}




RenderloopPlaceHolderListener::RenderloopPlaceHolderListener(){ 
		rm = RenderManager::getInstance(); 
	}

void RenderloopPlaceHolderListener::update(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, 800, 600);


		//activate the current shader
		currentShader = rm->getCurrentShader();
		if (currentShader != 0){
			currentShader->useProgram();
		}
		
		//get renderQueue	
		currentRenderQueue = rm->getRenderQueue(); 


		//render GCs with current Shader 
		if ( currentRenderQueue != 0 ){
			voList = currentRenderQueue->getVirtualObjectList();	//get List of all VOs in RenderQueue
			//for every VO
			for (std::list<VirtualObject* >::iterator i = voList.begin(); i != voList.end(); ++i) {	//get GCs of VO
				currentGCs = (*i)->getGraphicsComponent();
					//for every GC
					for (unsigned int j = 0; j < currentGCs.size(); j++){
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

SetDefaultShaderListener::SetDefaultShaderListener(Shader* shader){
	rm = RenderManager::getInstance();
	this->shader = shader;}

void SetDefaultShaderListener::update(){
	rm->setCurrentShader(shader);
}	

SetClearColorListener::SetClearColorListener(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void SetClearColorListener::update(){
		glClearColor(r,g,b,a);
}

ApplyLinearImpulseOnRigidBody::ApplyLinearImpulseOnRigidBody(btRigidBody* rigidBody, glm::vec3 force){
	this->rigidBody = rigidBody;
	this->force = force;
}

void ApplyLinearImpulseOnRigidBody::update(){
	rigidBody->applyCentralImpulse(btVector3(force.x, force.y, force.z));
}

UploadUniformVOListener::UploadUniformVOListener(std::string name, VirtualObject* vo, std::string uniform_name){
	setName(name);
	this->vo 	=  vo;
	this->uniform_name 	= uniform_name;
}

void UploadUniformVOListener::update(){
	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( vo->getPhysicsComponent()->getPosition(), uniform_name);
}

#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Tools/NoAssimpVirtualObjectFactory.h"

ShootSphereListener::ShootSphereListener(Camera* cam, VRState* state){
	this->cam = cam;
	this->state = state;
}
void ShootSphereListener::update(){
	glm::vec3 start = cam->getPosition();
	glm::vec3 view = cam->getViewDirection();
	btVector3 dir = btVector3(view.x, view.y, view.z);
	btScalar speed = 30;

	VirtualObject* 	sphere = 	state->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 3.0, 8);

	sphere->translate(glm::vec3(start.x, start.y, start.z));
	//sphere->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(start.x, start.y, start.z)));
	//sphere->getPhysicsComponent()->setPosition(start.x, start.y, start.z);

	//sphere->setPhysicsComponent(1.0f,1.0f,1.0f,start.x, start.y, start.z, 3.0f, 8);
	sphere->physicsComponent->getRigidBody()->setLinearVelocity(dir*speed);


	/*
	VirtualObject* sphere = new VirtualObject(0.2f, 0.2f, 0.2f, start.x, start.y, start.z, 1.0f);
	VirtualObject* sphere = new VirtualObject(0.2f, start.x, start.y, start.z, 1.0f);
	sphere->addGraphicsComponent(new GraphicsComponent);
	VirtualObject* cube = VirtualObjectFactory::getInstance()->createNonAssimpVO();
	 */

	/*
	VirtualObject* 	cube = 	VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/cube.obj");

	state->addVirtualObject(cube);
	cube->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(start.x, start.y, start.z)));
	cube->getPhysicsComponent()->~PhysicsComponent();
	cube->setPhysicsComponent(1.0f, 1.0f, 1.0f, start.x, start.y, start.z, 3.0f);
	cube->physicsComponent->getRigidBody()->setLinearVelocity(dir*speed);
	std::cout << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	*/
}
