/*
 * DeferredShader.h
 *
 *  Created on: 13.12.2013
 *      Author: Raphimulator
 */

#ifndef DEFERREDSHADER_H_
#define DEFERREDSHADER_H_

#include <Visuals/GraphicsComponent.h>
#include <Visuals/Shader.h>

class DeferredShader {
public:
	DeferredShader(Shader* screenFill = new Shader("/GBuffer/screenFill.vert", "/GBuffer/simpleTexture.frag"), Shader* gBuffer = new Shader("/GBuffer/screenFill.vert", "/GBuffer/GBuffer.frag"), Shader* finalCompositing= new Shader("/GBuffer/screenFill.vert", "/GBuffer/finalCompositing.frag"));
	virtual ~DeferredShader();

void render(GraphicsComponent* graphcomp);

void uploadModelMatrix(glm::mat4 modelMatrix);
void uploadViewMatrix(glm::mat4 viewMatrix);
void uploadProjectionMatrix(glm::mat4 projectionMatrix);

void clearScene();
void composeScene();
void setFormat(int width, int height);

private:
	Shader* mSimpleTexture;
	Shader* mGBuffer;
	Shader* mFinalCompositing;

	GLuint screenFillVertexArrayHandle;

	int mWidth, mHeight;

    GLint positionMapHandle;
    GLint colorMapHandle;
    GLint normalMapHandle;
    GLint blurStrengthHandle;

    GLuint framebufferHandle;
    GLuint positionTextureHandle;
    GLuint normalTextureHandle;
    GLuint colorTextureHandle;
    GLuint depthbufferHandle;

	void createBuffers ();
	void createScreenFillVertexArrayObject();


};

#endif /* DEFERREDSHADER_H_ */
