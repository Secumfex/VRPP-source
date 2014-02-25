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
#include <Visuals/RenderLoop.h>
#include <Visuals/Shader.h>
#include <Visuals/FrameBufferObject.h>

class RenderPass {
public:
	RenderPass();
	RenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector);
	virtual ~RenderPass();
	void addRenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector);
	void render();
	bool inFrustum();
	bool inFrustum(glm::vec4 vec_a, glm::vec4 vec_b, glm::vec4 vec_c, glm::vec4 vec_d, glm::vec4 vec_e, glm::vec4 vec_f, glm::vec4 vec_g, glm::vec4 vec_h);
	void calcViewFrustum();
private:

	FrameBufferObject mFBO;
	vector<GraphicsComponent*> mGcVector;
	Shader *mShader;
};

#endif /* RENDERPASS_H_ */
