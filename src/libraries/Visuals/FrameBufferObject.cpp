/*
 * FrameBufferObject.cpp
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#include "Visuals/FrameBufferObject.h"

FrameBufferObject::FrameBufferObject(int width, int height) {

	glGenFramebuffers(1, &mFramebufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);



	mWidth = width;
	mHeight = height;

	mColorTextureHandle = 0;
	mDepthbufferHandle = 0;
	mNormalTextureHandle = 0;
	mPositionTextureHandle = 0;

	createDepthTexture();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBufferObject::~FrameBufferObject() {
}

void FrameBufferObject::createPositionTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mPositionTextureHandle);
	glBindTexture(GL_TEXTURE_2D, mPositionTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPositionTextureHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT0);

}
void FrameBufferObject::createNormalTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mNormalTextureHandle);
	glBindTexture(GL_TEXTURE_2D, mNormalTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalTextureHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT1);

}
void FrameBufferObject::createColorTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mColorTextureHandle);
	glBindTexture(GL_TEXTURE_2D, mColorTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mColorTextureHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT2);
}
void FrameBufferObject::createShadowMap(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mShadowMapHandle);
	glBindTexture(GL_TEXTURE_2D, mShadowMapHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mShadowMapHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_DEPTH_ATTACHMENT);
}
void FrameBufferObject::createDepthTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenRenderbuffers(1, &mDepthbufferHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, mDepthbufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthbufferHandle);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint FrameBufferObject::getFboHandle(){
	return mFramebufferHandle;
}
GLuint FrameBufferObject::getPositionTextureHandle(){
	return mPositionTextureHandle;
}
GLuint FrameBufferObject::getNormalTextureHandle(){
	return mNormalTextureHandle;
}
GLuint FrameBufferObject::getColorTextureHandle(){
	return mColorTextureHandle;
}
GLuint FrameBufferObject::getShadowMapHandle(){
	return mShadowMapHandle;
}
GLuint FrameBufferObject::getDepthTextureHandle(){
	return mDepthbufferHandle;
}

void FrameBufferObject::bindFBO(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
}
void FrameBufferObject::unbindFBO(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::bindPositionTexture(){
	glBindTexture(GL_TEXTURE_2D, mPositionTextureHandle);
}
void FrameBufferObject::bindNormalTexture(){
	glBindTexture(GL_TEXTURE_2D, mNormalTextureHandle);
}
void FrameBufferObject::bindColorTexture(){
	glBindTexture(GL_TEXTURE_2D, mColorTextureHandle);
}
void FrameBufferObject::bindShadowMap(){
	glBindTexture(GL_TEXTURE_2D, mShadowMapHandle);
}
void FrameBufferObject::bindDepthBuffer(){
	glBindTexture(GL_TEXTURE_2D, mDepthbufferHandle);
}
void FrameBufferObject::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBufferObject::unbindAllTextures(){

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
}

void FrameBufferObject::makeDrawBuffers(){
	glDrawBuffers(mDrawBuffers.size(), &mDrawBuffers[0]);
}

void FrameBufferObject::resize(int width, int height){

//	if(mNormalTextureHandle != 0){
//		bindNormalTexture();
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
//	}
//	if(mColorTextureHandle != 0){
//		bindColorTexture();
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
//	}
//	if(mShadowMapHandle != 0){
//		bindShadowMap();
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
//	}
//	if(mDepthbufferHandle != 0){
//		bindDepthBuffer();
//		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//	}
//	unbindTexture();
}
