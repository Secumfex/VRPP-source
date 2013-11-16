#ifndef LISTENER_H
#define LISTENER_H
//TODO Basti ist das so in etwa Richtig? Gerne nach dem URL Diagramm aus deinen Folien anpassen <3
//Nich ganz, das interface für den Listener ist sogar noch viel einfacher :)
//Ich werde die Klassen einzeln packen, das macht die Wartung und Übersicht etwas leichter wie ich finde

class Listener{
protected:
	virtual void update() = 0;
};

#endif
