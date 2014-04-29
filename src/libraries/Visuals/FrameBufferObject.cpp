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

	mColorTextureHandle = -1;
	mDepthbufferHandle = -1;
	mNormalTextureHandle = -1;
	mPositionTextureHandle = -1;

	mShadowMapHandle = -1;
	mSpecularTextureHandle = -1;

	mGuiTextureHandle = -1;


	createDepthBuffer();

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mColorTextureHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT2);
}
void FrameBufferObject::createSpecularTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mSpecularTextureHandle);
	glBindTexture(GL_TEXTURE_2D, mSpecularTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, mSpecularTextureHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT3);
}
void FrameBufferObject::createShadowMap(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mShadowMapHandle);
	glBindTexture(GL_TEXTURE_2D, mShadowMapHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, mShadowMapHandle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mDrawBuffers.push_back(GL_COLOR_ATTACHMENT4);
}
void FrameBufferObject::createDepthBuffer(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);

	glGenTextures(1, &mDepthbufferHandle);
	glBindTexture(GL_TEXTURE_2D, mDepthbufferHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthbufferHandle, 0);

//	glGenRenderbuffers(1, &mDepthbufferHandle);
//	glBindRenderbuffer(GL_RENDERBUFFER, mDepthbufferHandle);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthbufferHandle);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBufferObject::createGuiTexture(){
	glGenTextures(1, &mGuiTextureHandle);
	glBindTexture(GL_RENDERBUFFER, mGuiTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, mGuiTextureHandle, 0);
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
GLuint FrameBufferObject::getSpecularTextureHandle(){
	return mSpecularTextureHandle;
}
GLuint FrameBufferObject::getShadowMapHandle(){
	return mShadowMapHandle;
}
GLuint FrameBufferObject::getDepthBufferHandle(){
	return mDepthbufferHandle;
}
GLuint FrameBufferObject::getGuiTextureHandle(){
	return mGuiTextureHandle;
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
void FrameBufferObject::bindSpecularTexture(){
	glBindTexture(GL_TEXTURE_2D, mSpecularTextureHandle);
}
void FrameBufferObject::bindShadowMap(){
	glBindTexture(GL_TEXTURE_2D, mShadowMapHandle);
}
void FrameBufferObject::bindDepthBuffer(){
	glBindTexture(GL_TEXTURE_2D, mDepthbufferHandle);
}
void FrameBufferObject::bindGuiTexture(){
	glBindTexture(GL_TEXTURE_2D, mGuiTextureHandle);
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

	mWidth = width;
	mHeight = height;

	std:: cout << "resizing to: " << width << " * " << height << std:: endl;

	std::vector <GLuint> texsToBeDeleted;

	if(mPositionTextureHandle != -1){
		texsToBeDeleted.push_back(getPositionTextureHandle());
		createPositionTexture();
	}
	if(mNormalTextureHandle != -1){
		texsToBeDeleted.push_back(getNormalTextureHandle());
		createNormalTexture();
	}
	if(mColorTextureHandle != -1){
		texsToBeDeleted.push_back(getColorTextureHandle());
		createColorTexture();
	}
	if(mShadowMapHandle != -1){
		texsToBeDeleted.push_back(getShadowMapHandle());
		createShadowMap();
	}
	if(mSpecularTextureHandle != -1){
		texsToBeDeleted.push_back(getSpecularTextureHandle());
		createSpecularTexture();
	}

	glDeleteTextures(texsToBeDeleted.size(), &texsToBeDeleted[0]);

	makeDrawBuffers();
}

GLfloat FrameBufferObject::getWidth(){
	return mWidth;
}
GLfloat FrameBufferObject::getHeight(){
	return mHeight;
}
