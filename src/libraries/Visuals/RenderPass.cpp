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
RenderPass::RenderPass(Shader* shader, FrameBufferObject* fbo, std::vector<GraphicsComponent*> gcVector){
	mFBO = fbo;
	mGcVector = gcVector;
	mShader = shader;
}

//wir KÖNNTEN statt einer addRenderPass Funktion auch einfach den Konstruktor überladen, wie ihr wollt. -Saschalex
void RenderPass::addRenderPass(Shader* shader, FrameBufferObject fbo, std::vector<GraphicsComponent*> gcVector){

	/*
	 * iwo muss auch noch das ViewFrustumCulling hin
	 * dem RenderPass eine priority geben ?!
	 * oder direkt nach dem Aufruf zeichnen ?!
	 */

}

std::vector<GraphicsComponent*> RenderPass::willBeRendered(){

	RenderManager *rm = RenderManager::getInstance();
	Frustum *frustum = rm->getCurrentFrustum();

	std::vector<GraphicsComponent*> toBeRendered;
	unsigned int i = 0;
	for (i = 0; i < mGcVector.size(); ++i) {
		if(frustum->inFrustum(mGcVector[i]))
			toBeRendered.push_back(mGcVector[i]);
	}

	return toBeRendered;
}


void RenderPass::render(){
	RenderManager *rm = RenderManager::getInstance();
	std::vector<GraphicsComponent*> visibleGC = willBeRendered();

	mShader->useProgram();
	rm->setCurrentShader(mShader);

	for(unsigned int i = 0; i < visibleGC.size(); i++){
		GraphicsComponent* myGC = visibleGC[i];
		rm->setCurrentGC(myGC);
		mShader->uploadAllUniforms();
		mShader->render(myGC);
	}
}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

ShadowPass::ShadowPass(){}
ShadowPass::~ShadowPass(){}

CompositingPass::CompositingPass(){
	mTriangle =	VirtualObjectFactory::getInstance()->getTriangle();
}
CompositingPass::~CompositingPass(){}

void CompositingPass::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	mShader->useProgram();
	RenderManager::getInstance()->setCurrentShader(mShader);
	mShader->uploadAllUniforms();
	mShader->render(mTriangle);

}
