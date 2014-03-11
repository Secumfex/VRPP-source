#include "PlaceHolderListeners.h"

#include <iostream>
#include <typeinfo>


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



TurnCameraListener::TurnCameraListener(Camera* cam, float delta_phi, float delta_theta){
	this->cam 			= cam;
	this->delta_theta 	= delta_theta;
	this->delta_phi 	= delta_phi;
}

void TurnCameraListener::update(){
	float old_phi   = cam->getPhi();
	float old_theta = cam->getTheta();

	cam->setPhi(  old_phi   + delta_phi);
	cam->setTheta(old_theta + delta_theta);
}

ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener::ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(SelectionHandler* selectionHandler, Camera* cam, float strength){
	this->selectionHandler = selectionHandler;
	this->cam = cam;
	this->strength = strength; 
}

void ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener::update(){
	if (selectionHandler->somethingIsSelected()){
		/*Pray and Cast*/
		void* userPointer = selectionHandler->getCurrentSelection()->getUserPointer();
		if 	(userPointer != 0){
			btRigidBody* rigidBody = (static_cast< PhysicsComponent* > (userPointer))->getRigidBody();
			/*pray some more and apply force*/
			glm::vec3 force = cam->getViewDirection() * strength;
			rigidBody->applyCentralImpulse(btVector3(force.x,force.y,force.z));	
		}
	}
}

UpdateVirtualObjectModelMatrixListener::UpdateVirtualObjectModelMatrixListener(VirtualObject* vo){
	this->vo = vo;
}

void UpdateVirtualObjectModelMatrixListener::update(){
	vo->updateModelMatrixViaPhysics();
}

