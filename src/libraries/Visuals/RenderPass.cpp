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
RenderPass::RenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector){
	mFBO = fbo;
	mGcVector = gcVector;
	mShader = shader;
}

//wir KÖNNTEN statt einer addRenderPass Funktion auch einfach den Konstruktor überladen, wie ihr wollt. -Saschalex
void RenderPass::addRenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector){

	/*
	 * iwo muss auch noch das ViewFrustumCulling hin
	 * dem RenderPass eine priority geben ?!
	 * oder direkt nach dem Aufruf zeichnen ?!
	 */

}

bool RenderPass::inFrustum(glm::vec4 vec_a, glm::vec4 vec_b, glm::vec4 vec_c, glm::vec4 vec_d, glm::vec4 vec_e, glm::vec4 vec_f, glm::vec4 vec_g, glm::vec4 vec_h){

	if((vec_a.x < vec_a.w))

	return true;
}

bool RenderPass::inFrustum(){
	RenderManager *rm = RenderManager::getInstance();
	GraphicsComponent *gc = rm->getCurrentGC();
	glm::mat4 modelMat = rm->getCurrentVO()->getModelMatrix();
	glm::mat4 viewMat = rm->getCamera()->getViewMatrix();
	glm::mat4 projMat = rm->getProjectionMatrix();

	glm::vec3 max = gc->getBoundingBox_Max();
	glm::vec3 min = gc->getBoundingBox_Min();

	glm::vec4 vec_a = glm::vec4(min,1.0);
	glm::vec4 vec_b = glm::vec4(min.x, min.y, max.z ,1.0);
	glm::vec4 vec_c = glm::vec4(min.x, max.y, min.z ,1.0);
	glm::vec4 vec_d = glm::vec4(max.x, min.y, min.z ,1.0);
	glm::vec4 vec_e = glm::vec4(min.x, max.y, max.z ,1.0);
	glm::vec4 vec_f = glm::vec4(max.x, min.y, max.z ,1.0);
	glm::vec4 vec_g = glm::vec4(max.x, max.y, min.z ,1.0);
	glm::vec4 vec_h = glm::vec4(max,1.0);

	vec_a = projMat * viewMat * modelMat * vec_a;
	vec_b = projMat * viewMat * modelMat * vec_b;
	vec_c = projMat * viewMat * modelMat * vec_c;
	vec_d = projMat * viewMat * modelMat * vec_d;
	vec_e = projMat * viewMat * modelMat * vec_e;
	vec_f = projMat * viewMat * modelMat * vec_f;
	vec_g = projMat * viewMat * modelMat * vec_g;
	vec_h = projMat * viewMat * modelMat * vec_h;

	bool inside = 		(-vec_a.w < vec_a.x < vec_a.w) ||
			(-vec_b.w < vec_b.x < vec_b.w) ||
			(-vec_c.w < vec_c.x < vec_c.w) ||
			(-vec_d.w < vec_d.x < vec_d.w) ||
			(-vec_e.w < vec_e.x < vec_e.w) ||
			(-vec_f.w < vec_f.x < vec_f.w) ||
			(-vec_g.w < vec_g.x < vec_g.w) ||
			(-vec_h.w < vec_h.x < vec_h.w);
	if(!inside)
		return inFrustum(vec_a, vec_b, vec_c, vec_d, vec_e, vec_f, vec_g, vec_h);
	else return true;
}

void RenderPass::calcViewFrustum(){
}

void RenderPass::render(){
	mShader->useProgram();
	calcViewFrustum();
	RenderManager *rm = RenderManager::getInstance();
	rm->setCurrentShader(mShader);
	for(unsigned int i = 0; i < mGcVector.size(); i++){
		GraphicsComponent* myGC = mGcVector[i];
		rm->setCurrentGC(myGC);
		if(inFrustum()){

		}

	}
}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

