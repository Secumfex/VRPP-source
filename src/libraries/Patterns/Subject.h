#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <list>
#include "Listener.h"

using namespace std;

class Subject{

public:
	void attach(Listener* listener); //method to subscribe to the subject

	void detach(Listener* listener); 	//method to "de-subscribe" a listener

	void notify();		//this method sends the updates to the attached listeners

	void notify(string name); 	//method to notify specific listeners
private:
	list<Listener*> listeners;	//list of all listeners attached to the Subject

protected:
	Subject() {};	//protected-constructor so the class becomes abstract
};

#endif /* SUBJECT_H_ */
