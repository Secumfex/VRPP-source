#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicWorldSimulationListener.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "BulletDynamics/ConstraintSolver/btTypedConstraint.h"
#include <cmath>

//Application* testingApp;
//VRState* testingState;
//IOHandler* testingInputHandler;
//btRigidBody* camBody;
//Camera* cam;
//PhysicsComponent* phyComp;
//
//vector<VirtualObject*> voVec;
//vector<btRigidBody*> rigidBodyVec;
//vector<btTransform> transformsVec;
//vector<btGeneric6DofSpringConstraint*> constraintsVec;
//vector<RenderPass*> rpVec;
//VirtualObject* vo_tmp;
//btRigidBody* rb_tmp;
//btTransform transform_tmp;
//btGeneric6DofSpringConstraint* constraint_tmp;
//
//
//void configureApplication() {
///* create minimal Application with one state */
//testingApp = Application::getInstance();		//sets up Application
//testingApp->setLabel("PROJEKT PRAKTIKUM");
//
//testingState = new VRState("TESTING FRAMEWORK");
//testingState->attachListenerOnAddingVirtualObject(		new PrintMessageListener( string("Added a VirtualObject to RenderQueue")));// console output when virtual object is added
//testingState->attachListenerOnActivation(				new SetClearColorListener(0.44, 0.5, 0.56));// custom background color
//testingState->attachListenerOnActivation(				new PrintCameraStatusListener(testingState->getCamera()));
//
//cam = testingState->getCamera();
//cam->setPosition(0, 65, 75);
//
//}
//
///* Create a Floor plane */
//void createFloor() {
//	VirtualObject* floor = testingState->createVirtualObject( 	RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 0.0, 1);
//	glm::mat4 myModelMatrix1 = glm::scale(	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),	glm::vec3(5.0f, 0.2f, 5.0f));	//floor
//	floor->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
//	floor->setPhysicsComponent(10.0f, 0.4f, 10.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1);
//
//}
//
//void createVirtualObject(int height, float x, float z) {
//
//	voVec.clear();
//	rigidBodyVec.clear();
//	transformsVec.clear();
//	constraintsVec.clear();
//	rpVec.clear();
//
//	//Erstelle erstes Objekt unten statisch
//	vo_tmp = testingState->createVirtualObject( RESOURCES_PATH "/Fauna/Seegras.dae", VirtualObjectFactory::SPHERE, 0.0, 8);
//	testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(vo_tmp));
//	testingState->attachListenerOnBeginningProgramCycle(	new UpdatePhysicsComponentListener(vo_tmp));
//	vo_tmp->translate(glm::vec3(x, 0, z));
//	voVec.push_back(vo_tmp);
//	rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
//	rigidBodyVec.push_back(rb_tmp);
//	transform_tmp = btTransform::getIdentity();
//	transform_tmp.setOrigin(	btVector3(btScalar(x), btScalar(0.), btScalar(z)));
//	transformsVec.push_back(transform_tmp);
//
//	//Erstelle folgende Objekte nach oben hin
//	float xPosPerVO = x;
//	float yPosPerVO = 16;
//	float zPosPerVO = z;
//
//	PhysicWorld::getInstance()->dynamicsWorld->setGravity(btVector3(0,3.0,0));
//
//	for (int i = 1; i < height; i++) {
//
//		vo_tmp = testingState->createVirtualObject(	RESOURCES_PATH "/Fauna/Seegras.dae", VirtualObjectFactory::CUBE, 1.0, 8);
//
//		vo_tmp->translate(glm::vec3(xPosPerVO, yPosPerVO, zPosPerVO));
//		voVec.push_back(vo_tmp);
//
//
//		testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(voVec[i]));
//		rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
//		rb_tmp->setDamping(.2, .9);
//		rb_tmp->setActivationState(DISABLE_DEACTIVATION);
//		rigidBodyVec.push_back(rb_tmp);
//
//		transform_tmp = btTransform::getIdentity();
//		transform_tmp.setOrigin(	btVector3(btScalar(0), btScalar(0), btScalar(0)));
//		transformsVec.push_back(transform_tmp);
//
//		constraint_tmp = new btGeneric6DofSpringConstraint( *rigidBodyVec[i - 1], *rigidBodyVec[i], transformsVec[i - 1], transformsVec[i], true);
//		constraint_tmp->setLinearUpperLimit(btVector3(0., 16., 0.));
//		constraint_tmp->setLinearLowerLimit(btVector3(0., 13., 0.));
//		constraint_tmp->setLimit(0, .9, .9);
//		constraint_tmp->setLimit(2, .9, .9);
//		constraint_tmp->setDamping(.2, .9);
//		constraintsVec.push_back(constraint_tmp);
//		PhysicWorld::getInstance()->dynamicsWorld->addConstraint( constraintsVec[i-1], true);
//
//		yPosPerVO +=16;
//		if(i==0){
//			rpVec[i] = new RenderPass(new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag"));
//			rpVec[i]->setClearColorBufferBit(true);
//			rpVec[i]->setInitialGraphicsComponentList(testingState->getRenderQueue()->getGraphicsComponentList());
//			rpVec[i]->addRenderQueueRequestFlag(new CurrentRenderQueFlag());
//		}else{
//			rpVec[i] = new RenderPass(new Shader(SHADERS_PATH "/FaunaFeature/FaunaFeature.vert", SHADERS_PATH "/FaunaFeature/simpleTexture.frag"));
//
//		}
//	}
//
//	for(int i = 0; i<voVec.size()-2; i++){
//		rpVec[0]->addRenderQueueRequestFlag(new FlagPartOfVirtualObject (voVec[i], true));
//	}
//	testingState->getRenderLoop()->addRenderPass(rpVec[0]);
//
////First Renderpass 1. VO to 2. VO
//	rpVec[1]->addInitialGraphicsComponent(voVec[0]);
//	rpVec[1]->setUseAlphaBlending(true);
//	rpVec[1]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[0], "p0"));
//	rpVec[1]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[0], "p1"));
//	rpVec[1]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[1], "p2"));
//	rpVec[1]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[2], "p3"));
//	testingState->getRenderLoop()->addRenderPass(rpVec[1]);
//
////RenderPasses für die Objekte in zwischen dem 1. und letzten
//	for(int o = 2; o < rpVec.size()-2; o++){
//
//		rpVec[o]->addInitialGraphicsComponent(voVec[o-1]);
//		rpVec[o]->setUseAlphaBlending(true);
//		rpVec[o]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[o-2], "p0"));
//		rpVec[o]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[o-1], "p1"));
//		rpVec[o]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[o], "p2"));
//		rpVec[o]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[o+1], "p3"));
//		testingState->getRenderLoop()->addRenderPass(rpVec[o]);
//
//	}
//
//
////RenderPass letztes Objekt
//	int size = rpVec.size()-1;
//	rpVec[size]->addInitialGraphicsComponent(voVec[3]);
//	rpVec[size]->setUseAlphaBlending(true);
//	rpVec[size]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[size-2], "p0"));
//	rpVec[size]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[size-1], "p1"));
//	rpVec[size]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[size], "p2"));
//	rpVec[size]->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[size], "p3"));
//	testingState->getRenderLoop()->addRenderPass(rpVec[size]);
//
//}

