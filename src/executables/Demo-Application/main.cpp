#include "Application/Application.h"
#include "Application/ApplicationStates.h"

Application* myApp;

/**
*proposed way to work with our Libraries (?????)
*/
void initMyApp(){

//myApp = new Application("PROJEKT PRAKTIKUM");	//create an Application labled PROJEKT PRAKTIKUM
myApp = Application::getInstance();
MenuState* myMenu = new MenuState("MAINMENU");	//create a MenuState labled MAINMENU
/*
	Button* myButton = new Button("START_BUTTON");	//create a Button labled START_BUTTON
	myButton->addPressListener(new StateChangeListener(myApp, "LOADING_SCREEN")); //add a state changing listener to be notified upon a button press
myMenu->addButton(myButton);	//add Button to Main Menu
*/
MenuState* myLoadingMenu = new MenuState("LOADING_SCREEN");	//create a MenuState labled LOADING_SCREEN

/*
myLoadingMenu->addLoadingFinishedListener(new StateChangeListener("VRSTATE"));	//add a state changing listener to be notified upon the end of loading
*/
VRState* myVRState = new VRState("VRSTATE"); //create a VRState labled VRSTATE
/*
	VirtualObject* myCubeObject = new VirtualObject("cube.obj");	//create a Virtual Object by reading an .obj file
myVRState->addVirtualObject(myCubeObject);	//add the Virtual Object to VRState
*/
myApp->addState(myMenu);	//add the Main Menu to Application
myApp->addState(myLoadingMenu);	//add the Loading Screen to Application
myApp->addState(myVRState);	//add the VR State to Application
/*
myApp->setBeginState("MAINMENU"); //set initial state to the state labled MAINMENU
*/
}

int main() {
	initMyApp();
//	myApp->run();
	myApp->setState("MAINMENU");
	myApp->setState("LOADING_SCREEN");
	myApp->setState("VRSTATE");

	int terminate;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
	return 0;
}
