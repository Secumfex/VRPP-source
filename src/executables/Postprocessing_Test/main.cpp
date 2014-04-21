#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

void configureTestingApplication(){
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

}

void configureVirtualObjects(){
	//setInitialGraphicsComponentList

}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */

}

void configureInputHandler(){
	/* customization of input handling */
	/* use listener interfaces for: what should happen when a specific key is pressed, etc. */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

}

void configureRendering(){
	/* creating shaders */
	Shader *simpleTexShader = new Shader(SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/simpleTexture.frag");

	Shader *finalCompShader = new Shader(	SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/finalCompositing.frag");

	Shader *gbufferShader = new Shader(		SHADERS_PATH "/Postprocessing/GBuffer.vert",
			SHADERS_PATH "/Postprocessing/GBuffer.frag");

	Shader *gbuffer_normalMap_Shader = new Shader(		SHADERS_PATH "/Postprocessing/GBuffer.vert",
			SHADERS_PATH "/Postprocessing/GBuffer_normalTexture.frag");

	Shader *postprocessShader = new Shader( 	SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/glow.frag");


	/* creating and seting up fbos */
	FrameBufferObject *fbo = new FrameBufferObject(800, 600);

	fbo->bindFBO();
	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createSpecularTexture();
	fbo->createShadowMap();
	fbo->makeDrawBuffers();	// draw color to color attachment 0
	fbo->unbindFBO();
	
	FrameBufferObject *fbo2 = new FrameBufferObject(800, 600);

	fbo2->bindFBO();
	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createSpecularTexture();
	fbo->createShadowMap();
	fbo2->makeDrawBuffers();
	fbo2->unbindFBO();

	/* creating listeners */
	Listener* uniResX = new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", 800, "resX");
	Listener* uniResY = new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", 600, "resY");
	Listener* uniPositionMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "positionMap", 	fbo->getPositionTextureHandle());
	Listener* uniColorMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "colorMap", 	fbo->getColorTextureHandle());
	Listener* uniNormalMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "normalMap", 	fbo->getNormalTextureHandle()); 
	Listener* uniPositionMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "positionMap", 	fbo2->getPositionTextureHandle());
	Listener* uniColorMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "colorMap", 	fbo2->getColorTextureHandle());
	Listener* uniNormalMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "normalMap", 	fbo2->getNormalTextureHandle()); 

	testingApp->attachListenerOnProgramInitialization( new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Postprocessing/GBuffer.vert", SHADERS_PATH "/Postprocessing/GBuffer.frag")));

	/* gbuffer renderpass */
	RenderPass* gBufferRenderPass = new RenderPass(gbufferShader, fbo);
	gBufferRenderPass->setCustomClearColor( glm::vec4(1.0, 1.0, 1.0, 1.0) );
	gBufferRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniResX );
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniResY );
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniPositionMap1 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniColorMap1 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniNormalMap1 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden


	testingState->getRenderLoop()->addRenderPass(	gBufferRenderPass );

	/* compositing renderpass */
	
	RenderPass* compositingRenderPass = new RenderPass(finalCompShader, fbo2);
	compositingRenderPass->setCustomClearColor( glm::vec4(1.0, 1.0, 1.0, 1.0) );
	compositingRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	compositingRenderPass->attachListenerOnPostUniformUpload( uniResX );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniResY );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniPositionMap2 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
	compositingRenderPass->attachListenerOnPostUniformUpload( uniColorMap2 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
	compositingRenderPass->attachListenerOnPostUniformUpload( uniNormalMap2 );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden



	testingState->getRenderLoop()->addRenderPass(	compositingRenderPass );

	/* postprocessing renderpass */
	MixTexturesRenderPass* glowRenderPass = new MixTexturesRenderPass( postprocessShader, 0, fbo->getColorTextureHandle(), fbo2->getPositionTextureHandle() );
	glowRenderPass->setBaseTextureUniformName( "colorMap" );	// set custom uniform name for base texture
	glowRenderPass->setMixTextureUniformName(  "preGlowTexture" );
	glowRenderPass->attachListenerOnPostUniformUpload( uniResX );
	glowRenderPass->attachListenerOnPostUniformUpload( uniResY );



	testingState->getRenderLoop()->addRenderPass( glowRenderPass );

	

}

void configureOtherStuff(){
	/* customization for other stuff */
	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("POSTPROCESSING");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();
	configurePhysics();
	configureInputHandler();
	configureRendering();
	configureOtherStuff();
}

int main() {

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
