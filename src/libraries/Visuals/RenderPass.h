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

	/** \brief perform a renderPass */
	virtual void render();

	/** \brief upload Uniforms */
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

	/** \brief setter
	 *
	 * @param shader Shader which will be used to render
	 */
	void setShader(Shader* shader);
	Shader* getShader();

	/** \brief setter
	 *
	 * @param fbo FrameBufferObject which will be used as render target
	 */
	void setFrameBufferObject(FrameBufferObject* fbo);


	FrameBufferObject* getFrameBufferObject();

	/** \brief attach listener
	 *
	 * attach Listener before uniforms are uploaded
	 * @param listener
	 */
	void attachListenerOnPreUniformUpload(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener after uniforms are uploaded
	 * @param listener
	 */
	void attachListenerOnPostUniformUpload(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener before GraphicsComponents are rendered, may be used as interface
	 * for UploadUniform Listeners to override or provide additional uniforms
	 * @param listener
	 */
	void attachListenerOnPreRender(Listener* listener);
	/** \brief attach listener
	 *
	 * attach Listener after GraphicsComponents are renderede
	 * @param listener
	 */
	void attachListenerOnPostRender(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on activation
	 * @param listener
	 */
	void attachListenerOnActivation(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on deactivation
	 * @param listener
	 */
	void attachListenerOnDeactivation(Listener* listener);

	/** \brief setter
	 *
	 * @param x coordinate of view port
	 */
	void setViewPortX(float x);

	/** \brief setter
	 *
	 * @param y coordinate of view port
	 */
	void setViewPortY(float y);

	/** \brief setter
	 *
	 * @param width of view port
	 */
	void setViewPortWidth(float width);

	/** \brief setter
	 *
	 * @param height of view port
	 */
	void setViewPortHeight(float height);
	
	/** \brief getter
	 *
	 * @return x coordinate of view port
	 */
	float getViewPortX();

	/** \brief getter
	 *
	 * @return y coordinate of view port
	 */
	float getViewPortY();

	/** \brief getter
	 *
	 * @return width of view port
	 */
	float getViewPortWidth();

	/** \brief getter
	 *
	 * @return height of view port
	 */
	float getViewPortHeight();
	
	/** \brief setter
	 *
	 * @param clear color buffer bit boolean
	 */
	void setClearColorBufferBit(bool clear);

	/** \brief setter
	 *
	 * @param clear depth buffer bit boolean
	 */
	void setClearDepthBufferBit(bool clear);

	/** \brief setter
	 *
	 * @param use boolean of Depth Test
	 */
	void setUseDepthTest(bool use);

	/** \brief setter
	 *
	 * @param use of Alpha Blending
	 */
	void setUseAlphaBlending(bool use);

	/** \brief setter
	 *
	 * @param initialGraphicsComponentList list of graphics components which will be narrowed down by evaluating render queue request flags
	 */
	void setInitialGraphicsComponentList(std::list < GraphicsComponent* > initialGraphicsComponentList);


	/** \brief getter
	 *
	 * @return initialGraphicsComponentList pointer
	 */
	std::list<GraphicsComponent* >* getInitialGraphicsComponentListPointer();


	/** \brief getter
	 *
	 * @return initialGraphicsComponentList
	 */
	std::list<GraphicsComponent*>   getInitialGraphicsComponentList();
protected:
	float viewPort_x, viewPort_y, viewPort_width, viewPort_height;

	FrameBufferObject *mFBO;				/**< FrameBufferObject which will be set as render target */
	vector<RenderQueueRequestFlag* > mRenderQueueRequestFlags;	/**< RenderQueueRequestFlags which will be evaluated in order */
	
	std::list<GraphicsComponent* > mInitialGraphicsComponentList; /**< List of graphicsComponents which will be evaluated with the render queue request flags at the beginning of a rendering iteration */
	
	Shader *mShader;						/**< Shader which will be used to render */

	bool clearColorBufferBit;	/**< boolean whether Color Buffer Bit will be cleared at the beginning of a rendering iteration*/
	bool clearDepthBufferBit;	/**< boolean whether Color Buffer Bit will be cleared at the beginning of a rendering iteration*/
	bool useDepthTest;			/**< boolean whether GL_DEPTH_TEST will be enabled */
	bool useAlphaBlending;		/**> boolean whether GL_BLEND will be enabled */
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
