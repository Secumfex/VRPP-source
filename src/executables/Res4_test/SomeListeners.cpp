#include "SomeListeners.h"

#include <iostream>


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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 800, 600);


		//activate the current shader
		currentShader = rm->getCurrentShader();
		if (currentShader != 0){
			currentShader->useProgram();
		}
        else std::cout<<"Please SET Shader!"<<endl;
		
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
	Shader* shader = new Shader( SHADERS_PATH "/chest_test/chest_phong.vert", SHADERS_PATH "/chest_test/chest_phong.frag"); 
	rm->setCurrentShader(shader);
}	

SetCurrentShaderListener::SetCurrentShaderListener(Shader* shader){
	rm = RenderManager::getInstance();
	this->shader = shader;}

void SetCurrentShaderListener::update(){
	rm->setCurrentShader(shader);
	shader->useProgram();
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
    
    glm::mat4 new_modelMatrix2 = glm::translate(glm::rotate(glm::mat4(1.0f), glm::degrees(angle), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.5f, 0.5f));
    
	vo->setModelMatrix(new_modelMatrix);
    vo->getGraphicsComponent()[1]->setModelMatrixGc(new_modelMatrix2);
}

/* my Listener for animate a GraphicComponent */
AnimateGraphicComponentListener::AnimateGraphicComponentListener(GraphicsComponent* gc){
    this->gc=gc;
    angle = 0.0;
}

void AnimateGraphicComponentListener::update(){
    angle=fmod((float)(angle+0.001), (float)(pi<float>()*2.0f));

    glm::mat4 new_modelMatrix2 = glm::translate(glm::rotate(glm::mat4(1.0f), glm::degrees(angle), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.5f, -0.5f));
    
    gc->setModelMatrixGc(new_modelMatrix2);
};

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

MovePlayerCameraListener::MovePlayerCameraListener(Camera* pcam, float x, float y, float z){
    this->pcam = pcam;
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;
}
void MovePlayerCameraListener::update(){
    float old_x = pcam->getX();
    float old_y = pcam->getY();
    float old_z = pcam->getZ();
    
    pcam->setPosition(old_x+x_pos,old_y+y_pos,old_z+z_pos);
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
	state->		attachListenerOnBeginningProgramCycle(  new UpdatePhysicsComponentListener(			vo));	// update PhysicsComponent on every program cycle iteration
	state->		attachListenerOnBeginningProgramCycle(  new UpdateVirtualObjectModelMatrixListener(	vo ));	// update VirtualObject Model Matrix on every program cycle iteration
    
}

SetFrameBufferObjectListener::SetFrameBufferObjectListener( FrameBufferObject* fbo){
	this->fbo = fbo;
}

void SetFrameBufferObjectListener::update(){
	if( fbo != 0){
		RenderManager::getInstance()->setCurrentFBO( fbo );
		fbo->bindFBO();
	}
}

UnbindFrameBufferObjectListener::UnbindFrameBufferObjectListener(){
}

void UnbindFrameBufferObjectListener::update(){
	FrameBufferObject* currentFBO = RenderManager::getInstance()->getCurrentFBO();
	if (currentFBO != 0){
		currentFBO->unbindFBO();
	}
	RenderManager::getInstance()->setCurrentFBO( 0 );
}

ReflectionMapRenderPass::ReflectionMapRenderPass(FrameBufferObject* fbo){
    rm = RenderManager::getInstance();
    this->fbo = fbo;
  }

void ReflectionMapRenderPass::update(){
    /***************** save old state ******************/
    FrameBufferObject* tempFBO = rm->getCurrentFBO();
    
    /***************** set shader state and get ready to draw ***************/
    fbo->bindFBO();	// From now on, everything will be written into ColorAttachment0

    rm->setCurrentFBO(fbo);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, fbo->getWidth(), fbo->getHeight());
    
    currentShader = rm->getCurrentShader();
    currentRenderQueue = rm->getRenderQueue();
    
    /***************** render objects ***************/
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
    /****************** back to old state *****************/
    fbo->unbindFBO();	
    rm->setCurrentFBO(tempFBO);
    
}

RenderGraphicsComponentListener::RenderGraphicsComponentListener(GraphicsComponent* gc){
	this->gc = gc;
}

void RenderGraphicsComponentListener::update(){
	if( gc != 0){
		RenderManager::getInstance()->setCurrentGC(gc);
		RenderManager::getInstance()->getCurrentShader()->uploadAllUniforms();
		RenderManager::getInstance()->getCurrentShader()->render(gc);
	}
}

RenderScreenFillingTriangleListener::RenderScreenFillingTriangleListener(){
	this->gc = VirtualObjectFactory::getInstance()->getTriangle();
}

void RenderScreenFillingTriangleListener::update(){
	glDisable(GL_DEPTH_TEST);
	RenderGraphicsComponentListener::update();
	glEnable(GL_DEPTH_TEST);
    
}
