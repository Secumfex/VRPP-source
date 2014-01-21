/*
 * FrameBufferObject.cpp
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#include "Visuals/FrameBufferObject.h"

FrameBufferObject::FrameBufferObject() {

    glGenFramebuffers(1, &mFramebufferHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);


    mWidth = 800;
    mHeight = 800;

	mColorTextureHandle = 0;
	mDepthbufferHandle = 0;
	mNormalTextureHandle = 0;
	mPositionTextureHandle = 0;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBufferObject::~FrameBufferObject() {
}

void FrameBufferObject:: createPositionTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mPositionTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mPositionTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPositionTextureHandle, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void FrameBufferObject:: createNormalTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mNormalTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mNormalTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalTextureHandle, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FrameBufferObject:: createColorTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenTextures(1, &mColorTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mColorTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mColorTextureHandle, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FrameBufferObject:: createDepthTexture(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);
	glGenRenderbuffers(1, &mDepthbufferHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthbufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, (mHeight/4.0)*3); //800x600
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthbufferHandle);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBufferObject:: getFboHandle(){
	return mFramebufferHandle;
}
GLuint FrameBufferObject:: getPositionTextureHandle(){
	return mPositionTextureHandle;
}
GLuint FrameBufferObject:: getNormalTextureHandle(){
	return mNormalTextureHandle;
}
GLuint FrameBufferObject:: getColorTextureHandle(){
	return mColorTextureHandle;
}
GLuint FrameBufferObject:: getDepthTextureHandle(){
	return mDepthbufferHandle;
}
