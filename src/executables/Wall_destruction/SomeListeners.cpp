#include "SomeListeners.h"

#include <iostream>

AnimateClearColorListener::AnimateClearColorListener(){
	t = 0.0;
}

void AnimateClearColorListener::update(){
		float r = std::sin(1.0*t) * 0.5;
		float g = std::sin(2.0*t+0.3) * 0.5;
		float b = std::sin(3.0*t+0.7) * 0.5;
		glClearColor(r,g,b,1.0);
		t+= 0.0001;
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

SetClearColorListener::SetClearColorListener(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void SetClearColorListener::update(){
		glClearColor(r,g,b,a);
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

UpdateVirtualObjectModelMatrixListener::UpdateVirtualObjectModelMatrixListener(VirtualObject* vo){
	this->vo = vo;
}

void UpdateVirtualObjectModelMatrixListener::update(){
	vo->updateModelMatrixViaPhysics();
}
#include "Physics/PhysicWorld.h"
UpdatePhysicsWorldListener::UpdatePhysicsWorldListener(){
}

void UpdatePhysicsWorldListener::update(){
	PhysicWorld* pw = PhysicWorld::getInstance();
	pw->dynamicsWorld->stepSimulation(0.1,5,0.02);
}

PrintCameraStatusListener :: PrintCameraStatusListener(Camera* cam){
	this->cam = cam;
}

void PrintCameraStatusListener::update(){
	glm::vec3 pos 	= cam->getPosition();
	glm::vec3 dir 	= cam->getViewDirection();
	float phi 		= cam->getPhi();
	float theta		= cam->getTheta();

	std::cout << "Cam pos : " << pos.x << " , " << pos.y << " , " << pos.z << std::endl;
	std::cout << "Cam dir : " << dir.x << " , " << dir.y << " , " << dir.z << std::endl;
	std::cout << "rotation phi : " << phi   << " , pitch theta : " 		  << theta << std::endl;
}

SetCameraDirectionListener::SetCameraDirectionListener(Camera* cam, glm::vec3 direction){
	this->cam = cam;
	this->direction = direction;
}

void SetCameraDirectionListener::update(){
	cam->setDirection(direction);
}
TurnCameraListener::TurnCameraListener(Camera* cam, float phi, float theta){
	this->cam 	= cam;
	this->theta = theta;
	this->phi 	= phi;
}
void TurnCameraListener::update(){
	float old_phi   = cam->getPhi();
	float old_theta = cam->getTheta();

	cam->setPhi(  old_phi   + phi);
	cam->setTheta(old_theta + theta);
}

//includes for ray-picking
#include "IO/IOManager.h"
#include "IO/IOHandler.h"
#include "Physics/PhysicWorld.h"

PickRayListener::PickRayListener(){

	this->phWorld = PhysicWorld::getInstance();
}

void PickRayListener::update(){

	//int xPos = IOManager::getInstance()->;
	//int yPos = IOManager::getInstance()->;
	//int WIDTH = IOManager::getInstance()->;
	//int HEIGHT = IOManager::getInstance()->;

	glm::vec3 outOrigin;
	glm::vec3 outDirection;
	glm::mat4 projectionMatrix = RenderManager::getInstance()->getProjectionMatrix();
	//IOHandler* handler = IOManager::getInstance()->getCurrentIOHandler;
	glm::mat4 viewMatrix = IOManager::getInstance()->getCurrentIOHandler()->getViewMatrix();
	//glm::mat4 viewMatrix = handler->getViewMatrix();
	//phWorld->screenPosToWorldRay(xPos,yPos,WIDTH,HEIGHT,viewMatrix,projectionMatrix,outOrigin,outDirection);
}
