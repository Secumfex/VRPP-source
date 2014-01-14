/*
 * DeferredShader.cpp
 *
 *  Created on: 13.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/DeferredShader.h>

DeferredShader::DeferredShader(Shader* screenFill, Shader* gBuffer, Shader* finalCompositing) {
	mSimpleTexture = screenFill;
	mGBuffer = gBuffer;
	mFinalCompositing = finalCompositing;

    positionMapHandle = glGetUniformLocation(mFinalCompositing->getProgramHandle(), "positionMap");
    colorMapHandle = glGetUniformLocation(mFinalCompositing->getProgramHandle(), "colorMap");
    normalMapHandle = glGetUniformLocation(mFinalCompositing->getProgramHandle(), "normalMap");
    blurStrengthHandle = glGetUniformLocation(mFinalCompositing->getProgramHandle(), "blurStrength");


}

DeferredShader::~DeferredShader() {
}

void DeferredShader::setFormat(int width, int height){
	mWidth = width;
	mHeight = height;
    createBuffers();
}

void DeferredShader::createBuffers(){
    glGenFramebuffers(1, &framebufferHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);

    //the geometry buffer
    glGenTextures(1, &positionTextureHandle);
    glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //the normal buffer
    glGenTextures(1, &normalTextureHandle);
    glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //the color buffer
    glGenTextures(1, &colorTextureHandle);
    glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, (mHeight/4.0)*3, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //the depth buffer
    glGenRenderbuffers(1, &depthbufferHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, (mHeight/4.0)*3); //800x600
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbufferHandle);

    //set color attachments
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTextureHandle, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTextureHandle, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTextureHandle, 0);

    //set the list of draw buffers.
    GLenum drawBufferHandles[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, drawBufferHandles);
}

void DeferredShader::createScreenFillVertexArrayObject() {
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
}

void DeferredShader::render(GraphicsComponent* graphcomp){
	glBindVertexArray(graphcomp->getMesh()->getVAO());
	glBindTexture(GL_TEXTURE_2D, graphcomp->getMaterial()->getDiffuseMap()->getTextureHandle());
	glDrawArrays(GL_TRIANGLES, 0, sizeof(graphcomp->getMesh()->getVAO()));
}

void DeferredShader::uploadModelMatrix(glm::mat4 modelMatrix){
	mGBuffer->uploadModelMatrix(modelMatrix);
}
void DeferredShader::uploadViewMatrix(glm::mat4 viewMatrix){
	mGBuffer->uploadViewMatrix(viewMatrix);
}
void DeferredShader::uploadProjectionMatrix(glm::mat4 projectionMatrix){
	mGBuffer->uploadProjectionMatrix(projectionMatrix);
}

void DeferredShader::composeScene(){

	createScreenFillVertexArrayObject();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(screenFillVertexArrayHandle);
    glUseProgram(mSimpleTexture->getProgramHandle());

    glViewport(0, (mHeight/4)*3, mWidth/3, mHeight/4);
    glBindTexture(GL_TEXTURE_2D, positionTextureHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-LEFT VIEWPORT

    glViewport(mWidth/3, (mHeight/4)*3, mWidth/3, mHeight/4);
    glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-CENTER VIEWPORT

    glViewport((mWidth/3)*2, (mHeight/4)*3, mWidth/3, mHeight/4);
    glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3); //DRAW PLANE INTO TOP-RIGHT VIEWPORT

    //show what's been drawn

}

void DeferredShader::clearScene(){
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(mGBuffer->getProgramHandle());
    glViewport(0, 0, mWidth, (mHeight/4)*3);
}
