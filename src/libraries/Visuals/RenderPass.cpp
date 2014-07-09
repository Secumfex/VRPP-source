#include <IO/IOManager.h>
#include <Visuals/RenderManager.h>
#include <Visuals/RenderPass.h>

RenderPass::RenderPass() {
	mFBO = 0;
	mShader = 0;

	clearColorBufferBit = false;
	clearDepthBufferBit = true;
	useDepthTest = true;
	useAlphaBlending = false;

	mViewPort_x = 0;
	mViewPort_y = 0;
	mViewPort_width  = IOManager::getInstance()->getWidth();
	mViewPort_height = IOManager::getInstance()->getHeight();

	mCustomViewPortHeight = 0.0f;
	mCustomViewPortWidth = 0.0f;

	mCustomClearColor = 0;
	mHasCustomClearColor = false;
}

//Variante statt addRenderPass:
RenderPass::RenderPass(Shader* shader, FrameBufferObject* fbo){
	mFBO = fbo;
	mShader = shader;

	clearColorBufferBit = false;
	clearDepthBufferBit = true;
	useDepthTest = true;
	useAlphaBlending = false;

	mViewPort_x = 0;
	mViewPort_y = 0;
	if (mFBO)
	{
		mViewPort_width  = mFBO->getWidth();
		mViewPort_height = mFBO->getHeight();
	}else{
		mViewPort_width = IOManager::getInstance()->getWidth();
		mViewPort_height = IOManager::getInstance()->getHeight();
	}

	mCustomClearColor = 0;
	mHasCustomClearColor = false;


	mCustomViewPortHeight = 0.0f;
	mCustomViewPortWidth = 0.0f;
}

void RenderPass::setCustomClearColor(glm::vec4* customClearColor)
{
	mHasCustomClearColor = true;
	mCustomClearColor = customClearColor;
}


void RenderPass::setCustomClearColor(glm::vec4 customClearColor)
{
	mHasCustomClearColor = true;
	mCustomClearColor = new glm::vec4( customClearColor );
}

