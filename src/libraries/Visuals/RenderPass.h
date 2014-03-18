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
#include <Visuals/VirtualObjectFactory.h>

class RenderPass {
public:
	/** \brief default constructor
	 *
	 */
	RenderPass();

	/** \brief constructor
	 *
	 * @param shader
	 * @param fbo
	 * @param gcVector
	 */
	RenderPass(Shader* shader, FrameBufferObject* fbo, vector<GraphicsComponent*> gcVector);

	/** \brief destructor
	 *
	 */
	virtual ~RenderPass();

	/** \brief !docu pls!
	 *
	 * @param shader
	 * @param fbo
	 * @param gcVector
	 */
	void addRenderPass(Shader* shader, FrameBufferObject fbo, vector<GraphicsComponent*> gcVector);

	/** \brief !docu pls!
	 *
	 */
	virtual void render();

	/** \brief !docu pls!
	 *
	 * @return vector of graphic components references
	 */
	std::vector<GraphicsComponent*> willBeRendered();

protected:

	FrameBufferObject *mFBO;				/**< !docu pls! */
	vector<GraphicsComponent*> mGcVector;	/**< !docu pls! */
	Shader *mShader;						/**< !docu pls! */
};
class ShadowPass : public RenderPass {
public:
	/** \brief constructor
	 *
	 */
	ShadowPass();

	/** \brief destructor
	 *
	 */
	~ShadowPass();

	/** \brief !docu pls!
	 *
	 */
	void render();
};

class CompositingPass : public RenderPass {
public:
	/** \brief constructor
	 *
	 */
	CompositingPass();

	/** \brief destructor
	 *
	 */
	~CompositingPass();

	/** \brief !docu pls!
	 *
	 */
	void render();

	GraphicsComponent* mTriangle;	/**< !docu pls! */

};
#endif /* RENDERPASS_H_ */
