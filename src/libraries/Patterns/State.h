#ifndef STATE_H
#define STATE_H

#include <string>
#include "Subject.h"

class State : public Subject{	//a state of a context

protected:

private:
	std::string name;	/**< !docu pls! */

public:
	/** \brief destructor
	 *
	 */
	virtual ~State(){};

	/** \brief constructor
	 *
	 * @param name
	 */
	State(std::string name = "");

	/** \brief getter
	 *
	 * @return name
	 */
	std::string getName();

	/** \brief setter
	 *
	 * @param name
	 */
	void setName(std::string name);

	/** \brief !docu pls!
	 *
	 */
	virtual void activate();
};

#endif
