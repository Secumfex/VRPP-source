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

class ConcreteSubject {
	void Subject::attach(Listener* listener){
		listeners.push_back(listener);
	}

	void Subject::detach(Listener* listener){
		listeners.remove(listener);
	}

	void Subject::notify(){
		list<Listener*>::iterator i = listeners.begin();
		for ( ; i != listeners.end(); i++){
			(*i)->update();
		}
	}
};

#endif /* CONCRETESUBJECT_CPP_ */
