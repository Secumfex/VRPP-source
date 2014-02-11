/*
 * RenderPass.cpp
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#include <Visuals/GraphicsComponent.h>
#include <Visuals/RenderPass.h>
#include <Visuals/RenderQueue.h>
#include <Visuals/Shader.h>

RenderPass::RenderPass() {

	}

void RenderPass::addRenderPass(Shader shader, FrameBufferObject fbo, list<GraphicsComponent> gcList){

	/*
	 * iwo muss auch noch das ViewFrustumCulling hin
	 * dem RenderPass eine priority geben ?!
	 * oder direkt nach dem Aufruf zeichnen ?!
	 */

}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

