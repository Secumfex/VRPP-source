#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Visuals/VirtualObjectFactory.h"

#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

#include "SomeListeners.h" // until missing functionality is added

Application* myApp;
	/*How to build your own custom Application*/
void configureMyApp(){
	/*	customize application a little bit*/
	myApp = 		Application::getInstance();	//create an Application labled PROJEKT PRAKTIKUM
	myApp->			setLabel("PROJEKT PRAKTIKUM");



	/*   create some states to work with */	
	MenuState* myMenu = 		new MenuState("MAINMENU");	//create a MenuState labled MAINMENU
	/*
		Button* myButton = new Button("START_BUTTON");	//create a Button labled START_BUTTON
		myButton->addListenerOnButtonPress(new SetStateListener(myApp, "LOADING_SCREEN")); //add a state changing listener to be notified upon a button press
		myMenu->addButton(myButton);	//add Button to Main Menu
	*/

	/*	customize myLoadingScreen */
	MenuState* myLoadingMenu = 	new MenuState("LOADING_SCREEN");	// create a MenuState labled LOADING_SCREEN
	
	VirtualObject* myLoadingBarrel = 	myLoadingMenu->		createVirtualObject(RESOURCES_PATH "/barrel.obj"); 		// create and add virtual object to loading menu state
	myLoadingBarrel->setModelMatrix(	glm::scale(			glm::mat4(1.0f), glm::vec3(1.0,0.125,1.0)));
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateSinusModelMatrixListener(myLoadingBarrel));	// animated loading barrel
	myLoadingMenu->	attachListenerOnBeginningProgramCycle(	new AnimateClearColorListener());						// animated pseudo Loading_screen

	/*	cutomize myVRState*/
	VRState* myVRState = 	new VRState("VRSTATE"); // create a VRState labled VRSTATE
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
	myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color



	/*	load some virtual objects into vr state scene*/
	VirtualObject* 	myCowObject1 = 		myVRState->			createVirtualObject(RESOURCES_PATH "/cow.obj");	 		// create a Virtual Object by reading an .obj file and add it to VRState automatically
	myVRState->		attachListenerOnBeginningProgramCycle(	new AnimateRotatingModelMatrixListener(myCowObject1));	// animate cow through listener
	
	VirtualObject* 	myCubeObject1 = 	VirtualObjectFactory::getInstance()->createVirtualObject(RESOURCES_PATH "/cube.obj");	// create a Virtual Object by using the VirtualObject-Factory and add it to VRState manually
	myVRState->		addVirtualObject(	myCubeObject1);		// add to VRState manually
	VirtualObject* 	myCubeObject2 = 	myVRState->	createVirtualObject(RESOURCES_PATH "/cube.obj");	// create another Virtual Object from the same geometry 

	/*	customize virtual objects*/
	glm::mat4		myModelMatrix1 = 	glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(2.5f, 0.2f, 2.5f));	//floor
	myCubeObject1-> setModelMatrix(		myModelMatrix1); 	// override default Model Matrix
	
	glm::mat4 myModelMatrix2 = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.5f)), glm::vec3(2.5f, 2.5f, 0.2f));	// wall
	myCubeObject2-> setModelMatrix(		myModelMatrix2);	// override default Model Matrix



	/*	further customize application functionality by adding various listeners */
	myApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	myApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
	myApp->attachListenerOnStateChange( 			new PrintCurrentStateListener(	myApp) );

	myApp->attachListenerOnBeginningProgramCycle(	new TimedTriggerListener(		new SetStateListener(myApp, "LOADING_SCREEN"), 	2500.0)); //	Use Listeners to change states
	myApp->attachListenerOnBeginningProgramCycle(	new TimedTriggerListener(		new SetStateListener(myApp, "VRSTATE"), 		5000.0));

	// attach a listener which overrides the rendermanager's current Shader
	myApp->attachListenerOnProgramInitialization(	new SetAlternativeDefaultRenderManagerPointersListener());
	// attach a listener which serves as renderloop by using the rendermanagers current RenderQueue and Shader
	myApp->attachListenerOnRenderManagerFrameLoop(	new AlternativeRenderloopListener());

	

	/*	add customized states to application state pool*/
	myApp->addState(	myMenu);		//add the Main Menu to Application
	myApp->addState(	myLoadingMenu);	//add the Loading Screen to Application
	myApp->addState(	myVRState);		//add the VR State to Application

	myApp->setState(	"MAINMENU"); 	//set initial state to the state labled MAINMENU
}

int main() {
	configureMyApp();		// 1 do some customization

	myApp->run();			// 2 run application

	return 0;				// 3 end :)
}
