/*
 * ConcreteSubject.h
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */

#ifndef CONCRETESUBJECT_H_
#define CONCRETESUBJECT_H_
#include "Subject.h"
#include <string>

using namespace std;

class ConcreteSubject : public Subject {
private:
	string data;

public:

	void setData (string _data) {data = _data;}
	string getData() {return data;}
	ConcreteSubject() : Subject() {}
};

#endif /* CONCRETESUBJECT_H_ */
