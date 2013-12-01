#include <iostream>
#include <string.h>

#include "Patterns/Singleton.h"
#include "Patterns/ConcreteListener.h"
#include "Patterns/ConcreteSubject.h"
#include "Application/Application.h"
#include "Visuals/RenderManager.h"

//Test Executable, die das Singleton Pattern und Listener / Subject Pattern testet 
int main() {

	////////////////////////////////////////////////////////////////////////////////
	/*Singleton Pattern - Test*/
	
	//einzige Application-Instanz ansprechen und Status ändern
	Application* app = Application::getInstance();
	app->setState(new VRState());

	std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;

	//einzige Application-Instanz ansprechen
	RenderManager* rm1 = RenderManager::getInstance();
	std::cout<<"The RenderManager address in pointer 1 is: " << rm1 <<std::endl;
	RenderManager* rm2 = RenderManager::getInstance();
	std::cout<<"The RenderManager address in pointer 2 is: " << rm2 <<std::endl;

	std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;

	//einzige ConcreteSingleton-Instanz ansprechen und spezifische Methode aufrufen
	ConcreteSingleton::getInstance()->helloWorld();

	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Listener / Subject Pattern - Test*/

	//create a subject
	ConcreteSubject* s = new ConcreteSubject();

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

	//change the subjects data for one last time
	s->setData("neue Werte, die nur für den Concrete Listener_2 relevant sind");
	//notify specific listener 2
	s->notify("Concrete Listener_2");

	////////////////////////////////////////////////////////////////////////////////
	/*Endlosschleife, damit das Fenster aufbleibt, wenn man nicht aus Eclipse startet oder so*/
	int terminate;
	std::cout<<"_____________________________"<<std::endl;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
	return 0;
};