/*
 * A basic executable to use as starting point with our libraries
 * see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
 * tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
 */

/*
 * Ein Billboard, das sich über komplette Dings
 * Tiefenwert nachträglich drauf multiplizieren
 *
 * Weltkoordinaten die wir haben (mit dem T) in Kamerakoordinaten umrechnen,
 * Billboard drüber und dann mit Tiefenwert Multiplizieren (wieder umrechnen?)
 * */


Application* testingApp;
VRState* testingState;
IOHandler* testingInputHandler;
btRigidBody* camBody;
Camera* cam;
PhysicsComponent* phyComp;

vector<VirtualObject*> voVec;
vector<btRigidBody*> rigidBodyVec;
vector<btTransform> transformsVec;
vector<btGeneric6DofSpringConstraint*> constraintsVec;
VirtualObject* vo_tmp;
btRigidBody* rb_tmp;
btTransform transform_tmp;
btGeneric6DofSpringConstraint* constraint_tmp;


void configureApplication() {
/* create minimal Application with one state */
testingApp = Application::getInstance();		//sets up Application
testingApp->setLabel("PROJEKT PRAKTIKUM");

testingState = new VRState("TESTING FRAMEWORK");
testingState->attachListenerOnAddingVirtualObject(		new PrintMessageListener( string("Added a VirtualObject to RenderQueue")));// console output when virtual object is added
testingState->attachListenerOnActivation(				new SetClearColorListener(0.44, 0.5, 0.56));// custom background color
testingState->attachListenerOnActivation(				new PrintCameraStatusListener(testingState->getCamera()));

cam = testingState->getCamera();
cam->setPosition(0, 65, 75);

}

