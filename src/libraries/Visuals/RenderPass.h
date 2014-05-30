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
	 * @param shader to be used in this render pass
	 * @param fbo to be used as render target in this renderpass ( optional: set 0 or leave out to render to screen )
	 */
	RenderPass(Shader* shader, FrameBufferObject* fbo = 0);

	/** \brief destructor
	 *
	 */
	virtual ~RenderPass();

	/** \brief perform a renderPass with a dynamic set of graphics components and a frame buffer object
	* extracts graphics components from render queue beginning with initial Graphics Component list,
	* then calls the PreRender Listeners, then iterates over all Graphics Components to render
	* per Graphics Component, it is set in RenderManager, then PreUniformUpload Listeners are called,
	* then Shader-Uniforms are uploaded and then PostUniformUpload Listeners are called. 
	* Then the Graphics Component will be rendered by the Shader. 
	* After rendering of all graphics components is complete, PostRender Listeners are called*/
	virtual void render();

	/** \brief upload Uniforms */
	virtual void uploadUniforms();

	/** \brief activate this renderpass 
	* enables the Shader, binds the FBO, sets the Viewport and OpenGL functionality: blending, clearing buffers
	* also sets the Shader and FBO pointers in RenderManager and calls Activation Listeners at the end*/
	virtual void activate();

	/** \brief deactivate this renderpass 
	* disables the FBO, sets the RenderManager FBO and Shader to 0 and re-enables / disables gl functions to default
	* also calls Deactivation Listeners at the end */
	virtual void deactivate();

	/** \brief add a Request Flag to narrow down the list of objects to render */
	void addRenderQueueRequestFlag(RenderQueueRequestFlag* renderQueueRequestFlag);

	/** \brief extract the sub-list of valid graphics components from active render queue which would be rendered
	 *
	 * list of initial graphics components will be narrowed down by active render queue according to provided list of request flags
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
	 * @param customClearColor vec4 color rgba
	 */
	void setCustomClearColor(glm::vec4 customClearColor);

	/** \brief setter
	 *
	 * @param customClearColor vec4 color rgba
	 */
	void setCustomClearColor(glm::vec4* customClearColor);

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

	/** \brief setter
	 *
	 * @param initialGraphicsComponentVector vector of graphics component which will be set as initial Graphics Components list
	 */
	void setInitialGraphicsComponentList(std::vector < GraphicsComponent*> initialGraphicsComponentVector );

	/** \brief add a graphics component as rendering candidate
	 * @param gc graphics component to be added to the initial graphics component list
	 */
	void addInitialGraphicsComponent(GraphicsComponent* gc);

	/** \brief add a Virtual Object as rendering canditate
	 * @param vo virtual object whose graphics components will be added to the initial graphics components list
	 */
	void addInitialGraphicsComponent(VirtualObject* vo);

	/** \brief add a bunch of graphics components as rendering canditates
	 * @param gcs vector of graphics components to be added to the initial graphics component list
	 */
	void addInitialGraphicsComponent(std::vector<GraphicsComponent* > gcs);

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

	float mViewPort_x, mViewPort_y, mViewPort_width, mViewPort_height, mCustomViewPortHeight, mCustomViewPortWidth;

	FrameBufferObject *mFBO;				/**< FrameBufferObject which will be set as render target */
	vector<RenderQueueRequestFlag* > mRenderQueueRequestFlags;	/**< RenderQueueRequestFlags which will be evaluated in order */
	
	std::list<GraphicsComponent* > mInitialGraphicsComponentList; /**< List of graphicsComponents which will be evaluated with the render queue request flags at the beginning of a rendering iteration */
	
	Shader *mShader;						/**< Shader which will be used to render */

	bool clearColorBufferBit;	/**< boolean whether Color Buffer Bit will be cleared at the beginning of a rendering iteration*/
	bool clearDepthBufferBit;	/**< boolean whether Color Buffer Bit will be cleared at the beginning of a rendering iteration*/
	bool useDepthTest;			/**< boolean whether GL_DEPTH_TEST will be enabled */
	bool useAlphaBlending;		/**< boolean whether GL_BLEND will be enabled */


	bool mHasCustomClearColor;		/**< boolean whether this renderpass has a custom clear color or uses the active clear color before */
	glm::vec4* mCustomClearColor;		/**< custom clear color */
};

