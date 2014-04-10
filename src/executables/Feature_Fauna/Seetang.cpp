#include <iostream>
#include "Seetang.h"
using namespace std;

float x=0;
float y=0;
float z=0;

vector<VirtualObject*> mVOVec;


Seetang::Seetang(){
	mVOVec[0]->createVirtualObject(RESOURCES_PATH "/sphere.obj", VirtualObjectFactory::SPHERE, 1.0, 8);
	mVOVec[0].addSphere(1.0,x,y,z,0.0);
	mVOVec[0]->setDamping(5,100);
	mVOVec[0]->setSleepingThresholds(1,1);
	mVOVec[0]->applyForce(btVector3(0,0,0),btVector3(0,0,0));

}

//VirtualObject SetUpGroundTarget(){
//
//
//return 0;
//}

VirtualObject SetUpFurtherTarget(){
	for (int i = 1; i < 5; i++) {
		mVOVec[i].addSphere(1.0,x,y+5.0,z,1.0);
		y+=5.0;
		mVOVec[i]->setDamping(-3,100);
		mVOVec[i]->setSleepingThresholds(1,1);
		mVOVec[i]->applyForce(btVector3(0,5,0),btVector3(0,0,0));
		//TODO Constraint später einbauen/benutzen
	}

return 0;
}








