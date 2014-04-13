#include "Seetang.h"
#include "../libraries/IO/Camera.h"

#ifndef CATMULLROMESPLINE_H_
#define CATMULLROMESPLINE_H_

class CatmullRomeSpline{
private:

	glm::mat4 mViewMatrix;

public:
	CatmullRomeSpline();
	~CatmullRomeSpline();
	glm::mat4 getViewMatrix();
	void MVMultiplikation();
	//void Spline(VirtualObject* Sphere1,VirtualObject* Sphere2,VirtualObject* Sphere3,VirtualObject* Sphere4);
	void Value();

};



#endif /* CATMULLROMESPLINE_H_ */
