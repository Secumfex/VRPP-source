/*
 * ConcreteListener.cpp
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */

#include <iostream>
#include "ConcreteListener.h"

using namespace std;

void ConcreteListener::update(){
	listenerState = subject->getData();
	cout << "Listener " <<name << " has new State: "<< listenerState << endl;
}

void ConcreteListener::setSubject(ConcreteSubject* subj){
	subject = subj;
}

ConcreteSubject* ConcreteListener::getSubject(){
	return subject;
}

ConcreteListener::ConcreteListener(ConcreteSubject* s, string n){
	name= n;
	subject = s;
}
