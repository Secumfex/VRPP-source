#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <list>
#include "Listener.h"

using namespace std;

/** \brief a class which is able to attach and call listeners
 *
 */
class Subject{

public:
	/** \brief method to subscribe to the subject
	 *
	 * @param listener
	 */
	void attach(Listener* listener);

	/** \brief method to "de-subscribe" a listener
	 *
	 * @param listener
	 */
	void detach(Listener* listener);

	/** \brief this method sends the updates to the attached listeners
	 *
	 */
	void notify();

	/** \brief method to notify specific listeners
	 *
	 * @param name
	 */
	void notify(string name);
private:

protected:
	list<Listener*> listeners;	/**<  list of all listeners attached to the Subject */
	/** \brief protected-constructor so the class becomes abstract
	 *
	 */
	Subject() {};
};

#endif /* SUBJECT_H_ */