void RenderPass::activate()
{

	RenderManager *rm = RenderManager::getInstance();
	rm->setCurrentShader(mShader);
	rm->setCurrentFBO(mFBO);	
	mShader->useProgram();

	if (mFBO)
	{
		mFBO->bindFBO();
		mViewPort_width = mFBO->getWidth();
		mViewPort_height =mFBO->getHeight();
	}
	else {
		mViewPort_width  = IOManager::getInstance()->getWidth();
		mViewPort_height = IOManager::getInstance()->getHeight();
	}

	if (mCustomViewPortHeight != 0.0f)
	{
		mViewPort_height = mCustomViewPortHeight;
	}
	if (mCustomViewPortWidth != 0.0f)
	{
		mViewPort_width = mCustomViewPortWidth;
	}

	glViewport(mViewPort_x, mViewPort_y, mViewPort_width, mViewPort_height);

	if (useDepthTest) 
	{
		glEnable(GL_DEPTH_TEST);
	}else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (useAlphaBlending)
	{
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}else{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	if ( mHasCustomClearColor )
	{
		glClearColor( (*mCustomClearColor).r, (*mCustomClearColor).g, (*mCustomClearColor).b, (*mCustomClearColor).a);
	}
	notify("ACTIVATION");
}


void RenderPass::deactivate()
{
	RenderManager *rm = RenderManager::getInstance();
	rm->setCurrentShader(0);
	rm->setCurrentFBO(0);	
	
	if (mFBO)
	{
		mFBO->unbindFBO();
	}

	if (!useDepthTest) 
	{
		glEnable(GL_DEPTH_TEST);
	}
	if (useAlphaBlending)
	{
		glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	notify("DEACTIVATION");
}

void RenderPass::uploadUniforms()
{
		mShader->uploadAllUniforms();
}

void RenderPass::render(){
	if (clearColorBufferBit)
	{
 		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (clearDepthBufferBit) 
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	RenderManager *rm = RenderManager::getInstance();
	std::list<GraphicsComponent*> renderables = extractGCsFromRenderQueue();
	notify("PRERENDER");

	for(list<GraphicsComponent*>::iterator gc_it = renderables.begin(); gc_it != renderables.end(); ++gc_it){
		GraphicsComponent* myGC = *gc_it;
		rm->setCurrentGC(myGC);
		
		notify("PREUNIFORMUPLOAD");
		uploadUniforms();
		notify("POSTUNIFORMUPLOAD");
	
		mShader->render(myGC);
	}

	notify("POSTRENDER");
}


void RenderPass::addRenderQueueRequestFlag(RenderQueueRequestFlag* renderQueueRequestFlag)
{
	mRenderQueueRequestFlags.push_back(renderQueueRequestFlag);
}


std::list< GraphicsComponent* > RenderPass::extractGCsFromRenderQueue()
{
	RenderQueue* rq = RenderManager::getInstance()->getRenderQueue();
	std::list <GraphicsComponent* > result = mInitialGraphicsComponentList;
	for (unsigned int i = 0; i < mRenderQueueRequestFlags.size(); i++)
	{
		result = mRenderQueueRequestFlags[i]->extrudeGCsRequestFlagList(rq, result);
	}
	return result;
}


void RenderPass::setShader(Shader* shader)
{
	mShader = shader;
}


Shader* RenderPass::getShader()
{
	return mShader;
}


void RenderPass::setFrameBufferObject(FrameBufferObject* fbo)
{
	mFBO = fbo;
	if (mFBO)
	{
		mViewPort_width  = mFBO->getWidth();
		mViewPort_height = mFBO->getHeight();
	}
	else
	{
		mViewPort_width  = IOManager::getInstance()->getWidth();
		mViewPort_height = IOManager::getInstance()->getHeight();
	}
}


FrameBufferObject* RenderPass::getFrameBufferObject()
{
	return mFBO;
}

void RenderPass::setClearColorBufferBit(bool clear)
{
	clearColorBufferBit = clear;
}

void RenderPass::setClearDepthBufferBit(bool clear)
{
	clearDepthBufferBit = clear;
}

void RenderPass::setUseAlphaBlending(bool use)
{
	useAlphaBlending = use;
}

void RenderPass::setUseDepthTest(bool use)
{
	useDepthTest = use;
}

void RenderPass::setViewPortX(float x)
{
	mViewPort_x = x;
}

void RenderPass::setViewPortY(float y)
{
	mViewPort_y = y;
}

void RenderPass::setViewPortWidth(float width)
{

	mCustomViewPortWidth = width;

	mViewPort_width = width;
}

void RenderPass::setViewPortHeight(float height)
{
	mCustomViewPortHeight = height;

	mViewPort_height = height;
}

float RenderPass::getViewPortWidth()
{
	return mViewPort_width;
}

float RenderPass::getViewPortHeight()
{
	return mViewPort_height;
}
float RenderPass::getViewPortX()
{
	return mViewPort_x;
}
float RenderPass::getViewPortY()
{
	return mViewPort_y;
}

std::list < GraphicsComponent* > * RenderPass::getInitialGraphicsComponentListPointer()
{
	return &mInitialGraphicsComponentList;
}

std::list < GraphicsComponent* > RenderPass::getInitialGraphicsComponentList()
{
	return mInitialGraphicsComponentList;
}

void RenderPass::setInitialGraphicsComponentList(std::list<GraphicsComponent*> initialGraphicsComponentList)
{
	mInitialGraphicsComponentList = initialGraphicsComponentList;
}

void RenderPass::setInitialGraphicsComponentList(std::vector < GraphicsComponent*> initialGraphicsComponentVector)
{
	mInitialGraphicsComponentList.clear();
	for (unsigned int i = 0; i < initialGraphicsComponentVector.size(); i++)
	{
		mInitialGraphicsComponentList.push_back(initialGraphicsComponentVector[i]);
	}
}

void RenderPass::setInitialGraphicsComponentList(std::vector < VirtualObject* > initialGraphicsComponentVector)
{
	mInitialGraphicsComponentList.clear();
	for (unsigned int i = 0; i < initialGraphicsComponentVector.size(); i++)
	{
		addInitialGraphicsComponent( initialGraphicsComponentVector[i]);
	}
}

void RenderPass::addInitialGraphicsComponent(GraphicsComponent* gc)
{
	mInitialGraphicsComponentList.push_back(gc);
}

void RenderPass::addInitialGraphicsComponent(VirtualObject* vo)
{
	std::vector < GraphicsComponent* > gcs = vo->getGraphicsComponent();

	addInitialGraphicsComponent(gcs);
}

void RenderPass::addInitialGraphicsComponent(std::vector <GraphicsComponent* > gcs)
{
	for (unsigned int i = 0; i < gcs.size(); i++)
	{
		addInitialGraphicsComponent(gcs[i]);
	}
}

void RenderPass::attachListenerOnPreUniformUpload(Listener* listener)
{
	listener->setName( "PREUNIFORMUPLOAD" );
	attach(listener);
}

void RenderPass::attachListenerOnPostUniformUpload(Listener* listener)
{
	listener->setName( "POSTUNIFORMUPLOAD" );
	attach(listener);
}

void RenderPass::attachListenerOnPreRender(Listener* listener)
{
	listener->setName( "PRERENDER" );
	attach(listener);
}

void RenderPass::attachListenerOnPostRender(Listener* listener)
{
	listener->setName( "POSTRENDER" );
	attach(listener);
}

void RenderPass::attachListenerOnActivation(Listener* listener)
{
	listener->setName( "ACTIVATION" );
	attach(listener);
}

void RenderPass::attachListenerOnDeactivation(Listener* listener)
{
	listener->setName( "DEACTIVATION" );
	attach(listener);
}

RenderPass::~RenderPass() {
	// TODO Auto-generated destructor stub
}

ShadowPass::ShadowPass(){}
ShadowPass::~ShadowPass(){}

GBufferRenderPass::GBufferRenderPass(Shader* gbuffer_shader, FrameBufferObject* gbuffer_fbo)
{
	mFBO = gbuffer_fbo;
	mShader = gbuffer_shader;

	clearColorBufferBit = false;
	clearDepthBufferBit = true;
	useDepthTest = true;
	useAlphaBlending = false;

	mViewPort_x = 0;
	mViewPort_y = 0;
	if (mFBO)
	{
		mViewPort_width  = mFBO->getWidth();
		mViewPort_height = mFBO->getHeight();
	
		// create missing draw buffers
		if (mFBO->getPositionTextureHandle() == -1)
		{
			mFBO->createPositionTexture();
			mFBO->makeDrawBuffers();
		}
		if (mFBO->getNormalTextureHandle() == -1)
		{
			mFBO->createNormalTexture();
			mFBO->makeDrawBuffers();
		}
		if (mFBO->getColorTextureHandle() == -1)
		{
			mFBO->createColorTexture();
			mFBO->makeDrawBuffers();
		}
	}

	mCustomClearColor = 0;
	mHasCustomClearColor = false;

	mCustomViewPortHeight = 0.0f;
	mCustomViewPortWidth = 0.0f;
}

CompositingPass::CompositingPass(Shader* gbuffer_compositing_shader, FrameBufferObject* fbo){
	clearDepthBufferBit = true;
	clearColorBufferBit = true;

	mShader = gbuffer_compositing_shader;
	mFBO = fbo;
	
	mTriangle =	VirtualObjectFactory::getInstance()->getTriangle();

	useDepthTest = false;

	positionMap = 0;
	colorMap = 0;
	normalMap = 0;

	mInitialGraphicsComponentList.push_back( mTriangle );

	colorMapUploader.setTextureUnit(6);
	colorMapUploader.setUniformName("colorMap");
	normalMapUploader.setTextureUnit(5);
	normalMapUploader.setUniformName("normalMap");
	positionMapUploader.setTextureUnit(4);
	positionMapUploader.setUniformName("positionMap");
}

void CompositingPass::uploadUniforms()
{
	RenderPass::uploadUniforms();
	colorMapUploader.update();
	positionMapUploader.update();
	normalMapUploader.update();
}

CompositingPass::~CompositingPass(){

}

void CompositingPass::setColorMap(GLuint colorMap)
{
	this->colorMap = colorMap;
	colorMapUploader.setTextureHandle(colorMap);
}

void CompositingPass::setPositionMap(GLuint positionMap)
{
	this->positionMap = positionMap;
	positionMapUploader.setTextureHandle(positionMap);
}

void CompositingPass::setNormalMap(GLuint normalMap)
{
	this->normalMap = normalMap;
	normalMapUploader.setTextureHandle(normalMap);
}

MixTexturesRenderPass::MixTexturesRenderPass( Shader* mixShader, FrameBufferObject* fbo, GLuint baseTexture, GLuint mixTexture )
{
	mShader = mixShader;
	mFBO = fbo;
	setBaseTexture(baseTexture);
	setMixTexture(mixTexture);

	mTriangle = VirtualObjectFactory::getInstance()->getTriangle();

	useDepthTest = false;

	mInitialGraphicsComponentList.push_back( mTriangle );

	mBaseTextureUploader.setTextureUnit(7);
	mBaseTextureUploader.setUniformName("uniformBaseTexture");
	
	mMixTextureUploader.setTextureUnit(8);
	mMixTextureUploader.setUniformName("uniformMixTexture");
}

void MixTexturesRenderPass::uploadUniforms()
{
	RenderPass::uploadUniforms();
	mBaseTextureUploader.update();
	mMixTextureUploader.update();
}

void MixTexturesRenderPass::setBaseTexture(GLuint baseTexture){
	mBaseTexture = baseTexture;
	mBaseTextureUploader.setTextureHandle(baseTexture);
}

void MixTexturesRenderPass::setMixTexture(GLuint mixTexture){
	mMixTexture = mixTexture;
	mMixTextureUploader.setTextureHandle(mixTexture);
}

void MixTexturesRenderPass::setBaseTextureUniformName( std::string name)
{
	mBaseTextureUploader.setUniformName(name);
}

void MixTexturesRenderPass::setMixTextureUniformName(std::string name)
{
	mMixTextureUploader.setUniformName(name);
}

TextureRenderPass::TextureRenderPass( Shader* textureShader, FrameBufferObject* fbo, GLuint texture )
{
	mShader = textureShader;
	mFBO = fbo;
	setTexture( texture );

	mTriangle = VirtualObjectFactory::getInstance()->getTriangle();

	useDepthTest = false;

	mInitialGraphicsComponentList.push_back( mTriangle );

	mTextureUploader.setTextureUnit(7);
	mTextureUploader.setUniformName("uniformTexture");
}

void TextureRenderPass::uploadUniforms()
{
	RenderPass::uploadUniforms();
	mTextureUploader.update();
}

void TextureRenderPass::setTexture(GLuint baseTexture){
	mTexture = baseTexture;
	mTextureUploader.setTextureHandle(baseTexture);
}

void TextureRenderPass::setTextureUniformName( std::string name)
{
	mTextureUploader.setUniformName(name);
}

RenderPass* ConditionalRenderPassProxy::getRenderPass(){
	return mRenderPass;
}

void ConditionalRenderPassProxy::setRenderPass( RenderPass* renderPass) {
	mRenderPass = renderPass;
}

ConditionalRenderPassProxy::ConditionalRenderPassProxy(RenderPass* renderPass, bool* condition, bool invert) {
	mCondition = condition;
	mRenderPass = renderPass;
	mInvert = invert;
}

void ConditionalRenderPassProxy::activate() {
	if ( (mInvert) ? !*mCondition : *mCondition )
	{
		mRenderPass->activate();
	}
}

void ConditionalRenderPassProxy::render() {
	if ( (mInvert) ? !*mCondition : *mCondition )
	{
		mRenderPass->render();
	}
}

void ConditionalRenderPassProxy::deactivate() {
	if ( (mInvert) ? !*mCondition : *mCondition )
	{
		mRenderPass->deactivate();
	}
}

ScreenFillingTriangleRenderPass::ScreenFillingTriangleRenderPass(Shader* shader, FrameBufferObject* fbo)
  : RenderPass(shader, fbo)
{
	mTriangle = VirtualObjectFactory::getInstance()->getTriangle();

	useDepthTest = false;

	mInitialGraphicsComponentList.push_back( mTriangle );
}

bool RenderPass::getClearColorBufferBit() {
	return clearColorBufferBit;
}
bool RenderPass::getClearDepthBufferBit() {
	return clearColorBufferBit;
}

void RenderPass::removeInitialGraphicsComponent(GraphicsComponent* gc) {
	mInitialGraphicsComponentList.remove(gc);
}

void RenderPass::removeInitialGraphicsComponent(VirtualObject* vo) {
	std::vector <GraphicsComponent* > gcs = vo->getGraphicsComponent();
	for (unsigned int i = 0; i < gcs.size(); i++)
	{
		removeInitialGraphicsComponent(gcs[i]);
	}
}
