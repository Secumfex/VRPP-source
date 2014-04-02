#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "../libraries/Feature_Fauna/Seetang.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicWorldSimulationListener.h"

/*
 * A basic executable to use as starting point with our libraries
 * see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
 * tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
 */

Application* testingApp;
VRState* testingState;
IOHandler* testingInputHandler;
Seetang* Sea;
btRigidBody* Test;
PhysicsComponent* phyComp;

void configureTestingApplication() {
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(	new PrintMessageListener(string("Application is terminating")));
	testingApp->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));

}

void configureVirtualObjects() {
	//testingState = 	new VRState("VRSTATE");
	testingState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	testingState->		attachListenerOnActivation(	new SetClearColorListener(0.44,0.5,0.56));					// custom background color
	testingState-> 	attachListenerOnActivation(	new PrintCameraStatusListener( testingState->getCamera()));


	/* creation and customization of Virtual Objects */
	/* use testingState->createVirtualObject() to create a Virtual Object */
	VirtualObject* 	cube2 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 0.0, 8);
	cube2->translate(glm::vec3(0, 0, 0));
	//cube2->setPhysicsComponent(0.5,0.0,0.0,0.0,0.0,1);
	cube2->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,0,0),btVector3(0,0,0));
	//phyComp->getRigidBody()->setDamping(5,100);
	//phyComp->getRigidBody()->setSleepingThresholds(1,1);
	//phyComp->getRigidBody()->applyForce(btVector3(0,0,0),btVector3(0,0,0));
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube2));


	VirtualObject* 	cube3 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 1.0, 8);
	cube3->translate(glm::vec3(0, 1, 0));
	//cube3->setPhysicsComponent(0.5,0.0,0.0,0.0,1.0,1);
	cube3->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,11,0),btVector3(0,0,0));
	//phyComp->getRigidBody()->setDamping(5,100);
	//phyComp->getRigidBody()->setSleepingThresholds(1,1);
	//phyComp->getRigidBody()->applyForce(btVector3(0,-5,0),btVector3(0,0,0));
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube3));


	VirtualObject* 	cube4 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 1.0, 8);
	//cube4->setPhysicsComponent(0.5,0.0,0.0,0.0,1.0,8);
	cube4->translate(glm::vec3(0, 2, 0));
	/*
	phyComp = cube4->getPhysicsComponent();
	phyComp->getRigidBody()->setDamping(5,100);
	phyComp->getRigidBody()->setSleepingThresholds(1,1);
	phyComp->getRigidBody()->activate(true);

	phyComp->getRigidBody()->applyForce(btVector3(0,-5,0),btVector3(0,0,0));
	*/
	//cube4->getPhysicsComponent()->getRigidBody()->setDamping(5,100);
	//cube4->getPhysicsComponent()->getRigidBody()->setSleepingThresholds(1,1);
	cube4->getPhysicsComponent()->getRigidBody()->activate(true);

	cube4->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,-11,0),btVector3(0,0,0));
	//cube4->getPhysicsComponent()->getRigidBody()->applyCentralImpulse( btVector3( 0.f, 0.f, -15 ) );
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube4));


	VirtualObject* 	cube5 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 1.0, 8);
	//cube5->setPhysicsComponent(0.5,0.0,0.0,0.0,1.0,8);
	cube5->translate(glm::vec3(0, 4, 0));

	//cube5->getPhysicsComponent()->getRigidBody()->setDamping(5,100);
	//cube5->getPhysicsComponent()->getRigidBody()->setSleepingThresholds(1,1);
	cube5->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,15,0),btVector3(0,0,0));
	cube5->getPhysicsComponent()->getRigidBody()->applyCentralImpulse( btVector3( 0.f, 0.f, 15 ) );
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube5));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	//create an invisible ground plane
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);


}

void configurePhysics() {
	/* customization of Bullet / Physicsworld */

}

void configureInputHandler() {
	/* customization of input handling */
	/* use listener interfaces for: what should happen when a specific key is pressed, etc. */
	testingInputHandler->attachListenerOnKeyPress(	new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress(	new SetCameraPositionListener(testingState->getCamera(), glm::vec3(0.0f,0.1f,0.0)),	GLFW_KEY_SPACE);

}

void configureRendering() {
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	/* use listener interfaces for: what should happen everytime a frame is drawn */

	/*comment in to use placeholders for Renderloop, rendering every VO of the testingState; change Shader paths to use a different shader*/
// testingApp->attachListenerOnProgramInitialization( new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag")));
// testingApp->attachListenerOnRenderManagerFrameLoop( new RenderloopPlaceHolderListener());
	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener(	new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());
}

void configureOtherStuff() {
	/* customization for other stuff */

}

void configureApplication() {
	/* create minimal Application with one state */
	testingApp = Application::getInstance();		//sets up Application
	testingApp->setLabel("PROJEKT PRAKTIKUM");
	testingState = new VRState("TESTING FRAMEWORK");
	testingApp->addState(testingState);
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

	configureApplication();	// 1 do some customization

	testingApp->run();	// 2 run application

	return 0;	// 3 end :)
}
