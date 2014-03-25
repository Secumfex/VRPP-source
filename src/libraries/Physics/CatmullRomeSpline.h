#include "../Feature_Fauna/Seetang.h"

#ifndef CATMULLROMESPLINE_H_
#define CATMULLROMESPLINE_H_

class CatmullRomeSpline{
private:
	Seetang*  Seetang;		//Koordinaten vom Seetang, bestehend aus 4 Kugeln
public:
	void MVMultiplikation();
	void Position();
	void Value();

};



#endif /* CATMULLROMESPLINE_H_ */
