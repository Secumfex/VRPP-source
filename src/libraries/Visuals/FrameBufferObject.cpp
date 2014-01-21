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

	mColorTextureHandle = 0;
	mDepthbufferHandle = 0;
	mNormalTextureHandle = 0;
	mPositionTextureHandle = 0;

	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferHandle);

	createTriangle();

}

FrameBufferObject::~FrameBufferObject() {
	// TODO Auto-generated destructor stub
}

void FrameBufferObject:: createTriangle(){

        glGenVertexArrays(1, &screenFillVertexArrayHandle);
        glBindVertexArray(screenFillVertexArrayHandle);

        GLuint vertexBufferHandle;
        glGenBuffers(1, &vertexBufferHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

        //        3 :.
        //          :   .
        //          :      .
        //        1 :_________.
        //          |         |  .
        //          |    +    |     .
        //          |_________|........
        //       -1/-1        1        3

        GLfloat vertices[] = {-1, -1,   3, -1,   -1,  3};
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);

}
