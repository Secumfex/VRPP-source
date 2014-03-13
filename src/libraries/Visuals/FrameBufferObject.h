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
	/** \brief constructor
	 *
	 * @param width,height
	 */
	FrameBufferObject(int width=800, int height=800);

	/** \brief destructor
	 *
	 */
	virtual ~FrameBufferObject();

	/** \brief creates a positionmap for a color attachment to write in
	 *
	 */
	void createPositionTexture();

	/** \brief creates a normalmap for a color attachment to write in
	 *
	 */
	void createNormalTexture();

	/** \brief creates a colormap for a color attachment to write in
	 *
	 */
	void createColorTexture();

	/** \brief creates a specularmap for a color attachment to write in
	 *
	 */
	void createSpecularTexture();

	/** \brief creates a shadowmap for a color attachment to write in
	 *
	 */
	void createShadowMap();

	/** \brief creates a depthbuffer for this fbo
	 *
	 */
	void createDepthBuffer();

	/** \brief getter
	 *
	 * @return FBO handle
	 */
	GLuint getFboHandle();

	/** \brief getter
	 *
	 * @return position texture handle
	 */
	GLuint getPositionTextureHandle();

	/** \brief getter
	 *
	 * @return normal texture handle
	 */
	GLuint getNormalTextureHandle();

	/** \brief getter
	 *
	 * @return color texture handle
	 */
	GLuint getColorTextureHandle();

	/** \brief getter
	 *
	 * @return specular texture handle
	 */
	GLuint getSpecularTextureHandle();

	/** \brief getter
	 *
	 * @return shadow texture handle
	 */
	GLuint getShadowMapHandle();

	/** \brief getter
	 *
	 * @return depth buffer handle
	 */
	GLuint getDepthBufferHandle();

	/** \brief binds this fbo
	 *
	 */
	void bindFBO();

	/** \brief unbinds this fbo
	 *
	 */
	void unbindFBO();

	/** \brief binds position map of this fbo
	 *
	 */
	void bindPositionTexture();

	/** \brief binds normal map of this fbo
	 *
	 */
	void bindNormalTexture();

	/** \brief binds color map of this fbo
	 *
	 */
	void bindColorTexture();

	/** \brief binds specular map of this fbo
	 *
	 */
	void bindSpecularTexture();

	/** \brief binds shadow map of this fbo
	 *
	 */
	void bindShadowMap();

	/** \brief binds depthbuffer of this fbo
	 *
	 */
	void bindDepthBuffer();

	/** \brief unbinds texture from current active texture
	 *
	 */
	void unbindTexture();

	/** \brief undbinds all textures from all active textures of this fbo
	 *
	 */
	void unbindAllTextures();

	/** \brief makes draw buffers for shaders to draw into our textures
	 *
	 */
	void makeDrawBuffers();

	/** \brief resizes the resolution of our fbo
	 *
	 */
	void resize(int width, int height);

	/** \brief getter
	 *
	 * @return the width
	 */
	GLfloat getWidth();

	/** \brief getter
	 *
	 * @return the height
	 */
	GLfloat getHeight();


protected:

	int mHeight, mWidth;				/**< !docu pls! */

    GLuint mFramebufferHandle;			/**< !docu pls! */

    GLuint mPositionTextureHandle;		/**< !docu pls! */
    GLuint mNormalTextureHandle;		/**< !docu pls! */
    GLuint mColorTextureHandle;			/**< !docu pls! */
    GLuint mSpecularTextureHandle;		/**< !docu pls! */
    GLuint mShadowMapHandle;			/**< !docu pls! */
    GLuint mDepthbufferHandle;			/**< !docu pls! */

    std::vector <GLenum> mDrawBuffers;	/**< !docu pls! */

};

#endif /* FRAMEBUFFEROBJECT_H_ */
