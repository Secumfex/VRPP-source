#ifndef LISTENERS_H
#define LISTENERS_H

///This Header contains various general purpose Listeners

#include <Patterns/Listener.h>
#include <string.h>

///PrintMessageListener prints a predefined message on the console when notified
class PrintMessageListener : public Listener{
private: 
	std::string message;
public:
	PrintMessageListener(std::string message);
	void update();
	std::string getMessage();
	void setMessage(std::string message);
};

#endif