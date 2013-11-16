#ifndef LISTENER_H
#define LISTENER_H
#include <vector>
//TODO Basti ist das so in etwa Richtig? Gerne nach dem URL Diagramm aus deinen Folien anpassen <3
//Nich ganz, das interface für den Listener ist sogar noch viel einfacher :)
class Listener{
protected:
	virtual void update() = 0;
};

#endif
