#include "CatmullRomeSpline.h"
#include <iostream>
using namespace std;


CatmullRomeSpline::CatmullRomeSpline(){

	float Tk = 0.5;				 				//Krümmungsvariable der Kurve
	float Ab = 0.1;								//Abstandsvariable im Spline
	int RV0 = 0;								//Richtungsvektoren zum Vertexziehen
	int RV1 = 1;
}

CatmullRomeSpline::~CatmullRomeSpline(){}

glm::mat4 CatmullRomeSpline::getViewMatrix(){
	//mViewMatrix = Camera::getViewMatrix();
	return mViewMatrix;
}

void CatmullRomeSpline::MVMultiplikation(){
	//btRigidBody *= mViewMatrix;
	//cout<<btRigidBody;
}

//void CatmullRomeSpline::Spline(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4){


//}

void CatmullRomeSpline::Value(){

}