/* Create a Floor plane */
void createFloor() {
	VirtualObject* floor = testingState->createVirtualObject( 	RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 0.0, 1);
	glm::mat4 myModelMatrix1 = glm::scale(	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),	glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	floor->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
	floor->setPhysicsComponent(10.0f, 0.4f, 10.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1);

}

void createVirtualObject(int height, float x, float z) {

	voVec.clear();
	rigidBodyVec.clear();
	transformsVec.clear();
	constraintsVec.clear();

	//Erstelle erstes Objekt unten statisch
	vo_tmp = testingState->createVirtualObject( RESOURCES_PATH "/Fauna/Seegras.dae", VirtualObjectFactory::SPHERE, 0.0, 8);
	testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(vo_tmp));
	testingState->attachListenerOnBeginningProgramCycle(	new UpdatePhysicsComponentListener(vo_tmp));
	vo_tmp->translate(glm::vec3(x, 0, z));
	voVec.push_back(vo_tmp);
	rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
	rb_tmp->setDamping(.2, .9);
	rb_tmp->setActivationState(DISABLE_DEACTIVATION);
	rigidBodyVec.push_back(rb_tmp);
	transform_tmp = btTransform::getIdentity();
	transform_tmp.setOrigin(	btVector3(btScalar(x), btScalar(0.), btScalar(z)));
	transformsVec.push_back(transform_tmp);

	//Erstelle folgende Objekte nach oben hin
	float xPosPerVO = x;
	float yPosPerVO = 16;
	float zPosPerVO = z;

	PhysicWorld::getInstance()->dynamicsWorld->setGravity(btVector3(0,3.0,0));

	for (int i = 1; i < height; i++) {

		vo_tmp = testingState->createVirtualObject(	RESOURCES_PATH "/Fauna/Seegras.dae", VirtualObjectFactory::CUBE, 1.0, 8);

		vo_tmp->translate(glm::vec3(xPosPerVO, yPosPerVO, zPosPerVO));
		voVec.push_back(vo_tmp);


		testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(voVec[i]));
		rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
		rb_tmp->setDamping(.2, .9);
		rb_tmp->setActivationState(DISABLE_DEACTIVATION);
		rigidBodyVec.push_back(rb_tmp);

		transform_tmp = btTransform::getIdentity();
		transform_tmp.setOrigin(	btVector3(btScalar(0), btScalar(0), btScalar(0)));
		transformsVec.push_back(transform_tmp);

		constraint_tmp = new btGeneric6DofSpringConstraint( *rigidBodyVec[i - 1], *rigidBodyVec[i], transformsVec[i - 1], transformsVec[i], true);
		constraint_tmp->setLinearUpperLimit(btVector3(2., 16., 2.));
		constraint_tmp->setLinearLowerLimit(btVector3(2., 14., 2.));
		constraint_tmp->setLimit(0, .9, .9);
		constraint_tmp->setLimit(2, .9, .9);
		constraint_tmp->setDamping(.2, .9);
		constraintsVec.push_back(constraint_tmp);
		PhysicWorld::getInstance()->dynamicsWorld->addConstraint( constraintsVec[i-1], true);

		yPosPerVO +=16;

	}


	RenderPass* pass1 = new RenderPass(new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag"));
	pass1->setClearColorBufferBit(true);
	pass1->setInitialGraphicsComponentList(testingState->getRenderQueue()->getGraphicsComponentList());
	pass1->addRenderQueueRequestFlag(new CurrentRenderQueFlag());
	pass1->addRenderQueueRequestFlag(new FlagPartOfVirtualObject (voVec[1], true));
	pass1->addRenderQueueRequestFlag(new FlagPartOfVirtualObject (voVec[2], true));
	pass1->addRenderQueueRequestFlag(new FlagPartOfVirtualObject (voVec[3], true));
	pass1->addRenderQueueRequestFlag(new FlagPartOfVirtualObject (voVec[4], true));

	testingState->getRenderLoop()->addRenderPass(pass1);

	//vom 1. VO zum 2.
	RenderPass* pass2 = new RenderPass(new Shader(SHADERS_PATH "/FaunaFeature/FaunaFeature.vert", SHADERS_PATH "/FaunaFeature/simpleTexture.frag"));
	pass2->addInitialGraphicsComponent(voVec[0]);
	pass2->setUseAlphaBlending(true);
	pass2->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[0], "p0"));
	pass2->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[0], "p1"));
	pass2->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[1], "p2"));
	pass2->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[2], "p3"));
	testingState->getRenderLoop()->addRenderPass(pass2);

	//vom 2. VO zum 3.
	RenderPass* pass3 = new RenderPass(new Shader(SHADERS_PATH "/FaunaFeature/FaunaFeature.vert", SHADERS_PATH "/FaunaFeature/simpleTexture.frag"));
	pass3->addInitialGraphicsComponent(voVec[1]);
	pass3->setUseAlphaBlending(true);
	pass3->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[0], "p0"));
	pass3->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[1], "p1"));
	pass3->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[2], "p2"));
	pass3->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[3], "p3"));
	testingState->getRenderLoop()->addRenderPass(pass3);

	RenderPass* pass4 = new RenderPass(new Shader(SHADERS_PATH "/FaunaFeature/FaunaFeature.vert", SHADERS_PATH "/FaunaFeature/simpleTexture.frag"));
	pass4->addInitialGraphicsComponent(voVec[2]);
	pass4->setUseAlphaBlending(true);
	pass4->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[1], "p0"));
	pass4->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[2], "p1"));
	pass4->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[3], "p2"));
	pass4->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[4], "p3"));
	testingState->getRenderLoop()->addRenderPass(pass4);

	RenderPass* pass5 = new RenderPass(new Shader(SHADERS_PATH "/FaunaFeature/FaunaFeature.vert", SHADERS_PATH "/FaunaFeature/simpleTexture.frag"));
	pass5->addInitialGraphicsComponent(voVec[3]);
	pass5->setUseAlphaBlending(true);
	pass5->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[2], "p0"));
	pass5->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[3], "p1"));
	pass5->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[4], "p2"));
	pass5->attachListenerOnPostUniformUpload(new UploadUniformVOListener("", voVec[4], "p3"));
	testingState->getRenderLoop()->addRenderPass(pass5);

}



