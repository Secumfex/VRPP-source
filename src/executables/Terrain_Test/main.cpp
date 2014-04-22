//test class for shader

#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"

#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "HeightfieldScene.h"


Application* myApp;
VRState* myVRState;
IOHandler* myIOHandler;


void configTestingApp(){

	myApp->attachListenerOnProgramInitialization(new PrintMessageListener(string("Application is booting")));
	myApp->attachListenerOnProgramTermination(new PrintMessageListener(string("Application is terminating")));
}

void configVOs(){

	HeightfieldScene::createScene(myVRState);
}

void configPhysics(){

	myVRState->attachListenerOnBeginningProgramCycle(new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));	// updates physics simulation
}

void configIOHandler(){

	myIOHandler->attachListenerOnKeyPress(new TerminateApplicationListener(myApp), 	GLFW_KEY_ESCAPE);	// Terminate Application by pressing Escape
	myIOHandler->attachListenerOnKeyPress(new RecompileAndSetShaderListener(SHADERS_PATH"/HeightField/heightField.vert",SHADERS_PATH"/HeightField/heightField.frag"), GLFW_KEY_F5);
	myIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener(HeightfieldScene::camera), GLFW_KEY_R);
}

void configRendering(){

	Shader* hfShader = new Shader(SHADERS_PATH"/HeightField/heightField.vert",SHADERS_PATH"/HeightField/heightField.frag");
	//Shader* fcShader = new Shader(SHADERS_PATH"/Underwater_Visuals_Test/screenFill.vert",SHADERS_PATH"/HeightField/finalComp.frag");

	//uniform Listener
	Listener* uniTex1 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",1,"uniformTexture1",HeightfieldScene::ground1->getTextureHandle());
	Listener* uniTex2 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",2,"uniformTexture2",HeightfieldScene::ground2->getTextureHandle());
	Listener* uniMask = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",3,"uniformTextureMask",HeightfieldScene::mask->getTextureHandle());

	/*
	Listener* uniNorm1 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",4,"uniformNormals1",HeightfieldScene::normals1->getTextureHandle());		//normalmaps
	Listener* uniNorm2 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",5,"uniformNormals2",HeightfieldScene::normals2->getTextureHandle());

	Listener* uniSpec1 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",6,"uniformSpecular1",HeightfieldScene::specular1->getTextureHandle());	//glossmaps
	Listener* uniSpec2 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",7,"uniformSpecular2",HeightfieldScene::specular2->getTextureHandle());
	*/

	/*
	Listener* uniFCposition = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",8,"positionOut",HeightfieldScene::fboTexture);
	Listener* uniFCcolor = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",9,"colorOut",HeightfieldScene::fboColor);
	Listener* uniFCnormals = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",10,"normalsOut",HeightfieldScene::fboNormals);
	Listener* uniFCspecular = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",11,"specularOut",HeightfieldScene::fboSpecular);
	*/

	Listener* unbindCurrentFBO = new UnbindFrameBufferObjectListener();

	//myApp->attachListenerOnProgramInitialization(new SetCurrentShaderListener(hfShader));

	//render textures
	//myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(hfShader));

	myApp->attachListenerOnRenderManagerFrameLoop(uniTex1);
	myApp->attachListenerOnRenderManagerFrameLoop(uniTex2);
	myApp->attachListenerOnRenderManagerFrameLoop(uniMask);

	/*
	myApp->attachListenerOnRenderManagerFrameLoop(uniNorm1);	//normalmaps
	myApp->attachListenerOnRenderManagerFrameLoop(uniNorm2);

	myApp->attachListenerOnRenderManagerFrameLoop(uniSpec1);	//glossmaps
	myApp->attachListenerOnRenderManagerFrameLoop(uniSpec2);
	*/

	TerrainRenderPass* renderTerrain = new TerrainRenderPass(HeightfieldScene::fboGround);
	//HeightfieldScene::fboGround->bindFBO();
	myApp->attachListenerOnRenderManagerFrameLoop(renderTerrain);
	//HeightfieldScene::fboGround->unbindFBO();

	//final compositing
	/*
	myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(fcShader));
	RenderGraphicsComponentListener* renderComp = new RenderScreenFillingTriangleListener();
	myApp->attachListenerOnRenderManagerFrameLoop(renderComp);
	*/
}
void configureMyApp(){
	/*	customize application a little bit*/
	myApp = Application::getInstance();
	myApp->	setLabel("PP:HeightmapShaderTest");

	/*	customize myVRState*/
	myVRState = 	new VRState("VRSTATE"); 	// create a VRState labeled VRSTATE
	myApp->addState(	myVRState);				//add the VR State to Application

	myIOHandler = myVRState-> getIOHandler();

	configTestingApp();
	configVOs();
	configPhysics();
	configIOHandler();
	configRendering();
}

int main() {

	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
};
