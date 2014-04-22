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

 ApplyForceOnCameraListener::ApplyForceOnCameraListener(PlayerCamera* cam,Kinect* kinect, float* strength){
	 this->kinect=kinect;
	 this->cam=cam;
	 this->strength= strength;
}

 void ApplyForceOnCameraListener::update(){
	 float temp=0;
	 float strength=0;

	temp = kinect->getKinectData(kinect->data);
	
	if(temp!=0 && !(kinect->isnew))
	{
		//update values
	 kinect->forceOld=kinect->forceNew;
	kinect->forceNew=temp;
 
	// Switch flag - slower updates
	 kinect->isnew=true;
	
	 /*calculate which direction
	 * threshhold depend on how fast you "swim"
	 *
	 *
	 */
	 if(kinect->forceNew-1.7f>kinect->forceOld){ strength=0.3;}
    else if(kinect->forceNew+2.8f<kinect->forceOld){strength=-1.85;} 
	else strength=0.0f; 

	std::cout<<strength<<endl;
	}

	//switch flag
	kinect->isnew=false;

	//apply strength on cameraview
 btRigidBody* rigidBody = cam->getRigidBody();
 glm::vec3 force = cam->getViewDirection() * strength;
 rigidBody->applyCentralImpulse(btVector3(force.x,force.y,force.z));	
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

ApplyLinearImpulseOnRigidBody::ApplyLinearImpulseOnRigidBody(btRigidBody* rigidBody, glm::vec3 force){
	this->rigidBody = rigidBody;
	this->force = force;
}

void ApplyLinearImpulseOnRigidBody::update(){
	rigidBody->applyCentralImpulse(btVector3(force.x,force.y,force.z));	
}

SetCameraPositionListener::SetCameraPositionListener(Camera* cam, glm::vec3 position){
	this->cam 			= cam;
	this->position = position;
}

void SetCameraPositionListener::update(){
	cam->setPosition(position);
}

void SwimCam::updatePosition(float deltaTime)
{
		//overwrite current Position with current Rigid Body Position and Apply current Movementforces
	if (rigidBody != 0){
	    btVector3 rigidBody_pos = rigidBody->getWorldTransform().getOrigin();
	    Camera::setPosition(glm::vec3(rigidBody_pos.getX(), rigidBody_pos.getY() + 0.25f, rigidBody_pos.getZ()));
	}
}