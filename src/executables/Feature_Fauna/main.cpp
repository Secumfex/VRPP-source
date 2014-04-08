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
#include "BulletDynamics/ConstraintSolver/btTypedConstraint.h"

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


	VirtualObject* sphere0 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 0.0, 8);
	testingState->attachListenerOnBeginningProgramCycle(new UpdateVirtualObjectModelMatrixListener(sphere0));
	testingState->attachListenerOnBeginningProgramCycle(new UpdatePhysicsComponentListener(sphere0));
	sphere0->translate(glm::vec3(0, 0, 0));
	sphere0->setPhysicsComponent(0.1,0,0,0,0,0);
	btRigidBody* rigidBody0 = sphere0->getPhysicsComponent()->getRigidBody();
	//rigidBody2->setActivationState(DISABLE_DEACTIVATION);
	btTransform t;
	t = btTransform::getIdentity();
	t.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	VirtualObject* sphere1 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE,1.0, 8);
	testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(sphere1));
	sphere1->translate(glm::vec3(0, 10, 0));
	sphere1->setPhysicsComponent(0.5,0,10,0,1,0);
	btRigidBody* rigidBody1 = sphere1->getPhysicsComponent()->getRigidBody();
	rigidBody1->applyForce(btVector3(0,150,0),btVector3(0,0,0));
	rigidBody1->applyDamping(150);
	rigidBody1->setDamping(10,100);
	rigidBody1->setGravity((sphere1->getPhysicsComponent()->getRigidBody()->getGravity())+btVector3(0,150,0));
	rigidBody1->setSleepingThresholds(1,1);
	rigidBody1->setActivationState(DISABLE_DEACTIVATION);
	btTransform s;
	s = btTransform::getIdentity();
	s.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	VirtualObject* cube4 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE,1.0, 8);
	testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(cube4));
	cube4->translate(glm::vec3(0, 20, 0));
	cube4->setPhysicsComponent(0.5,0,20,0,1,0);
	btRigidBody* rigidBody2 = cube4->getPhysicsComponent()->getRigidBody();
	rigidBody2->applyForce(btVector3(0,150,0),btVector3(0,0,0));
	rigidBody2->applyDamping(150);
	rigidBody2->setDamping(10,100);
	rigidBody2->setGravity((rigidBody2->getGravity())+btVector3(0,150,0));
	rigidBody2->setSleepingThresholds(1,1);
	rigidBody2->setActivationState(DISABLE_DEACTIVATION);
	btTransform r;
	r = btTransform::getIdentity();
	r.setOrigin(btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));

	//btGeneric6DofConstraint* constraint23 = new btGeneric6DofConstraint(*rigidBody2, *rigidBody1, t, s, false);

	btGeneric6DofSpringConstraint* constraint01 = new btGeneric6DofSpringConstraint(*rigidBody0, *rigidBody1, t, s, true);
	constraint01->setLinearUpperLimit(btVector3(0.,10.,0.));
	constraint01->setLinearLowerLimit(btVector3(0.,10.,0.));
	constraint01->enableSpring(0, false);
	constraint01->enableSpring(1, false);
	constraint01->setStiffness(0,50);
	constraint01->setDamping(5,5);
	constraint01->setEquilibriumPoint();

	btGeneric6DofSpringConstraint* constraint12 = new btGeneric6DofSpringConstraint(*rigidBody1, *rigidBody2, s, r, true);
	constraint12->setLinearUpperLimit(btVector3(0.,10.,0.));
	constraint12->setLinearLowerLimit(btVector3(0.,10.,0.));
	constraint12->enableSpring(0, false);
	constraint12->enableSpring(1, false);
	constraint12->setStiffness(0,50);
	constraint12->setDamping(5,5);
	constraint12->setEquilibriumPoint();


	VirtualObject* cubeTop = testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::OTHER, 1.0, 8);
	testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(cubeTop));
	cubeTop->translate(glm::vec3(0,30,0));
	cubeTop->setPhysicsComponent(1,0,30,0,1,0);
	btRigidBody* rigidBodyCubeTop = cubeTop->getPhysicsComponent()->getRigidBody();
	rigidBodyCubeTop->setActivationState(DISABLE_DEACTIVATION);
	rigidBodyCubeTop->setGravity((rigidBodyCubeTop->getGravity())+btVector3(0,-250,0));
	rigidBodyCubeTop->applyGravity();
	rigidBodyCubeTop->setDamping(10,10);
	rigidBodyCubeTop->applyDamping(20);


//	constraint23->setLinearLowerLimit(btVector3(springRestLen - springRange, 0., 0.));
	PhysicWorld::getInstance()->dynamicsWorld->addConstraint(constraint01, true);
	PhysicWorld::getInstance()->dynamicsWorld->addConstraint(constraint12, true);




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
