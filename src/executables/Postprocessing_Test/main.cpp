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
	VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();

	VirtualObject *object03 = voFactory->createVirtualObject(RESOURCES_PATH "/barrel.obj", VirtualObjectFactory::OTHER);
	VirtualObject *object02 = voFactory->createVirtualObject(RESOURCES_PATH "/cow.obj", VirtualObjectFactory::OTHER);
	VirtualObject *object01 = voFactory->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE);

	GraphicsComponent* triangle = voFactory->getTriangle();

	MaterialManager::getInstance()->makeMaterial("polished_chrome", object02->getGraphicsComponent());

	testingState->getRenderQueue()->addVirtualObject(object01);
	testingState->getRenderQueue()->addVirtualObject(object02);
	testingState->getRenderQueue()->addVirtualObject(object03);

	using namespace glm;
	float angle = 0.0f;
	float rotationSpeed = 1.0f;

		glEnable(GL_DEPTH_TEST);

		//rotation angle
		angle = fmod((float)(angle+rotationSpeed*glfwGetTime()), (float)(pi<float>()*2.0f));
		glfwSetTime(0.0);

		//scale a cube into a flat plane
		mat4 modelMatrix01 = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));

		//nice rotation of a small cube
		mat4 modelMatrix02 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.9f, 0.9f, 0.9f));

		mat4 modelMatrix03 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(0.0f, 1.0f, 1.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.3f, 0.3f, 0.3f));

		object01->setModelMatrix(modelMatrix01);
		object02->setModelMatrix(modelMatrix02);
		object03->setModelMatrix(modelMatrix03);

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
	fbo2->createPositionTexture();
	fbo2->createNormalTexture();
	fbo2->createColorTexture();
	fbo2->createSpecularTexture();
	fbo2->createShadowMap();
	fbo2->makeDrawBuffers();
	fbo2->unbindFBO();

	/* creating listeners */
	Listener* uniResX = new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", 800, "resX");
	Listener* uniResY = new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", 600, "resY");
	Listener* uniPositionMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 4, "positionMap", 	fbo->getPositionTextureHandle());	// upload to texture unit 4 ( default position Map unit )
	Listener* uniNormalMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 5, "normalMap", 	fbo->getNormalTextureHandle());// upload to texture unit 5 ( default normal Map unit )
	Listener* uniColorMap1 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 6, "colorMap", 	fbo->getColorTextureHandle()); // upload to texture unit 6 ( default color Map unit )
	Listener* uniPositionMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 4, "positionMap", 	fbo2->getPositionTextureHandle());
	Listener* uniNormalMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 5, "normalMap", 	fbo2->getNormalTextureHandle());
	Listener* uniColorMap2 = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 6, "colorMap", 	fbo2->getColorTextureHandle());

	//testingApp->attachListenerOnProgramInitialization( new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Postprocessing/GBuffer.vert", SHADERS_PATH "/Postprocessing/GBuffer.frag")));

	/* gbuffer renderpass */
	RenderPass* gBufferRenderPass = new RenderPass(gbufferShader, fbo);
	gBufferRenderPass->setCustomClearColor( glm::vec4(1.0, 1.0, 1.0, 1.0) );
	gBufferRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniResX );
	gBufferRenderPass->attachListenerOnPostUniformUpload( uniResY );

	gBufferRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue()->getGraphicsComponentList() ));

	testingState->getRenderLoop()->addRenderPass(	gBufferRenderPass );

	/* compositing renderpass */
	
	RenderPass* compositingRenderPass = new RenderPass(finalCompShader, fbo2);
	compositingRenderPass->setCustomClearColor( glm::vec4(1.0, 1.0, 1.0, 1.0) );
	compositingRenderPass->setClearColorBufferBit(true);	// clear color buffer on every frame
	compositingRenderPass->attachListenerOnPostUniformUpload( uniResX );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniResY );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniPositionMap1 );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniColorMap1 );
	compositingRenderPass->attachListenerOnPostUniformUpload( uniNormalMap1 );

	compositingRenderPass->addInitialGraphicsComponent( VirtualObjectFactory::getInstance()->getTriangle() );

	testingState->getRenderLoop()->addRenderPass( compositingRenderPass );

	/* postprocessing renderpass */
	MixTexturesRenderPass* glowRenderPass = new MixTexturesRenderPass( postprocessShader, 0, fbo->getColorTextureHandle(), fbo2->getPositionTextureHandle() );
	glowRenderPass->setBaseTextureUniformName( "colorMap" );	// set custom uniform name for base texture
	glowRenderPass->setMixTextureUniformName(  "preGlowTexture" );
	glowRenderPass->attachListenerOnPostUniformUpload( uniResX );
	glowRenderPass->attachListenerOnPostUniformUpload( uniResY );
	glowRenderPass->attachListenerOnPostUniformUpload( uniPositionMap2 );
	glowRenderPass->attachListenerOnPostUniformUpload( uniColorMap2 );
	glowRenderPass->attachListenerOnPostUniformUpload( uniNormalMap2 );

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
