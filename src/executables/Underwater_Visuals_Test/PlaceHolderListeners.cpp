#include "PlaceHolderListeners.h"

#include <iostream>

ReflectionMapRenderPass::ReflectionMapRenderPass(FrameBufferObject* fbo, Camera* reflectedCamera, VirtualObject* water_object){ 
		rm = RenderManager::getInstance(); 
		this->fbo = fbo;
		this->reflectedCamera = reflectedCamera;
		this->water_object = water_object;
	}

void ReflectionMapRenderPass::update(){
		/***************** save old state ******************/
        Camera* tempCamera = rm->getCamera();
        FrameBufferObject* tempFBO = rm->getCurrentFBO();

        /***************** set shader state and get ready to draw ***************/
        fbo->bindFBO();	// From now on, everything will be written into ColorAttachment0

        rm->setCamera(reflectedCamera);
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
				if((*i) == water_object){	// Render anything exept for water
					continue;
				}
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
        rm->setCamera(tempCamera);
        rm->setCurrentFBO(tempFBO);

	}

RefractionMapRenderPass::RefractionMapRenderPass(FrameBufferObject* fbo, VirtualObject* water_object){ 
		rm = RenderManager::getInstance(); 
		this->fbo = fbo;
		this->water_object = water_object;
	}

void RefractionMapRenderPass::update(){
		/***************** save old state ******************/
        Camera* tempCamera = rm->getCamera();
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
				if((*i) == water_object){	// Render anything exept for water
					continue;
				}
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
        rm->setCamera(tempCamera);
        rm->setCurrentFBO(tempFBO);

	}

GodRaysRenderPass::GodRaysRenderPass(FrameBufferObject* fbo){ 
		rm = RenderManager::getInstance(); 
		this->fbo = fbo;
	}

