/*
 * RenderPass.cpp
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */
#include <IO/IOManager.h>
#include <Visuals/RenderManager.h>
#include <Visuals/RenderPass.h>

RenderPass::RenderPass() {

}

//Variante statt addRenderPass:
RenderPass::RenderPass(Shader* shader, FrameBufferObject* fbo){
	mFBO = fbo;
	mShader = shader;

	clearColorBufferBit = false;
	clearDepthBufferBit = true;
	useDepthTest = true;
	useAlphaBlending = false;

	viewPort_x = 0;
	viewPort_y = 0;
	if (mFBO)
	{
		viewPort_width  = mFBO->getWidth();
		viewPort_height = mFBO->getHeight();
	}else{
		viewPort_width = IOManager::getInstance()->getWidth();
		viewPort_height = IOManager::getInstance()->getHeight();
	}
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
		viewPort_width = mFBO->getWidth();
		viewPort_height =mFBO->getHeight();
	}
	else{
		viewPort_width  = IOManager::getInstance()->getWidth();
		viewPort_height = IOManager::getInstance()->getHeight();
	}

	glViewport(viewPort_x, viewPort_y, viewPort_width, viewPort_height);

	if (clearColorBufferBit)
	{
 		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (clearDepthBufferBit) 
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

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
	viewPort_x = x;
}

void RenderPass::setViewPortY(float y)
{
	viewPort_y = y;
}

void RenderPass::setViewPortWidth(float width)
{
	viewPort_width = width;
}

void RenderPass::setViewPortHeight(float height)
{
	viewPort_height = height;
}

float RenderPass::getViewPortWidth()
{
	return viewPort_width;
}

float RenderPass::getViewPortHeight()
{
	return viewPort_height;
}
float RenderPass::getViewPortX()
{
	return viewPort_x;
}
float RenderPass::getViewPortY()
{
	return viewPort_y;
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

void CompositingPass::uploadUniforms()
{
	RenderPass::uploadUniforms();
	colorMapUploader.update();
	positionMapUploader.update();
	normalMapUploader.update();
	//TODO bind position, normal and color map
}

CompositingPass::CompositingPass(){
	mTriangle =	VirtualObjectFactory::getInstance()->getTriangle();

	clearDepthBufferBit = true;
	clearColorBufferBit = true;

	useDepthTest = false;

	mInitialGraphicsComponentList.push_back( mTriangle );

	colorMapUploader.setTextureUnit(6);
	colorMapUploader.setUniformName("colorMap");
	normalMapUploader.setTextureUnit(5);
	normalMapUploader.setUniformName("normalMap");
	positionMapUploader.setTextureUnit(4);
	positionMapUploader.setUniformName("positionMap");
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
