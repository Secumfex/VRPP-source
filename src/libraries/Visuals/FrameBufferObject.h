/*
 * FrameBufferObject.h
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBUFFEROBJECT_H_

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBufferObject {
public:
	FrameBufferObject(int width=800, int height=800);
	virtual ~FrameBufferObject();

	void createPositionTexture();//creates a positionmap for a color attachment to write in
	void createNormalTexture();//creates a normalmap for a color attachment to write in
	void createColorTexture();//creates a colormap for a color attachment to write in
	void createSpecularTexture();//creates a specularmap for a color attachment to write in
	void createShadowMap();//creates a shadowmap for a color attachment to write in

	void createDepthBuffer();//creates a depthbuffer for this fbo

	GLuint getFboHandle();//returns FBO handle
	GLuint getPositionTextureHandle();//returns position texture handle
	GLuint getNormalTextureHandle();//returns normal texture handle
	GLuint getColorTextureHandle();//returns color texture handle
	GLuint getSpecularTextureHandle();//returns specular texture handle
	GLuint getShadowMapHandle();//returns shadow texture handle
	GLuint getDepthBufferHandle();//returns depth buffer handle


	void bindFBO();//binds this fbo
	void unbindFBO();//unbinds this fbo
	void bindPositionTexture();//binds position map of this fbo
	void bindNormalTexture();//binds normal map of this fbo
	void bindColorTexture();//binds color map of this fbo
	void bindSpecularTexture();//binds specular map of this fbo
	void bindShadowMap();//binds shadow map of this fbo
	void bindDepthBuffer();//binds depthbuffer of this fbo
	void unbindTexture();//unbinds texture from current active texture
	void unbindAllTextures();//undbinds all textures from all active textures of this fbo
	void makeDrawBuffers();//makes draw buffers for shaders to draw into our textures
	void resize(int width, int height);//resizes the resolution of our fbo

	GLfloat getWidth();//returns the width
	GLfloat getHeight();//returns the height


protected:

	int mHeight, mWidth;

    GLuint mFramebufferHandle;

    GLuint mPositionTextureHandle;
    GLuint mNormalTextureHandle;
    GLuint mColorTextureHandle;
    GLuint mSpecularTextureHandle;
    GLuint mShadowMapHandle;
    GLuint mDepthbufferHandle;

    std::vector <GLenum> mDrawBuffers;

};

#endif /* FRAMEBUFFEROBJECT_H_ */
