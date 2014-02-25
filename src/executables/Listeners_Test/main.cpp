#include <iostream>
#include <string.h>

#include "SomeListeners.h"
#include "Tools/UtilityListeners.h"
#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/RenderManager.h"

#include <typeinfo>
void testAnimateClearColor(){
	//configure minimal app
	Application* myApp = Application::getInstance();
	myApp->addState(new VRState());
	myApp->attachListenerOnProgramInitialization(new PrintMessageListener(string("Application is booting")));
	myApp->attachListenerOnProgramTermination(new PrintMessageListener(string("Application is terminating")));

	RenderManager* rm = RenderManager::getInstance();

	//register AnimateClearColorListener as Framelistener
	rm->attachListenerOnNewFrame(new AnimateClearColorListener());

	//boot Application with custom configuration 
	myApp->run();
}

using namespace std;
#include <iostream>

int main() {
int input = 0;
	cout << "Zahl eingeben für testprogramm:"<< endl;
	cout << "	1: Test AnimateClearColorListener (WARNING: may explode)"<< endl;
	cout << "	2: Test simple Listeners"<< endl;
//	cout << "	3: "<<endl;
//	cout << "	4: "<<endl;

	cin >> input;

	switch(input){
		case 1:
			testAnimateClearColor();
			break;
		case 2: 
			cout << "not yet implemented..."<<endl;
	}

	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Endlosschleife, damit das Fenster aufbleibt*/
	int terminate;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
};
