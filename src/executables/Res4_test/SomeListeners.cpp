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
#include <glm/ext.hpp>

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
                        
                        /* request for NormalMap */
                        bool normalMap = currentGCs[j]->hasNormalMap();
                        glm::vec3 colorcheck = glm::vec3(1.0,0.0,0.0);
                       // std::cout<<"CHECK: "<<normalMap<<endl;
                        Listener* normalMapCheck 	= new UploadUniformBooleanListener	("UNIFORMUPLOADLISTENER", normalMap, "uniformNormalMap");
                        Listener* colorCheck        = new UploadUniformVec3Listener     ("UNIFORMUPLOADLISTENER", colorcheck, "uniformColorCheck");
						rm->getCurrentVO();

                        currentShader->attach(normalMapCheck);
                        currentShader->attach(colorCheck);
                        
                        
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
    shader->useProgram();
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
    if (angle >= 90.0f){
        angle = 90.0f;

    }
    else{
            angle += 0.5f;
    }

    glm::mat4 saveMatrix = glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(0.0,0.7,1.0)), 180.0f, glm::vec3(0.0,1.0,1.0));
    glm::mat4 new_modelMatrix = glm::rotate(glm::translate(glm::vec3(0.0,2.0,-1.0)), -angle, glm::vec3(1.0,0.0,0.0))*saveMatrix;

	vo->setModelMatrix(new_modelMatrix);
    
}

/* my Listener for animate a GraphicComponent */
AnimateGraphicComponentListener::AnimateGraphicComponentListener(GraphicsComponent* gc, VirtualObject* vo){
    this->gc=gc;
    this->vo=vo;
    angle = 0.0;
}

void AnimateGraphicComponentListener::update(){
    angle=fmod((float)(angle+0.001), (float)(pi<float>()*2.0f));

    glm::mat4 new_modelMatrix2 = glm::translate(glm::rotate(glm::mat4(1.0f), glm::degrees(angle), glm::vec3(1.0f, 1.0f, 0.0f)), glm::vec3(0.0f, 0.5f, -0.5f));
        gc->setModelMatrixGc(new_modelMatrix2);
    std::cout<<"andere Matrix gesetzt!";
    glm::mat4 new_modelMatrix = glm::mat4(1.0f);
    for (int i=0;i<vo->getGraphicsComponent().size();i++){
        new_modelMatrix = new_modelMatrix * vo->getGraphicsComponent()[i]->getModelMatrix();
        std::cout<<vo->getGraphicsComponent()[i]->getMaterial()->getName()<<": ";
        {
            int m,n;
            for (n=0; n<4; n++){
                for (m=0; m<4; m++){
                    std::cout<<vo->getModelMatrix()[m][n];
                }
                std::cout<<"\n";
            }
        }
    }
    vo->setModelMatrix(new_modelMatrix);

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

MovePlayerCameraListener::MovePlayerCameraListener(Camera* pcam, float x, float y, float z, VirtualObject* vo_1, VirtualObject* vo_2, btRigidBody* camBody){
    this->pcam = pcam;
    this->x_pos = x;
    this->y_pos = y;
    this->z_pos = z;
    this->vo_1 = vo_1;
    this->vo_2 = vo_2;
    this->camBody = camBody;
}
void MovePlayerCameraListener::update(){
    float old_x = pcam->getX();
    float old_y = pcam->getY();
    float old_z = pcam->getZ();
    
    pcam->setPosition(old_x+x_pos,old_y+y_pos-0.25f,old_z+z_pos);
    
    /* Collision */
    
    struct   MyContactResultCallback : public btCollisionWorld::ContactResultCallback
    {
        bool m_connected;
        btScalar m_margin;
        MyContactResultCallback() :m_connected(false),m_margin(7.95f)
        {
        }
        virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
        {
            if (cp.getDistance()<=m_margin)
                m_connected = true;
            return 1.f;
        }
    };
    
    vo_2->setPhysicsComponent(10.0f, 10.0f, 10.0f,0.0f,3.0f,0.0f,1.0f,true);
    btRigidBody* body_2 = vo_2->getPhysicsComponent()->getRigidBody();
    
    MyContactResultCallback callback;
    PhysicWorld::getInstance()->dynamicsWorld->contactPairTest(camBody, body_2, callback);
    std::cout<<"WTF: "<<callback.m_connected;
    
    if (callback.m_connected == true){
        Listener* listener = new AnimateRotatingModelMatrixListener(vo_2);
        RenderManager::getInstance()->attachListenerOnNewFrame(listener);
    }
    
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
	// RenderManager::getInstance()->setCurrentFBO( 0 );
}


RenderGraphicsComponentListener::RenderGraphicsComponentListener(GraphicsComponent* gc){
	this->gc = gc;
}

void RenderGraphicsComponentListener::update(){
	if( gc != 0){
		RenderManager::getInstance()->setCurrentGC(gc);
		RenderManager::getInstance()->getCurrentShader()->uploadAllUniforms();
		RenderManager::getInstance()->getCurrentShader()->render(gc);
        RenderManager::getInstance()->getCurrentFBO()->unbindAllTextures();
	}
}

RenderScreenFillingTriangleListener::RenderScreenFillingTriangleListener(){
	this->gc = VirtualObjectFactory::getInstance()->getTriangle();
}

void RenderScreenFillingTriangleListener::update(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	RenderGraphicsComponentListener::update();

    
}


ApplyLinearImpulseOnRigidBody::ApplyLinearImpulseOnRigidBody(btRigidBody* rigidBody, btVector3 force){
	this->rigidBody = rigidBody;
	this->force = force;
}

void ApplyLinearImpulseOnRigidBody::update(){
	rigidBody->applyCentralImpulse(btVector3(force));
}


/*struct   MyContactResultCallback : public btCollisionWorld::ContactResultCallback
{
	bool m_connected;
	MyContactResultCallback() :m_connected(false)
	{
	}
	virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObject* colObj0,int partId0,int index0,const btCollisionObject* colObj1,int partId1,int index1)
	{
		if (cp.getDistance()<=0)
			m_connected = true;
		return 1.f;
	}
};
*/