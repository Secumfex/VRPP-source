#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "State.h"
#include <map>
#include <list>

/** \brief State Machine enabled classes can add and remove states, switch between states and forbid state transitions
 *
 */
class StateMachine {
friend class State;

protected:
	State* currentState;	/**< !docu pls! */

private:
	std::map<std::string, State*> states;								/**< !docu pls! */
	std::list< std::pair< State*, State*> > stateTransitionConstraints;	/**< contains allowed state changes as a pair <FROM, TO> */

public:

	/** \brief destructor
	 *
	 */
	virtual ~StateMachine();

	/** \brief constructor
	 *
	 */
	StateMachine();

	/** \brief setter
	 *
	 * attempt to change state
	 * @param state state as State reference
	 */
	virtual bool setState(State* 		state);

	/** \brief setter
	 *
	 * attempt to change state
	 * @param state state as string
	 */
	virtual bool setState(std::string 	state);

	/** \brief add new state to states pool
	 *
	 * @param state
	 */
	virtual void addState(State* 		state);

	/** \brief getter
	 *
	 * get current state
	 * @return currentState
	 */
	State* getState();

	/** \brief getter
	 *
	 * get current state
	 * @return currentState
	 */
	State* getCurrentState();

	/** \brief getter
	 *
	 * @return states
	 */
	std::map  <std::string, State* > getStatesMap() ; 

	/** \brief getter
	 *
	 * get list of all possible states
	 * @return list of states
	 */
	std::list <State* 			   > getStatesList();

	/** \brief removes pair <FROM, TO> from stateTransitionConstraints if existing
	 *
	 * @param from,to
	 */
	void forbidStateTransitionFromTo(State* 	 from, State*  	   to);

	/** \brief removes pair <FROM, TO> from stateTransitionConstraints if existing
	 *
	 * @param from,to
	 */
	void forbidStateTransitionFromTo(std::string from, std::string to);

	/** \brief adds pair <FROM, TO> to stateTransitionConstraints if not existing
	 *
	 * @param from,to
	 */
	void allowStateTransitionFromTo (State* 	 from, State*  	   to);

	/** \brief adds pair <FROM, TO> to stateTransitionConstraints if not existing
	 *
	 * @param from,to
	 */
	void allowStateTransitionFromTo (std::string from, std::string to);

	/** \brief removes all pairs < ... , TO> from stateTransitionConstraints
	 *
	 * @param to
	 */
	void forbidAllStateTransitionsTo(State* to);

	/** \brief removes all pairs <FROM, ...> from stateTransitionConstraints
	 *
	 * @param from
	 */
	void forbidAllStateTransitionsFrom(State* from);

	/** \brief add pairs <FROM, TO> for every existing state
	 *
	 * @param to
	 */
	void allowAllStateTransitionsTo (State*  	   to);

	/** \brief checks whether it is allowed to transition to comitted State from active state
	 *
	 * @param to
	 * @return true if allowed, false if not
	 */
	bool checkStateTransitionConstraint(std::string to);

	/** \brief checks whether it is allowed to transition to comitted State from active state
	 *
	 * @param to
	 * @return true if allowed, false if not
	 */
	bool checkStateTransitionConstraint(State* to);
 };

#endif /* STATEMACHINE_H_ */