void listenersEtc(){

	testingState->attachListenerOnBeginningProgramCycle(	new PhysicWorldSimulationListener(	IOManager::getInstance()->getDeltaTimePointer()));// updates physics simulation

	testingInputHandler = testingState->getIOHandler();
	testingInputHandler->attachListenerOnKeyPress(			new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress(			new SetCameraPositionListener(testingState->getCamera(), glm::vec3(0.0f, 0.1f, 0.0)), GLFW_KEY_SPACE);
	testingInputHandler->attachListenerOnMouseButtonPress(  new ShootSphereListener(testingState->getCamera(), testingState), GLFW_MOUSE_BUTTON_LEFT);


	testingApp->attachListenerOnProgramInitialization( 		new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(			new PrintMessageListener(string("Application is terminating")));
	testingApp->attachListenerOnBeginningProgramCycle(		new PhysicWorldSimulationListener(	IOManager::getInstance()->getDeltaTimePointer()));
	testingApp->attachListenerOnProgramInitialization(		new SetDefaultShaderListener(	new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag")));

	std::cout << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	testingApp->addState(testingState);
}

int main() {

	configureApplication();	// 1 do some customization
	createFloor();
	createVirtualObject(5,0,0);
	//createVirtualObject(3,2,2);
	listenersEtc();
	testingApp->run();	// 2 run application
	return 0;	// 3 end :)
}
