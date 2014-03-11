#ifndef LISTENERS_H
#define LISTENERS_H

/// This Header contains various general purpose Listeners

#include <Patterns/Listener.h>
#include <string.h>
#include <time.h>


/// Listener which prints a predefined message on the console when notified
class PrintMessageListener : public Listener{
private: 
	std::string message;
public:
	/** \brief Constructor
	 * @param message string to be printed to the console upon update
	 */
	PrintMessageListener(std::string message);
	void update();
	std::string getMessage();
	void setMessage(std::string message);
};

class StateMachine;
/// Listener which prints the name of the current state of the state machine
class PrintCurrentStateListener : public Listener{
private:
	StateMachine* stateMachine;
public:
	/** \brief Constructor
	 * @param stateMachine state machine of interest
	 */
	PrintCurrentStateListener(StateMachine* stateMachine);
	void update();
};

/// Listener which will call another listener when called after after a set amount of time
class TimedTriggerListener : public Listener{
private:
	Listener* target;
	float milliseconds; //!< set time before target may be called
	float current_time; //!< time since first call
	bool running;	//!< true after the first update() call
	bool listener_triggered;	//!< true after time is greater than 
	clock_t last_clock_call;
public:
	/** \brief Constructor
	 * @param target pointer to the Listener supposed to be callable after a set amount of time
	 * @param milliseconds time before target listener becomes will be called upon the next update
	 */
	TimedTriggerListener(Listener* target, float milliseconds);
	void update();
};

/// Listener which prints the value pointed and print that other stuff in front of it
class PrintValueListener : public Listener{
private:
	float* value;
	std::string message;
public:

	/** \brief Constructor
	 * @param value pointer to the float variable of interest
	 * @param message string to be printed in front of it
	 */
	PrintValueListener(float* value, std::string message = "");
	void update();
};

#endif