//TODO
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
/// a Renderpass which is suitable to render into three draw buffers of a FrameBufferObject. Missing DrawBuffers will be created, cannot render into window 
class GBufferRenderPass : public RenderPass{
public:
	/** \brief constructor
	 * @param gbuffer_shader Shader to use for rendering, preferably rendering into draw buffers 
	 * @param gbuffer_fbo FrameBuffer Object to be used as target, missing draw buffers will be created
	 */
	GBufferRenderPass(Shader* gbuffer_shader, FrameBufferObject* gbuffer_fbo);

};

/// a Renderpass which will perform a screen filling polygon render pass and attempts to upload three textures to uniforms named colorMap, positionMap and normalMap and is suitable for G-Buffer style compositing
class CompositingPass : public RenderPass {
public:
	/** \brief constructor
	 * @param gbuffer_compositing_shader a g buffer compositing style shader, i.e. a shader with sampler2d uniforms for positionMap, colorMap and normalMap
	 * @param fbo FrameBufferObject
	 */
	CompositingPass(Shader* gbuffer_compositing_shader, FrameBufferObject* fbo = 0);

	/** \brief destructor
	 *
	 */
	~CompositingPass();

	virtual void uploadUniforms();	/**< upload all maps (color, normal, position) as uniforms */

	GLuint colorMap; 	/**< color map texture handle */
	GLuint positionMap; /**< position map texture handle */
	GLuint normalMap;	/**< normal map texture handle */

	void setColorMap(GLuint colorMap);	/**< set color map handle */
	void setPositionMap(GLuint positionMap); /**< set position map handle */
	void setNormalMap(GLuint normalMap); /**< set normal map handle */

	UploadUniformTextureListener colorMapUploader;	/**< Listener to upload color map */
	UploadUniformTextureListener positionMapUploader; /**< Listener to upload position map */
	UploadUniformTextureListener normalMapUploader; /**< Listener to upload normal map */

	GraphicsComponent* mTriangle;	/**< Screen Filling Triangle to be rendered */
};

/// a Renderpass which will perform a screen filling polygon render pass and upload two textures and is suitable for compositing of two textures, i.e. frames
class MixTexturesRenderPass : public RenderPass {
protected:
	GLuint mBaseTexture;	/**< base texture handle */
	GLuint mMixTexture;     /**< mix texture handle */

	UploadUniformTextureListener mBaseTextureUploader; /**< Listener to upload base texture */
	UploadUniformTextureListener mMixTextureUploader;  /**< Listener to upload mix texture */

	GraphicsComponent* mTriangle; /**< screen filling polygon graphics component */
public:
	virtual void uploadUniforms(); /**< upload all textures ( base, mix ) as uniforms */

	/** \brief constructor
	 *
	 * @param mixShader shader to be used in this render pass, should be of a compositing / post processing / mixing nature of textures
	 * @param fbo to be used as render target in this renderpass ( optional: set 0 or leave out to render to screen )
	 * @param baseTexture handle of one texture
	 * @param mixTexture handle of the other texture
	 */
	MixTexturesRenderPass( Shader* mixShader, FrameBufferObject* fbo = 0, GLuint baseTexture = 0, GLuint mixTexture = 0);

	void setBaseTexture(GLuint baseTexture); /**< set base texture handle*/
	void setMixTexture(GLuint mixTexture); /**< set mix texture handle*/

	void setBaseTextureUniformName(std::string name);	/**< set uniform target name of base texture uploader ( uniform to which base texture will attempt to upload )*/
	void setMixTextureUniformName(std::string name);    /**< set uniform target name of mix texture uploader ( uniform to which mix texture will attempt to upload )*/
};

#endif /* RENDERPASS_H_ */
