#include <iostream>
#include <string.h>

#include "Visuals/RenderManager.h"
#include "Patterns/Listener.h"
#include "Patterns/ConcreteListener.h"

//Test if the RenderManager is being accessed properly
int main() {

	RenderManager* rm = RenderManager::getInstance();
	ConcreteSubject* s = rm;
	std::cout<<"RenderManager is now a ConcreteSubject."<<std::endl;

	//create some listeners listening to the subject
	ConcreteListener* cl1 = new ConcreteListener(s,"Concrete Listener_1");
	ConcreteListener* cl2 = new ConcreteListener(s,"Concrete Listener_2");
	ConcreteListener* cl3 = new ConcreteListener(s,"Concrete Listener_3");

	//attach some listeners to the subject
	s->attach(cl1);
	s->attach(cl2);
	s->attach(cl3);

	//change the subjects data
	s->setData("neue Werte");
	//notify all listeners of the changes
	s->notify();

	//change the subjects data
	s->setData("voellig andere Werte");
	//notify all listeners of the changes
	s->notify();

	std::cout<<"Testing if RenderManager rm and ConcreteSubject s have the same address:"<<std::endl;
	std::cout<<s<<std::endl;
	std::cout<<rm<<std::endl;

	rm->renderLoop();

	return 0;
};
