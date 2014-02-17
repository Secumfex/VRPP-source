/*
 * RenderLoop.cpp
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"

#include "Visuals/Shader.h"
#include "Visuals/RenderQueue.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/VirtualObjectFactory.h"
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
 * 		Gib an Renderpass alle Objekte für den Shader
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
 *Für transparency: Shader, hast du Uniform isTransparent (o.ä,)
 *über glGetUniformLocation
 *
 */

/*
 * Mögliche Verwendung:
RenderManager::renderloop() called "RENDERLOOP" Listener

RenderLoop-Klasse als Listener Implementiert, beinhaltet Shaderstates und Framebuffer-Objekte

Ein RenderLoop soll also eine "Render-Iteration" zusammenfassen.
Hier steckt mann dann Shaderstates wie Shadowmapping, Gbuffer, Compositing usw rein,
sodass klar definiert ist, in welchen Schritten das Bild gerendert wird.
 *
 *
 *getAllElements für Pass 1 & render while hasNext() render & getNext
 *getAllElements für Pass 2 & render
 *getAllElements für Pass 3 & render

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

vector<GraphicsComponent*> gcVector;

void RenderLoop::fillLoop(){

	//soll den Vektor der Objekte erhalten, die im 1. Pass gerendert werden
	map<string, vector<GraphicsComponent*> > gcShaderStorage = mRenderQueue->getGcShaderStorage();
	vector<GraphicsComponent*> gcVector = gcShaderStorage["pass1"];
	/*for(unsigned int i = 0; i < gcVector.size(); i++){
		//gc.render(); <--- ? wie soll'n das aussehen? Funktion in RenderLoop? Oder in GC? Or wut?
	}*/ //delete soon

}

void RenderLoop::setCurrentRenderQueue(RenderQueue* rq){
	mRenderQueue = rq;
}

RenderLoop::RenderLoop() {
	// TODO Auto-generated constructor stub

}

RenderLoop::~RenderLoop() {
	// TODO Auto-generated destructor stub
}
