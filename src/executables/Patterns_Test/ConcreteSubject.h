/*
 * ConcreteSubject.h
 *
 *  Created on: 16.11.2013
 *      Author: Batsi
 */

#ifndef CONCRETESUBJECT_H_
#define CONCRETESUBJECT_H_
#include <Patterns/Subject.h>
#include <string>

using namespace std;
/// a simple Subject class, for testing purposes only
class ConcreteSubject : public Subject {
private:
	string data;

public:

	void setData (string _data);
	string getData();
	ConcreteSubject();
};

#endif /* CONCRETESUBJECT_H_ */
