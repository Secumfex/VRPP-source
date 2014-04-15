/*
 * RenderPass.h
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#ifndef RENDERPASS_H_
#define RENDERPASS_H_

#include <Visuals/GraphicsComponent.h>
#include <Visuals/RenderQueue.h>
#include <Visuals/Shader.h>
#include <Visuals/FrameBufferObject.h>
#include <Visuals/VirtualObjectFactory.h>
#include <Visuals/RenderQueueRequestFlag.h>

class RenderPass : public Subject{
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
	RenderPass(Shader* shader, FrameBufferObject* fbo = 0);

	/** \brief destructor
	 *
	 */
	virtual ~RenderPass();

	/** \brief !docu pls!
	 *
	 */
	virtual void render();

	virtual void uploadUniforms();

	/** \brief activate this renderpass */
	virtual void activate();

	/** \brief deactivate this renderpass */
	virtual void deactivate();

	/** \brief add a Request Flag to narrow down the list of objects to render */
	void addRenderQueueRequestFlag(RenderQueueRequestFlag* renderQueueRequestFlag);

	/** \brief !docu pls!
	 *
	 * @return vector of graphic components references
	 */
	std::list<GraphicsComponent*> extractGCsFromRenderQueue();

	void setShader(Shader* shader);
	Shader* getShader();
	void setFrameBufferObject(FrameBufferObject* fbo);
	FrameBufferObject* getFrameBufferObject();

	void attachListenerOnPreUniformUpload(Listener* listener);
	void attachListenerOnPostUniformUpload(Listener* listener);
	void attachListenerOnPreRender(Listener* listener);
	void attachListenerOnPostRender(Listener* listener);
	void attachListenerOnActivation(Listener* listener);
	void attachListenerOnDeactivation(Listener* listener);

	void setViewPortX(float x);
	void setViewPortY(float y);
	void setViewPortWidth(float width);
	void setViewPortHeight(float height);
	
	float getViewPortX();
	float getViewPortY();
	float getViewPortWidth();
	float getViewPortHeight();
	
	void setClearColorBufferBit(bool clear);
	void setClearDepthBufferBit(bool clear);

	void setUseDepthTest(bool use);
	void setUseAlphaBlending(bool use);

	void setInitialGraphicsComponentList(std::list < GraphicsComponent* > initialGraphicsComponentList);
	std::list<GraphicsComponent* >* getInitialGraphicsComponentListPointer();
	std::list<GraphicsComponent*>   getInitialGraphicsComponentList();
protected:
	float viewPort_x, viewPort_y, viewPort_width, viewPort_height;

	FrameBufferObject *mFBO;				/**< !docu pls! */
	vector<RenderQueueRequestFlag* > mRenderQueueRequestFlags;	/**< !docu pls! */
	
	std::list<GraphicsComponent* > mInitialGraphicsComponentList;
	
	Shader *mShader;						/**< !docu pls! */

	bool clearColorBufferBit;
	bool clearDepthBufferBit;
	bool useDepthTest;
	bool useAlphaBlending;
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

	/** \brief perform a render iteration
	 *
	 */
	virtual void render();

	virtual void uploadUniforms();	/**< upload all maps (color, normal, position) as uniforms */

	GLuint colorMap; 
	GLuint positionMap; 
	GLuint normalMap;

	void setColorMap(GLuint colorMap);
	void setPositionMap(GLuint positionMap);
	void setNormalMap(GLuint normalMap);

	UploadUniformTextureListener colorMapUploader;
	UploadUniformTextureListener positionMapUploader;
	UploadUniformTextureListener normalMapUploader;

	GraphicsComponent* mTriangle;	/**< Screen Filling Triangle to be rendered */

};
#endif /* RENDERPASS_H_ */
