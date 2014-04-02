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
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

/*
 * A basic executable to use as starting point with our libraries
 * see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
 * tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
 */

Application* testingApp;
VRState* testingState;
IOHandler* testingInputHandler;
Camera* cam;
PhysicsComponent* phyComp;

//Seetang* Sea;
//btRigidBody* Test;
//PhysicsComponent* phyComp;

void configureApplication() {
	/* create minimal Application with one state */
	testingApp = Application::getInstance();		//sets up Application
	testingApp->setLabel("PROJEKT PRAKTIKUM");


	//customize VRState
	testingState = new VRState("TESTING FRAMEWORK");
	testingState->attachListenerOnAddingVirtualObject(	new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));// console output when virtual object is added
	testingState->attachListenerOnActivation(			new SetClearColorListener(0.44, 0.5, 0.56));// custom background color
	testingState->attachListenerOnActivation(			new PrintCameraStatusListener(testingState->getCamera()));

	cam = testingState->getCamera();
	cam->setPosition(0,5,15);

//customize VOs
	//create Floor
	VirtualObject* floor = testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 0.0, 1);
	glm::mat4 myModelMatrix1 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	floor->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
	floor->setPhysicsComponent(10.0f, 0.4f, 10.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1);


	VirtualObject* cube2 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 0.0, 8);
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(cube2));
	testingState->attachListenerOnBeginningProgramCycle(new UpdatePhysicsComponentListener(cube2));
	cube2->translate(glm::vec3(0, 0, 0));
	cube2->setPhysicsComponent(0.1,0,0,0,0,0);
	btRigidBody* rigidBody2 = cube2->getPhysicsComponent()->getRigidBody();
	rigidBody2->setActivationState(DISABLE_DEACTIVATION);
	btTransform t;
	t = btTransform::getIdentity();
	t.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	VirtualObject* cube3 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE,1.0, 8);
	testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(cube3));
	cube3->translate(glm::vec3(0, 3, 0));
	cube3->setPhysicsComponent(0.5,0,3,0,1,0);
	cube3->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,150,0),btVector3(0,0,0));
	cube3->getPhysicsComponent()->getRigidBody()->applyDamping(150);
	cube3->getPhysicsComponent()->getRigidBody()->setDamping(10,100);
	cube3->getPhysicsComponent()->getRigidBody()->setGravity((cube3->getPhysicsComponent()->getRigidBody()->getGravity())+btVector3(0,150,0));
	cube3->getPhysicsComponent()->getRigidBody()->setSleepingThresholds(1,1);

	btRigidBody* rigidBody3 = cube3->getPhysicsComponent()->getRigidBody();
	rigidBody3->setActivationState(DISABLE_DEACTIVATION);
	btTransform s;
	s = btTransform::getIdentity();
	s.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	VirtualObject* cube4 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE,1.0, 8);
	testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(cube4));
	cube4->translate(glm::vec3(0, 3, 0));
	cube4->setPhysicsComponent(0.5,0,5,0,1,0);
	cube4->getPhysicsComponent()->getRigidBody()->applyForce(btVector3(0,150,0),btVector3(0,0,0));
	cube4->getPhysicsComponent()->getRigidBody()->applyDamping(150);
	cube4->getPhysicsComponent()->getRigidBody()->setDamping(10,100);
	cube4->getPhysicsComponent()->getRigidBody()->setGravity((cube4->getPhysicsComponent()->getRigidBody()->getGravity())+btVector3(0,150,0));
	cube4->getPhysicsComponent()->getRigidBody()->setSleepingThresholds(1,1);

	btRigidBody* rigidBody4 = cube4->getPhysicsComponent()->getRigidBody();
	rigidBody4->setActivationState(DISABLE_DEACTIVATION);
	btTransform r;
	r = btTransform::getIdentity();
	r.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	btGeneric6DofConstraint* constraint23 = new btGeneric6DofConstraint(*rigidBody2, *rigidBody3, t, s, false);
	constraint23->setLinearUpperLimit(btVector3(0.,10.,0.));
	btGeneric6DofConstraint* constraint24 = new btGeneric6DofConstraint(*rigidBody3, *rigidBody4, s, r, false);
	constraint24->setLinearUpperLimit(btVector3(0.,10.,0.));


//	constraint23->setLinearLowerLimit(btVector3(springRestLen - springRange, 0., 0.));
	PhysicWorld::getInstance()->dynamicsWorld->addConstraint(constraint23);
	PhysicWorld::getInstance()->dynamicsWorld->addConstraint(constraint24);



	testingState->attachListenerOnBeginningProgramCycle(new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));// updates physics simulation

	testingInputHandler = testingState->getIOHandler();
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress(		new SetCameraPositionListener(testingState->getCamera(),glm::vec3(0.0f, 0.1f, 0.0)), GLFW_KEY_SPACE);

	/*	further customize application functionality by adding various listeners */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(string("Application is terminating")));
	testingApp->attachListenerOnBeginningProgramCycle(	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));

	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener(
														new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());

	std::cout<< PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	/*	add customized states to application state pool*/
	testingApp->addState(testingState);
}

int main() {

	configureApplication();	// 1 do some customization

	testingApp->run();	// 2 run application

	return 0;	// 3 end :)
}
