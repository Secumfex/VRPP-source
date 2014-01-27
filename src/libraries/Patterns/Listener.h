#ifndef LISTENER_H
#define LISTENER_H
#include <string>

using namespace std;

/*! @brief Listener is the super  class of more specific listeners.
 *
 *	...more specific listeners can communicate changes in the objects they listen to.
 */
class Listener{
private:
	string name;

public:
	virtual ~Listener(){}			//!< destructor
	virtual void update() = 0;		//!< abstract method which must be defined by every concrete Listener class
	string getName();				//!< returns the name of the listener. It works like a key to be addressable
	void setName(string name);		//!< sets the name of the listener that works like a key to be addressable
};

#endif
