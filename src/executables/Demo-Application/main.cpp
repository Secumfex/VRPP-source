/*#include "Application/Application.h"
#include "Application/ApplicationStates.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

Application* myApp;

/**
*proposed way to work with our Libraries (?????)
*/
/*void configureMyApp(){

	//myApp = new Application("PROJEKT PRAKTIKUM");	//create an Application labled PROJEKT PRAKTIKUM
	myApp = Application::getInstance();


	MenuState* myMenu = new MenuState("MAINMENU");	//create a MenuState labled MAINMENU
	/*
		Button* myButton = new Button("START_BUTTON");	//create a Button labled START_BUTTON
		myButton->addListenerOnButtonPress(new SetStateListener(myApp, "LOADING_SCREEN")); //add a state changing listener to be notified upon a button press
		myMenu->addButton(myButton);	//add Button to Main Menu
	*/
	/*MenuState* myLoadingMenu = new MenuState("LOADING_SCREEN");	//create a MenuState labled LOADING_SCREEN

	/*
	myLoadingMenu->addLoadingFinishedListener(new StateChangeListener("VRSTATE"));	//add a state changing listener to be notified upon the end of loading
	*/
	/*VRState* myVRState = new VRState("VRSTATE"); //create a VRState labled VRSTATE
	/*
		 = new VirtualObject("cube.obj");	//create a Virtual Object by reading an .obj file
		myVRState->addVirtualObject(myCubeObject);	//add the Virtual Object to VRState
	*/

	/*VirtualObject* myCubeObject = myVRState->createVirtualObject(RESOURCES_PATH "/barrel.obj");	

	/*
		VirtualObjectFactory aufrufen
			Create VBO
			reate bounding box
			add to Physicsworld singleton
		gewonnenes Object in eigene RenderQueue hinzufügen
	*/

	/*myApp->attachListenerOnProgramInitialization(new PrintMessageListener(string("Application is booting")));
	myApp->attachListenerOnProgramTermination(new PrintMessageListener(string("Application is terminating")));
	myApp->attachListenerOnStateChange( new PrintCurrentStateListener(myApp) );

	myApp->attachListenerOnBeginningProgramCycle(new TimedTriggerListener(new SetStateListener(myApp, "LOADING_SCREEN"), 5000.0));
	myApp->attachListenerOnBeginningProgramCycle(new TimedTriggerListener(new SetStateListener(myApp, "VRSTATE"), 10000.0));

	myApp->addState(myMenu);	//add the Main Menu to Application
	myApp->addState(myLoadingMenu);	//add the Loading Screen to Application
	myApp->addState(myVRState);	//add the VR State to Application

	myApp->setState("MAINMENU"); //set initial state to the state labled MAINMENU
}

int main() {
	configureMyApp();

	myApp->run();
	myApp->setState("MAINMENU");
	myApp->setState("LOADING_SCREEN");
	myApp->setState("VRSTATE");

	std::cout<<"_____________________________"<<std::endl;
	////////////////////////////////////////////////////////////////////////////////
	int terminate;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
	return 0;
}
*/