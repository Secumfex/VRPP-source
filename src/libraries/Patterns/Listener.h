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
	/** \brief destructor
	 *
	 */
	virtual ~Listener(){}

	/** \brief abstract method which must be defined by every concrete Listener class
	 *
	 */
	virtual void update() = 0;

	/** \brief getter
	 *
	 * returns the name of the listener. It works like a key to be addressable
	 * @return name (string)
	 */
	string getName();

	/** \brief setter
	 *
	 * sets the name of the listener that works like a key to be addressable
	 * @param name
	 */
	void setName(string name);
};

#endif
