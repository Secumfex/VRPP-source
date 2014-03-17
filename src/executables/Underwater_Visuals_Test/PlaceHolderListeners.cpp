#include "PlaceHolderListeners.h"

#include <iostream>

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

