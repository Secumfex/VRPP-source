/*
 * ConcreteSubject.cpp
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */

#ifndef CONCRETESUBJECT_CPP_
#define CONCRETESUBJECT_CPP_
#include "Subject.h"
#include "Listener.h"
#include "ConcreteListener.h"

using namespace std;

	void ConcreteSubject::setData (string _data){
		data = _data;
	}

	string ConcreteSubject::getData(){
		return data;
	}

	ConcreteSubject::ConcreteSubject() : Subject() {}

#endif /* CONCRETESUBJECT_CPP_ */
