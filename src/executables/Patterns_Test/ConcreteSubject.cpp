/*
 * ConcreteSubject.cpp
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */


#include "ConcreteSubject.h"

using namespace std;

	void ConcreteSubject::setData (string _data){
		data = _data;
	}

	string ConcreteSubject::getData(){
		return data;
	}

	ConcreteSubject::ConcreteSubject() {}

