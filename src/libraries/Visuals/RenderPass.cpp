/*
 * RenderPass.cpp
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#include <Visuals/RenderPass.h>

RenderPass::RenderPass() {
	
}

//Variante statt addRenderPass:
RenderPass::RenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector, RenderManager* rm){
	mFBO = fbo;
	mGcVector = gcVector;
	mShader = shader;
	mRenderManager = rm;
}

//wir KÖNNTEN statt einer addRenderPass Funktion auch einfach den Konstruktor überladen, wie ihr wollt. -Saschalex
void RenderPass::addRenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector, RenderManager* rm){

	/*
	 * iwo muss auch noch das ViewFrustumCulling hin
	 * dem RenderPass eine priority geben ?!
	 * oder direkt nach dem Aufruf zeichnen ?!
	 */

}

void RenderPass::render(){
	//sort by distance to camera? sort by transparency?
	for(unsigned int i = 0; i < mGcVector.size(); i++){
		mShader->useProgram();
	}
}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

