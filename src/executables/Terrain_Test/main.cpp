#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"

#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "HeightfieldScene.h"

/*
#include "Visuals/VirtualObjectFactory.h"
#include "Physics/PhysicWorld.h"
#include "SomeListeners.h" // until missing functionality is added
#include "IO/PlayerCamera.h"
*/

Application* myApp;
VRState* myVRState;
IOHandler* myIOHandler;

//PlayerCamera*   playercam;


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

	Listener* uniTex1 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",0,"texture1",HeightfieldScene::ground1->getTextureHandle());
	Listener* uniTex2 = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",1,"texture2",HeightfieldScene::ground2->getTextureHandle());
	Listener* uniMask = new UploadUniformTextureListener("UNIFORMUPLOADLISTENER",2,"textureMask",HeightfieldScene::mask->getTextureHandle());



	Listener* unbindCurrentFBO = new UnbindFrameBufferObjectListener();

	myApp->attachListenerOnProgramInitialization(new SetCurrentShaderListener(hfShader));

	myApp->attachListenerOnRenderManagerFrameLoop(new SetCurrentShaderListener(hfShader));
	myApp->attachListenerOnRenderManagerFrameLoop(uniTex1);
	myApp->attachListenerOnRenderManagerFrameLoop(uniTex2);
	myApp->attachListenerOnRenderManagerFrameLoop(uniMask);
	TerrainRenderPass* renderTerrain = new TerrainRenderPass(HeightfieldScene::fboGround);
	myApp->attachListenerOnRenderManagerFrameLoop(renderTerrain);
}
void configureMyApp(){
	/*	customize application a little bit*/
	myApp = Application::getInstance();			//create an Application labeled PROJEKT PRAKTIKUM
	myApp->	setLabel("PROJEKT PRAKTIKUM");

	/*	customize myVRState*/
	myVRState = 	new VRState("VRSTATE"); 	// create a VRState labeled VRSTATE
	myApp->addState(	myVRState);		//add the VR State to Application

	myIOHandler = myVRState-> getIOHandler();

	configTestingApp();
	configVOs();
	configPhysics();
	configIOHandler();
	configRendering();

	/*
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));
	 */

	//playercam = new PlayerCamera();
	//myVRState->setCamera(playercam);

	/*	customize virtual objects*/

	//VirtualObject* groundObject = myVRState->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::PLANE);

	/*
	VirtualObject* 	terrain = 	myVRState->	createVirtualObject(RESOURCES_PATH "/Heightfield/terrainTest.obj", VirtualObjectFactory::TERRAIN);
	*/

	//glm::mat4 myModelMatrix1 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	//terrain->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
	//terrain->setPhysicsComponent(RESOURCES_PATH"/terrainTest.png", 2048, 2048, 0.0f, 0.0f, 1);
	//myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(terrain));

	//btRigidBody* camBody = playercam->getRigidBody();
	//playercam->setPosition(0.0f,2.0f,5.0f);
	//PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(camBody);

	/*
	VirtualObject* 	cube20 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");

	glm::mat4		cube20M = 	glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 3.0f, 0.0f));
	cube20-> setModelMatrix(		cube20M); 	// override default Model Matrix
	cube20->	setPhysicsComponent(1.0f, 1.0f, 1.0f, 1.5f, 3.0f, 0.0f, 1.0f);
	myVRState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube20));
	*/

	/*	load some virtual objects into vr state scene*/	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically


	// attach some listeners to keyboard key presses
	/*
	myIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.0,0.0,0.0),	GLFW_KEY_1);		// pressing '1' : black background
	myIOHandler->attachListenerOnKeyPress(new SetClearColorListener(1.0,1.0,1.0), 	GLFW_KEY_2);		// pressing '2' : white background
	myIOHandler->attachListenerOnKeyPress(new SetClearColorListener(0.44,0.5,0.56), 	GLFW_KEY_3);		// pressing '3' : default greyish-blue background
	myIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.1f, 0.0f), 	GLFW_KEY_LEFT);		// pressing '<-' : view direction at an angle to the left
	myIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_LEFT);
	myIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), -0.1f, 0.0f), 	GLFW_KEY_RIGHT);	// pressing '->' : view direction at an angle to the right
	myIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_RIGHT);
	myIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.0f, 0.1f), 	GLFW_KEY_UP);		// pressing '<-' : view direction straight ahead
	myIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_UP);
	myIOHandler->attachListenerOnKeyPress(new TurnCameraListener(myVRState->getCamera(), 0.0f, -0.1f), 	GLFW_KEY_DOWN);		// pressing '->' : view direction straight ahead
	myIOHandler->attachListenerOnKeyPress(new PrintCameraStatusListener( myVRState->getCamera()), 								GLFW_KEY_DOWN);
	myIOHandler->attachListenerOnMouseButtonPress(new PickRayListener(myVRState->getCamera()), GLFW_MOUSE_BUTTON_2);		//
	*/
	//myVRStateIOHandler->attachListenerOnMouseButtonPress(new ShootSphereListener(myVRState->getCamera(), myVRState), GLFW_MOUSE_BUTTON_LEFT);

	/*
	SelectionHandler* sh = myIOHandler->getSelectionHandler();
	myIOHandler->attachListenerOnMouseButtonPress(new ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(sh, myVRState->getCamera(),50.0f), GLFW_MOUSE_BUTTON_RIGHT);
	*/

	//myVRStateIOHandler->attachListenerOnKeyPress(new ApplyLinearImpulseOnRigidBody(playercam->getRigidBody(), btVector3(0.0f,5.0f,0.0f)), GLFW_KEY_SPACE );
	//myVRStateIOHandler->attachListenerOnKeyPress(new SetCameraPositionListener(playercam, glm::vec3(0.0f,5.0f,0.0f)), GLFW_KEY_R );

	/*	further customize application functionality by adding various listeners */
	/*
	myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );
	*/

	// attach a listener which overrides the rendermanager's current Shader
	/*
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());

	std::cout << "#collObjs: " << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;
	*/

	/*	add customized states to application state pool*/
}

int main() {

	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
};
