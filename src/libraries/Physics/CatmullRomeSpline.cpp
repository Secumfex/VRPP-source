#include "CatmullRomeSpline.h"

using namespace std;

CatmullRomeSpline::CatmullRomeSpline(){
	Seetangstrang = new Seetang();
	float Tk = 0.5;				 				//Krümmungsvariable der Kurve
	float Ab = 0.1;								//Abstandsvariable im Spline
	int RV0 = 0;								//Richtungsvektoren zum Vertexziehen
	int RV1 = 1;
}

CatmullRomeSpline::~CatmullRomeSpline(){}

//void CatmullRomeSpline::MVMultiplikation(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4){
	//Sphere1*glm::mat4;
	//Sphere2*glm::mat4;
	//Sphere3*glm::mat4;
	//Sphere4*glm::mat4;
//}

//void CatmullRomeSpline::Spline(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4){


//}

void CatmullRomeSpline::Value(){

}
