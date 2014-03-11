/*
 * ConcreteListener.h
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */

#ifndef CONCRETELISTENER_H_
#define CONCRETELISTENER_H_
#include <string>
#include <Patterns/Listener.h>

class ConcreteSubject;

using namespace std;

/// a basic Listener which reads ConcreteSubjects' data info, for testing purposes only
class ConcreteListener : public Listener {

private:
	string name;
	string listenerState;
	ConcreteSubject* subject;

public:
	void update();
	void setSubject(ConcreteSubject* sub);
	ConcreteSubject* getSubject();
	ConcreteListener (ConcreteSubject* sub, string name);
};

#endif /* CONCRETELISTENER_H_ */
