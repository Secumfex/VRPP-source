#include "../Feature_Fauna/Seetang.h"
#include "../IO/Camera.h"

#ifndef CATMULLROMESPLINE_H_
#define CATMULLROMESPLINE_H_

class CatmullRomeSpline{
private:

	Seetang* Seetangstrang;		//Koordinaten vom Seetang, bestehend aus 4 Kugeln
	glm::mat4 mViewMatrix;

public:
	CatmullRomeSpline();
	~CatmullRomeSpline();
	glm::mat4 getViewMatrix();
	//void MVMultiplikation(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4);
	//void Spline(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4);
	void Value();

};



#endif /* CATMULLROMESPLINE_H_ */
