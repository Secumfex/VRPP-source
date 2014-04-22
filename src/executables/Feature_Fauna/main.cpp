#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "Seetang.h"
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
testingState->attachListenerOnActivation(		new SetClearColorListener(0.44, 0.5, 0.56));// custom background color
testingState->attachListenerOnActivation(		new PrintCameraStatusListener(testingState->getCamera()));

cam = testingState->getCamera();
cam->setPosition(0, 15, 75);
}

void createFloor() {
	VirtualObject* floor = testingState->createVirtualObject( 	RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE, 0.0, 1);
	glm::mat4 myModelMatrix1 = glm::scale(	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),	glm::vec3(5.0f, 0.2f, 5.0f));	//floor
	floor->setModelMatrix(myModelMatrix1); 	// override default Model Matrix
	floor->setPhysicsComponent(10.0f, 0.4f, 10.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1);
	cout<<"1"<<endl;

}

void createVirtualObject(int height) {
	//Erstelle erstes Objekt unten
	vo_tmp = testingState->createVirtualObject( RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 0.0, 8);
	testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(vo_tmp));
	testingState->attachListenerOnBeginningProgramCycle(	new UpdatePhysicsComponentListener(vo_tmp));
	vo_tmp->translate(glm::vec3(0, 0, 0));
	voVec.push_back(vo_tmp);
	rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
	rigidBodyVec.push_back(rb_tmp);
	transform_tmp = btTransform::getIdentity();
	transform_tmp.setOrigin(	btVector3(btScalar(0.), btScalar(0.), btScalar(0.)));
	transformsVec.push_back(transform_tmp);
	//Erstelle folgende Objekte nach oben hin
	float yPosPerVO = 0;
	float xPosPerVO = 0;
	float zPosPerVO = 0;

	for (int i = 1; i < height; i++) {
			xPosPerVO += 5;
			yPosPerVO += 5;
			zPosPerVO += 5;
//		if ( (i%2)==0){
//			xPosPerVO = 0;
//			zPosPerVO = 0;
//		}
//		else if ( (i%3) ==1){
//			xPosPerVO = 5;
//			zPosPerVO = 5;
//		}
//		else {
//			xPosPerVO =-5;
//			zPosPerVO =-5;
//		}

		vo_tmp = testingState->createVirtualObject(	RESOURCES_PATH "/Fauna/plant.obj", VirtualObjectFactory::SPHERE, 1.0, 8);
		vo_tmp->translate(glm::vec3(xPosPerVO, yPosPerVO, zPosPerVO));
		voVec.push_back(vo_tmp);
		testingState->attachListenerOnBeginningProgramCycle(	new UpdateVirtualObjectModelMatrixListener(voVec[i]));
		rb_tmp = vo_tmp->getPhysicsComponent()->getRigidBody();
		rb_tmp->applyForce(btVector3(0.,100.,0), btVector3(0,0,0));
		//rb_tmp->setDamping(.1, .1);
		//Negative Gravity um Erdanziehungskraft zu simulieren
		rb_tmp->setGravity(rb_tmp->getGravity() - rb_tmp->getGravity()+ btVector3(0.,0.,0.));
		//rb_tmp->setFriction(btScalar(250.));
		rb_tmp->setActivationState(DISABLE_DEACTIVATION);
		rigidBodyVec.push_back(rb_tmp);

		transform_tmp = btTransform::getIdentity();
		transform_tmp.setOrigin(	btVector3(btScalar(0.), btScalar(0.), btScalar(0.)));
		transformsVec.push_back(transform_tmp);

		constraint_tmp = new btGeneric6DofSpringConstraint( *rigidBodyVec[i - 1], *rigidBodyVec[i], transformsVec[i - 1], transformsVec[i], true);
		constraint_tmp->setLinearUpperLimit(btVector3(0., 20., 0.));
		constraint_tmp->setLinearLowerLimit(btVector3(0., 16., 0.));
		constraint_tmp->setDamping(.1, .1);
		constraintsVec.push_back(constraint_tmp);
			//constraints[i-1]->internalSetAppliedImpulse(btScalar(50));
					//constraints[i-1]->enableSpring(0, false);
					//constraints[i-1]->setStiffness(0,50);
					//constraints[i-1]->setEquilibriumPoint();

				//	constraint23->setLinearLowerLimit(btVector3(springRestLen - springRange, 0., 0.));
		PhysicWorld::getInstance()->dynamicsWorld->addConstraint( constraintsVec[i-1], true);

	}
}

