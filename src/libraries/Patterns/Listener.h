#ifndef LISTENER_H
#define LISTENER_H
#include <vector>
//TODO Basti ist das so in etwa Richtig? Gerne nach dem URL Diagramm aus deinen Folien anpassen <3
class Listener{
protected:
	virtual void call();
};

class Subject{
protected:
	std::vector<Listener*> listeners;

	void addListener(Listener* listener);
	void removeListener(Listener* listener);
	void callListeners();
};

#endif
