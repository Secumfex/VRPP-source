#ifndef LISTENERS_H
#define LISTENERS_H

/// This Header contains various general purpose Listeners

#include <Patterns/Listener.h>
#include <string.h>
#include <time.h>


/// PrintMessageListener prints a predefined message on the console when notified
class PrintMessageListener : public Listener{
private: 
	std::string message;
public:
	PrintMessageListener(std::string message);
	void update();
	std::string getMessage();
	void setMessage(std::string message);
};

class StateMachine;
/// Prints the name of the current state of the state machine
class PrintCurrentStateListener : public Listener{
private:
	StateMachine* stateMachine;
public:
	PrintCurrentStateListener(StateMachine* stateMachine);
	void update();
};

/// TimedTriggerListener will call another listener after being called after a set amount of time
class TimedTriggerListener : public Listener{
private:
	Listener* target;
	float milliseconds; //!< set time before target may be called
	float current_time; //!< time since first call
	bool running;	//!< true after the first update() call
	bool listener_triggered;	//!< true after time is greater than 
	clock_t last_clock_call;
public:
	TimedTriggerListener(Listener* target, float milliseconds);
	void update();
};


#endif