void catMullRomeSpline(){
	if(voVec.size()>= 2){
		int pos = 0;
		float p0x,p1x,p2x,p3x,p0y,p1y,p2y,p3y,p0z,p1z,p2z,p3z;
		VirtualObject* vo1;
		VirtualObject* vo2;
		VirtualObject* vo3;
		VirtualObject* vo4;
		VirtualObject* cat_tmp;
		vector<VirtualObject*>  catmullVec;
		for (int i = 0; i < voVec.size()-2; ++i) {
			for (float T = 0.0; T < 1.0; T += 0.1) {
				float Catmullx, Catmully, Catmullz = 0.0;

				if (i==0){							//1. Element
					vo1 = voVec[i];
					vo2 = voVec[i];
					if((i+1) == voVec.size()){
						vo3 = voVec[i+1];
						vo4 = voVec[i+1];
					}else{
						vo3 = voVec[i+1];
						vo4 = voVec[i+2];
					}
				}
				else if ((i+1) == (voVec.size()-1)){	//letzte Element
					vo1 = voVec[i-1];
					vo2 = voVec[i];
					vo3 = voVec[i+1];
					vo4 = voVec[i+1];
				}
				else{								// Mitte
					vo1 = voVec[i-1];
					vo2 = voVec[i];
					vo3 = voVec[i+1];
					vo4 = voVec[i+2];
				}
				p0x = (vo1->getPhysicsComponent()->getPosition()).x;
				p1x = (vo2->getPhysicsComponent()->getPosition()).x;
				p2x = (vo3->getPhysicsComponent()->getPosition()).x;
				p3x = (vo4->getPhysicsComponent()->getPosition()).x;

				p0y = (vo1->getPhysicsComponent()->getPosition()).y;
				p1y = (vo2->getPhysicsComponent()->getPosition()).y;
				p2y = (vo3->getPhysicsComponent()->getPosition()).y;
				p3y = (vo4->getPhysicsComponent()->getPosition()).y;

				p0z = (vo1->getPhysicsComponent()->getPosition()).z;
				p1z = (vo2->getPhysicsComponent()->getPosition()).z;
				p2z = (vo3->getPhysicsComponent()->getPosition()).z;
				p3z = (vo4->getPhysicsComponent()->getPosition()).z;

				Catmullx =(T * ((2.0 * p1x) + ((p2x - p0x) * T) + (((2.0 * p0x) - (5.0 * p1x) + (4.0 * p2x) - p3x) * (T * T))
						+ (((3.0 * p1x) - p0x - (3.0 * p2x) + p3x) * (T * T * T))));
				Catmully = (T * ((2.0 * p1y) + ((p2y - p0y) * T) + ((2.0 * p0y - 5.0 * p1y + 4.0 * p2y - p3y) * (T * T))
						+ ((3.0 * p1y - p0y - 3.0 * p2y + p3y) * (T * T * T))));
				Catmullz = (T * ((2.0 * p1z) + ((p2z - p0z) * T) + ((2.0 * p0z - 5.0 * p1z + 4.0 * p2z - p3z) * (T * T))
						+ ((3.0 * p1z - p0z - 3.0 * p2z + p3z) * (T * T * T))));

				cat_tmp = testingState->createVirtualObject( RESOURCES_PATH "/sphere.obj", VirtualObjectFactory::SPHERE, 0.0, 8);
				cat_tmp->translate(glm::vec3(Catmullx, Catmully, Catmullz));
				catmullVec.push_back(cat_tmp);
				testingState->attachListenerOnBeginningProgramCycle( new UpdateVirtualObjectModelMatrixListener(catmullVec[pos]));
				pos++;
			}
		}
	}
}
/*
 * Neue Klasse Seagras physics component, erbt von PhysicsComponent  		-> SeaGrasPhysicsComponent #include PhysicsComponent.h
 * kriegt den Vector von den Catmulls										vector aus GraphicsComponents? Oder doch eigene Klasse ?!
 * kriegt die Objekte, die mit Joints verbunden sind						-> vector aus btGeneric6dofCoinstraints
 *
 * Ein Grafik Objekt, durch mehrer Physikcomponentne beschrieben -> neu schreiben
 * Modelmatrix R�ckgabe durch unterstes Objekt
 * Jede Kugel muss ihre Position per UniformListener an den Shader �bergeben werden
 * Grafik Komponente des Shaders (auch ableiten/neu machen)
 * 			-> statischer Buffer der die unterschiedlichen T's hochladen
 * 			Liste T 0.1 bis n       -> Samplepunkte
 * 			Kontrollpunkte aus den Objekten selber von der physikengine
 * 			Spline im Shader implementieren
 */

void listenersEtc(){
	cout<<"2"<<endl;
	testingState->attachListenerOnBeginningProgramCycle(	new PhysicWorldSimulationListener(	IOManager::getInstance()->getDeltaTimePointer()));// updates physics simulation
	cout<<"3"<<endl;
	testingInputHandler = testingState->getIOHandler();
	cout<<"31"<<endl;
	testingInputHandler->attachListenerOnKeyPress(			new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	cout<<"32"<<endl;
	testingInputHandler->attachListenerOnKeyPress(			new SetCameraPositionListener(testingState->getCamera(), glm::vec3(0.0f, 0.1f, 0.0)), GLFW_KEY_SPACE);
	cout<<"33"<<endl;
	//testingInputHandler->attachListenerOnKeyPress( 			new ApplyLinearImpulseOnRigidBody(rigidBodyVec[3], btVector3(50, 0, 0)), GLFW_KEY_1);
	cout<<"4"<<endl;
	testingApp->attachListenerOnProgramInitialization( 		new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(			new PrintMessageListener(string("Application is terminating")));
	testingApp->attachListenerOnBeginningProgramCycle(		new PhysicWorldSimulationListener(	IOManager::getInstance()->getDeltaTimePointer()));
	testingApp->attachListenerOnProgramInitialization(		new SetDefaultShaderListener(	new Shader(SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(		new RenderloopPlaceHolderListener());
	cout<<"5"<<endl;
	std::cout << PhysicWorld::getInstance()->dynamicsWorld->getNumCollisionObjects() << endl;

	testingApp->addState(testingState);
}
int main() {

	configureApplication();	// 1 do some customization
	createFloor();
	createVirtualObject(5);
	//catMullRomeSpline();
	listenersEtc();
	testingApp->run();	// 2 run application
	return 0;	// 3 end :)
}
