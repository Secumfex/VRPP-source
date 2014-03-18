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

RenderloopPlaceHolderListener::RenderloopPlaceHolderListener(VirtualObject* water_object){ 
		rm = RenderManager::getInstance(); 
		this->water_object = water_object;
	}

void RenderloopPlaceHolderListener::update(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
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


	shader->uploadUniform(0, "uniformReflectionMap");

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
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void SetClearColorListener::update(){
		glClearColor(r,g,b,a);
}

UnderOrAboveWaterListener::UnderOrAboveWaterListener(Camera* cam, float sea_level_y, Listener* EnterWaterListener, Listener* ExitWaterListener){
	this->cam = cam;
	this->sea_level_y = sea_level_y;
	this->EnterWaterListener = EnterWaterListener;
	this->ExitWaterListener  = ExitWaterListener;
	underwater = false;
}

void UnderOrAboveWaterListener::update(){
	if ( cam->getPosition().y < this->sea_level_y ){
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
	glm::vec3 reflected_camdir = cam_source->getViewDirection();
	reflected_campos.y = 2.0f * *water_height - reflected_campos.y; 
	reflected_camdir.y = -reflected_camdir.y;
	( *cam_target).setPosition(  reflected_campos);
	( *cam_target).setDirection( reflected_camdir); 
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

