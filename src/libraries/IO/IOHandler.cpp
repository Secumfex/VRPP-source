#include "IOHandler.h"
#include <iostream>

IOHandler::IOHandler(){
	/* @todo	implement state check and change
	 * 			discuss if implement here or get from Rendermanager -> initialFoV = 45.0f;
	 */
	isMenuState = false;
	camObject = new Camera();
	xPos = -1;
	yPos = -1;

	selectionHandler = new SelectionHandler();
	//	glfwGetCursorPos(window, &xPos, &yPos);
	// Get mouse position
}

IOHandler::~IOHandler(){

}



// Compute new orientation
void IOHandler::setOrientation(GLFWwindow* window, double xpos, double ypos){
	
}

void IOHandler::cursorPos_callback(GLFWwindow* window, int xpos, int ypos){
	setOrientation(window, xpos, ypos);

	Subject::notify( "CURSOR_POS_CALLBACK_LISTENER" );
}

void IOHandler::mouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS){
		notify( button );		//notify button press listener
	}	
}

void IOHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE){	// 	so listeners are only called on pess event, not on release ( i.e. twice )
		notify(key);				//	notify listeners
	}
}

void IOHandler::setCameraObject(Camera* camera){
	camObject = camera;
}

Camera* IOHandler::getCameraObject(){
	return camObject;
}

void IOHandler::setSelectionHandler(SelectionHandler* selectionHandler){
	this->selectionHandler = selectionHandler;
}

SelectionHandler* IOHandler::getSelectionHandler(){
	return selectionHandler;
}

glm::mat4 IOHandler::getViewMatrix(){
	return mViewMatrix;
}

void IOHandler::attachListenerOnKeyPress(Listener* listener, int key){
	sstream	<<	key;	// convert int to string
	listener->setName( sstream.str()	);
	attach(listener);
	sstream.str("");	// clear stringstream
	sstream.clear();
}

void IOHandler::notify(int key){
	sstream << key;		// convert int to string
	Subject :: notify( sstream.str() );
	sstream.str("");	// clear stringstream
	sstream.clear();
}

void IOHandler::attachListenerOnMouseButtonPress(Listener* listener, int button){
	sstream	<<	button;	// convert int to string
	listener->setName( sstream.str()	);
	attach(listener);
	sstream.str("");	// clear stringstream
	sstream.clear();
}

void IOHandler::attachListenerOnCursorPosCallback(Listener* listener){
	listener->setName( "CURSOR_POS_CALLBACK_LISTENER");
	attach(listener);
}
