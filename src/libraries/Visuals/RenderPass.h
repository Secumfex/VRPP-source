/*
 * RenderPass.h
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#ifndef RENDERPASS_H_
#define RENDERPASS_H_

#include <Visuals/GraphicsComponent.h>
#include <Visuals/RenderPass.h>
#include <Visuals/RenderQueue.h>
#include <Visuals/Shader.h>
#include <Visuals/FrameBufferObject.h>

class RenderPass {
public:
	RenderPass();
	RenderPass(Shader shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector);
	virtual ~RenderPass();
	void addRenderPass(Shader shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector);
};

#endif /* RENDERPASS_H_ */
