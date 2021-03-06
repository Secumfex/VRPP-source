/*
 * RenderLoop.cpp
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#include "Visuals/RenderLoop.h"

/*RenderLoop:
 *
 * 1) aktiviere renderstate
 * 2) setRenderStateCurrent
 * 3) UploadUniform
 * 4) render
 *
 * --->aktiviere GBuffer
 * 		Mache GBuffer als Current Renderstate
 * 		Erstelle neuen RenderPass *
 * 		Gib an Renderpass alle Objekte f�r den Shader
 * 		Gib an Renderpass alle Uniforma Variablen
 *
 * 		--> Check dazu Raphis GBuffer (
 * 			gbuffer_normalMap_Shader->useProgram();
 * 			rm->setCurrentShader(gbuffer_normalMap_Shader();
 *
 * 			for(j=0; j< vo_temp  -> getGraphicsComponent().size(); ++j{
 * 				GraphicsComponent *gc_temp = vo_temp->getGraphicsComponent()[j];
 * 				rm->setCurrentGC(gc_temp);
 *
 * 				gbuffer_normalMap_Shader->uploadAllUniforms();
 *
 * 				gbufferShader->render(gc_temp);
 *
 *
 *F�r transparency: Shader, hast du Uniform isTransparent (o.�,)
 *�ber glGetUniformLocation
 *
 */

/*
 * M�gliche Verwendung:
RenderManager::renderloop() called "RENDERLOOP" Listener

RenderLoop-Klasse als Listener Implementiert, beinhaltet Shaderstates und Framebuffer-Objekte

Ein RenderLoop soll also eine "Render-Iteration" zusammenfassen.
Hier steckt mann dann Shaderstates wie Shadowmapping, Gbuffer, Compositing usw rein,
sodass klar definiert ist, in welchen Schritten das Bild gerendert wird.
 *
 *
 *getAllElements f�r Pass 1 & render while hasNext() render & getNext
 *getAllElements f�r Pass 2 & render
 *getAllElements f�r Pass 3 & render

 *
 * start:
 * FBO binden -> currentShader=gBufferShader; --> aka.GBuffer Renderpass
 * currentFBO = gBufferFBO
 *
 * while( currentGC.hasNextGC()){
 * currentGC=netxGC();
 * currentVO = rq -> getVO(currentGC)
 * currentShader ->uploadAllUniforms()
 * currentShader->render(currentGC)
 * }
 * "COMPOSITING" shaderstate (FBO unbinden)
 * Rendern
 *
 *
 * GBuffer:
 *  render window
 *  load, compile & link Shaders
 *  Create VAO to render a ScreenFillingTriangle
 *  Create VAO containing several Buffers to render a cube
 *  Create FBO
 *  Render Scene into FBO
 *  Take Texture from the FBO to compose them on an image plane
 *  Render small views (glViewPort - glBindTexture - glDrawArrays
 *
 *Renderloop -> create RenderPass (shader,FBO,list<GC>)
	RenderPass1-3
		render();

	RenderPass1(GBUFFER)
		Shader GBUFFER
		FBO: colorMap, NormalMap, BlaMap
		list<GC> rq->getAllGCs()
	RenderPass2(Compositing)
		Shader Compositing
		FBO: 800x600 FBO
		listGC 3eck
	RenderPass3(ShowResult)
		Shader ShowResult
		FBO: NULL / 0
		listCG 3eck
 */

void RenderLoop::render()
{
	for (unsigned int i = 0; i < mRenderPasses.size(); i++)
	{
		mRenderPasses[i]->activate();
		mRenderPasses[i]->render();
		mRenderPasses[i]->deactivate();
	}
}

void RenderLoop::addRenderPass(RenderPass* renderPass)
{
	mRenderPasses.push_back(renderPass);
}


RenderLoop::RenderLoop() {
	// TODO Auto-generated constructor stub
}

RenderLoop::~RenderLoop() {
	// TODO Auto-generated destructor stub
}

bool RenderLoop::addRenderPassBefore(RenderPass* addRenderPass,
		RenderPass* beforeRenderPass) {
	// iterate over vector
	for (std::vector<RenderPass*>::iterator it = mRenderPasses.begin(); it != mRenderPasses.end(); ++it)
	{
		if ( *it == beforeRenderPass)	// found renderPass
		{
			mRenderPasses.insert(it, addRenderPass);
			return true;
		}
	}
	return false;
}

bool RenderLoop::addRenderPassAfter(RenderPass* addRenderPass,
		RenderPass* afterRenderPass) {

	// iterate over vector
	for (std::vector<RenderPass*>::iterator it = mRenderPasses.begin(); it != mRenderPasses.end(); ++it)
	{
		if ( *it == afterRenderPass)	// found renderPass
		{
			++it;
			mRenderPasses.insert(it, addRenderPass);
			return true;
		}
	}
	return false;
}

std::vector<RenderPass*> RenderLoop::getRenderPasses() {
	return mRenderPasses;
}
