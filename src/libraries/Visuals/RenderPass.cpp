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
RenderPass::RenderPass(Shader shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector){
	//via Membervariablen? Sonstwie?
}

//wir KÖNNTEN statt einer addRenderPass Funktion auch einfach den Konstruktor überladen, wie ihr wollt. -Saschalex
void RenderPass::addRenderPass(Shader shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector){

	/*
	 * iwo muss auch noch das ViewFrustumCulling hin
	 * dem RenderPass eine priority geben ?!
	 * oder direkt nach dem Aufruf zeichnen ?!
	 */

}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

