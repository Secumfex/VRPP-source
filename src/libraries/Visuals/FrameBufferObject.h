/*
 * FrameBufferObject.h
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBUFFEROBJECT_H_

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBufferObject {
public:
	FrameBufferObject();
	virtual ~FrameBufferObject();

	void createPositionTexture();
	void createNormalTexture();
	void createColorTexture();
	void createShadowMap();
	void createDepthTexture();

	GLuint getFboHandle();
	GLuint getPositionTextureHandle();
	GLuint getNormalTextureHandle();
	GLuint getColorTextureHandle();
	GLuint getShadowMapHandle();
	GLuint getDepthTextureHandle();


	void bindFBO();
	void unbindFBO();
	void bindPositionTexture();
	void bindNormalTexture();
	void bindColorTexture();
	void bindDepthTexture();
	void unbindTexture();
	void unbindAllTextures();
	void makeDrawBuffers();


protected:

	int mHeight, mWidth;

    GLuint mFramebufferHandle;

    GLuint mPositionTextureHandle;
    GLuint mNormalTextureHandle;
    GLuint mColorTextureHandle;
    GLuint mShadowMapHandle;
    GLuint mDepthbufferHandle;

    std::vector <GLenum> mDrawBuffers;

};

#endif /* FRAMEBUFFEROBJECT_H_ */
