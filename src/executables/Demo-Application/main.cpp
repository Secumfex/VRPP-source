#include "Application/Application.h"
#include "Application/ApplicationStates.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "Tools/NoAssimpVirtualObjectFactory.h"

#include "SomeListeners.h" // until missing functionality is added

Application* myApp;

NoAssimpVirtualObjectFactory no_assimp_factory;

/**
*proposed way to work with our Libraries (?????)
*/
void configureMyApp(){

	//myApp = new Application("PROJEKT PRAKTIKUM");	//create an Application labled PROJEKT PRAKTIKUM
	myApp = Application::getInstance();


	MenuState* myMenu = new MenuState("MAINMENU");	//create a MenuState labled MAINMENU
	/*
		Button* myButton = new Button("START_BUTTON");	//create a Button labled START_BUTTON
		myButton->addListenerOnButtonPress(new SetStateListener(myApp, "LOADING_SCREEN")); //add a state changing listener to be notified upon a button press
		myMenu->addButton(myButton);	//add Button to Main Menu
	*/
	MenuState* myLoadingMenu = new MenuState("LOADING_SCREEN");	//create a MenuState labled LOADING_SCREEN
	myLoadingMenu->attachListenerOnBeginningProgramCycle(new AnimateClearColorListener());
	/*
	myLoadingMenu->addLoadingFinishedListener(new StateChangeListener("VRSTATE"));	//add a state changing listener to be notified upon the end of loading
	*/
	VRState* myVRState = new VRState("VRSTATE"); //create a VRState labled VRSTATE
	/*
		 = new VirtualObject("cube.obj");	//create a Virtual Object by reading an .obj file
		myVRState->addVirtualObject(myCubeObject);	//add the Virtual Object to VRState
	*/

	myVRState->attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));
	myVRState->attachListenerOnActivation(new SetClearColorListener(0.2,0.2,8.0));

	VirtualObject* myCowObject = myVRState->createVirtualObject(RESOURCES_PATH "/cow.obj");	
	//	VirtualObject* myCubeObject = no_assimp_factory.createCubeObject();
	//	myVRState->addVirtualObject(myCubeObject);
	/*
		VirtualObjectFactory aufrufen
			Create VBO
			reate bounding box
			add to Physicsworld singleton
		gewonnenes Object in eigene RenderQueue hinzufügen
	*/

	myApp->attachListenerOnProgramInitialization(new PrintMessageListener(string("Application is booting")));
	myApp->attachListenerOnProgramTermination(new PrintMessageListener(string("Application is terminating")));
	myApp->attachListenerOnStateChange( new PrintCurrentStateListener(myApp) );

	myApp->attachListenerOnBeginningProgramCycle(new TimedTriggerListener(new SetStateListener(myApp, "LOADING_SCREEN"), 2500.0));
	myApp->attachListenerOnBeginningProgramCycle(new TimedTriggerListener(new SetStateListener(myApp, "VRSTATE"), 5000.0));

	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(new AlternativeRenderloopListener());

	


	myApp->addState(myMenu);	//add the Main Menu to Application
	myApp->addState(myLoadingMenu);	//add the Loading Screen to Application
	myApp->addState(myVRState);	//add the VR State to Application

	myApp->setState("MAINMENU"); //set initial state to the state labled MAINMENU
}

int main() {
	configureMyApp();

	myApp->run();

	std::cout<<"_____________________________"<<std::endl;
	////////////////////////////////////////////////////////////////////////////////

	return 0;
}
