/*
 * FrameBufferObject.h
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBUFFEROBJECT_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBufferObject {
public:
	FrameBufferObject();
	virtual ~FrameBufferObject();


private:
	void createTriangle();

	int mHeight, mWidth;

    GLuint mFramebufferHandle;

    GLuint screenFillVertexArrayHandle;

    GLuint mPositionTextureHandle;
    GLuint mNormalTextureHandle;
    GLuint mColorTextureHandle;
    GLuint mDepthbufferHandle;


};

#endif /* FRAMEBUFFEROBJECT_H_ */
