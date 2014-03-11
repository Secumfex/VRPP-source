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

PickRayListener::PickRayListener(Camera* cam){
	this->cam = cam;
	this->phWorld = PhysicWorld::getInstance();
}

void PickRayListener::update(){

	GLFWwindow* window = glfwGetCurrentContext();

	double currentXPos,currentYPos;
	glfwGetCursorPos(window,&currentXPos,&currentYPos);

	/*
	int xPos,yPos;
	xPos = static_cast<int>(currentXPos);
	yPos = static_cast<int>(currentYPos);
	*/

	int currentWidth,currentHeight;
	glfwGetWindowSize(window,&currentWidth,&currentHeight);

	glm::vec3 outOrigin= cam->getPosition();
	glm::vec3 outDirection= cam->getViewDirection();;
	glm::mat4 projectionMatrix = RenderManager::getInstance()->getProjectionMatrix();
	glm::mat4 viewMatrix = IOManager::getInstance()->getCurrentIOHandler()->getViewMatrix();
	phWorld->screenPosToWorldRay(currentXPos,currentYPos,currentWidth,currentHeight,viewMatrix,projectionMatrix,outOrigin,outDirection);
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

	VirtualObject* 	sphere = 	VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/sphere.obj");

	state->addVirtualObject(sphere);
	sphere->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(start.x, start.y, start.z)));
	sphere->getPhysicsComponent()->~PhysicsComponent();
	sphere->setPhysicsComponent(2.0f, start.x, start.y, start.z, 3.0f);
	sphere->physicsComponent->getRigidBody()->setLinearVelocity(dir*speed);
	state->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(sphere));


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

	state->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube));
	*/
}


ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener::ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(SelectionHandler* selectionHandler, Camera* cam, float strength){
	this->selectionHandler = selectionHandler;
	this->cam = cam;
	this->strength = strength; 
}

void ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener::update(){
	if (selectionHandler->somethingIsSelected()){
		/*Pray and Cast*/
		btRigidBody* rigidBody = (static_cast< PhysicsComponent* > (selectionHandler->getCurrentSelection()->getUserPointer()))->getRigidBody();
		/*pray some more and apply force*/
		glm::vec3 force = cam->getViewDirection() * strength;
		std::cout << force.x <<", "<< force.y <<", "<< force.z << std::endl;
		rigidBody->applyCentralImpulse(btVector3(force.x,force.y,force.z));
	}
}