#include <iostream>
#include <string.h>

#include "Patterns/Singleton.h"
#include "Patterns/ConcreteListener.h"
#include "Patterns/ConcreteSubject.h"
#include "Application/Application.h"
#include "Visuals/RenderManager.h"

#include <typeinfo>

void testListenerSubjectPattern(){
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

	std::cout<<"Ändere Daten des Subjects..."<<std::endl;
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
}

void testSingletonPattern(){
	//einzige Application-Instanz ansprechen und Status ändern
	Application* app = Application::getInstance();

	std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;

	//einzige RenderManager-Instanz ansprechen
	RenderManager* rm1 = RenderManager::getInstance();
	std::cout<<"The RenderManager address in pointer 1 is: " << rm1 <<std::endl;
	RenderManager* rm2 = RenderManager::getInstance();
	std::cout<<"The RenderManager address in pointer 2 is: " << rm2 <<std::endl;

	std::cout<<"- - - - - - - - - - - - - - -"<<std::endl;

	//einzige ConcreteSingleton-Instanz ansprechen und spezifische Methode aufrufen
	ConcreteSingleton::getInstance()->helloWorld();
}

void testContextStatePattern(){
	//get the current Application State
	Application* app = Application::getInstance();
	State* state = app->getState();
	if ( typeid ( *state ) == typeid( IdleState ) ) {	//it should be Idle State which is the initial Application State
		std::cout<<" The Application-State is " <<typeid(*state).name()<<" : Idle-State."<<std::endl;
	}else{										//or something odd happend along the way
		std::cout<<" The Application-State is weird to say the least..."<<std::endl;
	}

	//change the Applications State to VR-State
	std::cout<<" Trying to change Application State to VRState...  "<<std::endl;
	app->setState(new VRState());				//Try to change the state.
	state = app->getState();					//Get the new Application State
	if ( typeid ( *state ) == typeid ( VRState ) ) {		//it should be VRState, or it hasn't been changed
		std::cout<<" The new Application-State is  "<<typeid(*state).name() <<" : VR-State."<<std::endl;
	}else{
		std::cout<<" The Application-State has not been changed."<<std::endl;
	}

	//test whether you can change the Application's State from VR-State
	std::cout<<" Trying to change Application State to IdleState...  "<<std::endl;
	app->setState(new IdleState());				//Try to change the state back to Idle
	state = app->getState();
	if ( typeid ( *state ) == typeid ( VRState ) ) {		//it should be VRState, or it has been changed
		std::cout<<" The new Application-State is  :"<<typeid(*state).name() <<" : VR-State "<<std::endl;	//good
	}else{
		std::cout<<" The new Application-State is  :"<<typeid(*state).name() <<" : Idle-State, which wasn't supposed to happen"<<std::endl;	//bad
	}

}

//Test Executable, die das Singleton Pattern und Listener / Subject Pattern testet 
int main() {

	////////////////////////////////////////////////////////////////////////////////
	/*Singleton Pattern - Test*/
	testSingletonPattern();

	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Listener / Subject Pattern - Test*/
	testListenerSubjectPattern();

	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Context / State Pattern - Test*/
	testContextStatePattern();
	
	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Endlosschleife, damit das Fenster aufbleibt, wenn man nicht aus Eclipse startet oder so*/
	int terminate;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
	return 0;
};