void GodRaysRenderPass::update(){
		fbo->bindFBO();
		
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0,0.0,0.0,1.0);
    	
    	glViewport(0, 0, fbo->getWidth(), fbo->getHeight());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentShader = rm->getCurrentShader();
		
		//get renderQueue	
		currentRenderQueue = rm->getRenderQueue(); 

		//render GCs with current Shader 
		if ( currentRenderQueue != 0 ){
			voList = currentRenderQueue->getVirtualObjectList();	//get List of all VOs in RenderQueue
			//for every VO
			for (std::list<VirtualObject* >::iterator i = voList.begin(); i != voList.end(); ++i) {	
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
		fbo->unbindFBO();	
	}


// ParticlesRenderPass::ParticlesRenderPass(FrameBufferObject* fbo, ParticleSystem* particleSystem, GLint vao){
// 		rm = RenderManager::getInstance();
// 		this->fbo = fbo;
// 		this->particleSystem = particleSystem;
// 	//	this->particleGC = particleGC;
// 		this->vao = vao;
// }

// void ParticlesRenderPass::update(){

// 	/***************** save old state ******************/
// 		FrameBufferObject* tempFBO = rm->getCurrentFBO();

// 		fbo->bindFBO();
// 		rm->setCurrentFBO(fbo);
// 		Shader* currentShader;
//         glDisable(GL_DEPTH_TEST);
//         glEnable(GL_BLEND);
//         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//         glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//     	glViewport(0, 0, fbo->getWidth(), fbo->getHeight());
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 		currentShader = rm->getCurrentShader();

//    /*****************render object************************/
// 		rm->setCurrentGC(particleGC);
// 		vector <Particle* > particles = particleSystem->getParticles();
// 		for (unsigned int i = 0; i < particles.size(); i++) {
// //			std::cout << "particle " << i << " position : " << particles[i]->getPosition().x << ", " << particles[i]->getPosition().y << ", " << particles[i]->getPosition().z << std::endl;
// //			currentShader->uploadAllUniforms();
// 			currentShader->uploadUniform(glm::translate(  glm::mat4(1.0f), particles[i]->getPosition()),	"uniformModel");
// 			currentShader->uploadUniform(rm->getCamera()->getViewMatrix(), 	"uniformView");;
// 			currentShader->uploadUniform(rm->getPerspectiveMatrix(), 		"uniformPerspective");
// 			currentShader->uploadUniform(1.0f, "uniformScale");

// 			currentShader->uploadUniform(particles[i]->getPosition(), "uniformParticlePosition");

// 			glBindVertexArray(vao); // Bind our Vertex Array Object

// 			glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square

// 			glBindVertexArray(0); // Unbind our Vertex Array Object

// //			currentShader->render(particleGC);
// 		}


	// /****************** back to old state *****************/
	// 	glDisable(GL_BLEND);
	// 	glEnable(GL_DEPTH_TEST);
	// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// 	fbo->unbindFBO();
	// 	rm->setCurrentFBO(tempFBO);
	// 	glViewport(0,0, 800, 600);
	// }


RenderloopPlaceHolderListener::RenderloopPlaceHolderListener(VirtualObject* water_object){ 
		rm = RenderManager::getInstance(); 
		this->water_object = water_object;
	}

void RenderloopPlaceHolderListener::update(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, 800, 600);

		currentShader = rm->getCurrentShader();

		
		//get renderQueue	
		currentRenderQueue = rm->getRenderQueue(); 

		//render GCs with current Shader 
		if ( currentRenderQueue != 0 ){
			voList = currentRenderQueue->getVirtualObjectList();	//get List of all VOs in RenderQueue
			//for every VO
			for (std::list<VirtualObject* >::iterator i = voList.begin(); i != voList.end(); ++i) {	//get GCs of VO
				if((*i) == water_object){
					continue;	//Water surface is supposed to be rendered differently
				}
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

RenderWaterObjectWithShaderAndReflectionMapListener::RenderWaterObjectWithShaderAndReflectionMapListener(VirtualObject* vo, Shader* shader, FrameBufferObject* fbo){
	this->shader = shader;
	this->vo = vo;
	this->fbo = fbo;
}

void RenderWaterObjectWithShaderAndReflectionMapListener::update(){	
	/***************** save old state ******************/
    Shader* temp_shader 		= RenderManager::getInstance()->getCurrentShader();
    FrameBufferObject* temp_fbo = RenderManager::getInstance()->getCurrentFBO();
  	RenderManager::getInstance()->setCurrentShader(shader);
  	RenderManager::getInstance()->setCurrentFBO(fbo);
    
    shader->useProgram();

    /*****************render object************************/

	std::vector<GraphicsComponent* > gcs = vo->getGraphicsComponent();

	for (unsigned int j = 0; j < gcs.size(); j++){
		RenderManager::getInstance()->setCurrentGC(gcs[j]);
		shader->uploadAllUniforms();
		shader->render(gcs[j]);
	}

	/****************** back to old state *****************/
	fbo->unbindTexture();
  	RenderManager::getInstance()->setCurrentFBO(temp_fbo);
	RenderManager::getInstance()->setCurrentShader(temp_shader);
    RenderManager::getInstance()->getCurrentShader()->useProgram();
}

SetCurrentShaderListener::SetCurrentShaderListener(Shader* shader){
	rm = RenderManager::getInstance();
	this->shader = shader;}

void SetCurrentShaderListener::update(){
	rm->setCurrentShader(shader);
	shader->useProgram();
}	


SetClearColorListener::SetClearColorListener(float r, float g, float b, float a){
	this->clearColorVec3 = new glm::vec3(r,g,b);
	this->clearColorVec4 = 0;
	this->a = a;
}

SetClearColorListener::SetClearColorListener(glm::vec3* clearColor, float a){
	this->clearColorVec3 = clearColor;
	this->clearColorVec4 = 0;
	this->a = a;
}

SetClearColorListener::SetClearColorListener(glm::vec4* clearColor){
	this->clearColorVec4 = clearColor;
	this->clearColorVec3 = 0;
	this->a = a;
}

void SetClearColorListener::update(){
	if (clearColorVec4 == 0){
		glClearColor(clearColorVec3->x,clearColorVec3->y,clearColorVec3->z, a);
	}else{
		glClearColor(clearColorVec4->r, clearColorVec4->g, clearColorVec4->b, clearColorVec4->a);
	}
}


UnderOrAboveWaterListener::UnderOrAboveWaterListener(Camera* cam, float* sea_level_y, Listener* EnterWaterListener, Listener* ExitWaterListener){
	this->cam = cam;
	this->sea_level_y = sea_level_y;
	this->EnterWaterListener = EnterWaterListener;
	this->ExitWaterListener  = ExitWaterListener;
	underwater = false;
}

void UnderOrAboveWaterListener::update(){
	if ( cam->getPosition().y < *(this->sea_level_y) ){
		if (!underwater){
			if (EnterWaterListener != 0){
				EnterWaterListener->update(); 
			}
			underwater = true;
		}
	}
	else{
		if (underwater){
			if (ExitWaterListener != 0){
				ExitWaterListener->update();
			}
			underwater = false;
		}
	}
}

RecompileAndSetShaderListener::RecompileAndSetShaderListener(std::string vertex_shader, std::string fragment_shader){
	this->vertex_shader = vertex_shader;
	this->fragment_shader = fragment_shader;
}

void RecompileAndSetShaderListener::update(){
	Shader* shader = new Shader ( vertex_shader, fragment_shader);

	RenderManager::getInstance()->setCurrentShader(shader);
	shader->useProgram();
}

UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float* water_height){
	this->water_height = water_height;
	this->cam_source = cam;
	this->cam_target = cam_target;
}

UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float water_height){
	this->water_height = new float(water_height);
	this->cam_source = cam;
	this->cam_target = cam_target;
}

void UpdateReflectedCameraPositionListener::update(){
	glm::vec3 reflected_campos = cam_source->getPosition();
	glm::vec3 reflected_center = cam_source->getPosition() + cam_source->getViewDirection();
	reflected_campos.y = 2.0f * *water_height - reflected_campos.y; 
	reflected_center.y = 2.0f * *water_height - reflected_center.y;
	( *cam_target).setPosition(  reflected_campos);
	( *cam_target).setCenter(    reflected_center); 
}

RenderVirtualObjectWithShaderListener::RenderVirtualObjectWithShaderListener(VirtualObject* vo, Shader* shader){
	this->shader = shader;
	this->vo = vo;
}

void RenderVirtualObjectWithShaderListener::update(){	
	std::vector<GraphicsComponent* > gcs = vo->getGraphicsComponent();
	
	for (unsigned int j = 0; j < gcs.size(); j++){
		RenderManager::getInstance()->setCurrentGC(gcs[j]);
		shader->uploadAllUniforms();
		shader->render(gcs[j]);
	}
}

UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(std::string name, float* t, float frequency, float phase, std::string uniform_name){
	this->t = t;
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(std::string name, float t, float frequency, float phase, std::string uniform_name){
	this->t = new float(t);
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

void UploadUniformSinusWaveListener::update(){
	float sinus = std::sin( (*t) * frequency + phase ) ;

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform(sinus, uniform_name);
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

SetCameraListener::SetCameraListener(Camera* cam){
	this->cam = cam;
}

void SetCameraListener::update(){
	RenderManager::getInstance()->setCamera(cam);
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


UpdateParticleSystemListener::UpdateParticleSystemListener(ParticleSystem* particleSystem, float* t){
	this->particleSystem = particleSystem;
	this->t = t;
}

void UpdateParticleSystemListener::update(){
	particleSystem->update(*t);
}

KeepOffsetListener::KeepOffsetListener(VirtualObject* vo, glm::vec3* target,
		glm::vec3* offset) {

	this->vo = vo;
	this->target = target;
	this->offset = offset;

	if (!offset)
	{
		offset = new glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void KeepOffsetListener::update() {
	glm::vec3 targetPosition = *target + *offset;
	vo->getPhysicsComponent()->setPosition(targetPosition.x, targetPosition.y, targetPosition.z);
	vo->updateModelMatrixViaPhysics();
}
