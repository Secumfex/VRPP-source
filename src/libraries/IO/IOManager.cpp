	/*
	 * @author Sanèr, Oliver
	 */

#include "IOManager.h"

void IOManager::bindCallbackFuncs(){
	if (window != 0){
		glfwSetKeyCallback(window, staticKey_callback);
		glfwSetCursorPosCallback(window, staticCursorPos_callback);
		glfwSetMouseButtonCallback(window, staticMouseButton_callback);
	}
}

void IOManager::staticKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	IOManager::getInstance()->key_callback(window,key,scancode,action,mods);
}	 

void IOManager::staticCursorPos_callback(GLFWwindow* window, double xpos, double ypos){
	IOManager::getInstance()->cursorPos_callback(window, xpos, ypos);
}

void IOManager::staticMouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	IOManager::getInstance()->mouseButton_callback(window, button, action, mods);
}

void IOManager::cursorPos_callback(GLFWwindow* window, double xpos, double ypos){
	// save current mouse cursor position
	xPos = xpos;
	yPos = ypos;

	// @todo call IOHandler cursorPos func
	// if (currentIOHandler != 0){
	// 	currentIOHandler->cursorPos_callback(window, xpos, ypos);
	// }
}

void IOManager::mouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	// @todo call IOHandler mouseButton func
	// if (currentIOHandler != 0){
	// 	currentIOHandler->mouseButton_callback(window, xpos, ypos);
	// }
}

void IOManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	if (currentIOHandler != 0){
		currentIOHandler->key_callback(window, key, scancode, action, mods);
	}
}

IOManager::IOManager(){
	currentIOHandler 	= 0;
	window 				= 0;
	deltaTime 			= 0.1f; //default deltaTime value: 100ms
	lastTime 			= 0.0f;

	WIDTH 	= 0;
	HEIGHT 	= 0;
}

void IOManager::setWindow(GLFWwindow* window){
	this->window = window;

	glfwGetWindowSize(window, &WIDTH, &HEIGHT);
}

void IOManager::computeFrameTimeDifference(){
	if (window != 0){
		if (lastTime 	= 0.0f){ 			// if glfwGetTime() has never been called before	
			lastTime 	= glfwGetTime();	// last time is current time
			deltaTime 	= 0.1f;				// time since last call is assumed 100ms 
		}
		else{	// Compute time difference between current and last frame	
			currentTime = glfwGetTime();	// get current time
			deltaTime 	= float(currentTime - lastTime);	//compute time difference since last call
			lastTime = currentTime;			// save current time for next call
		}
	}
}

float IOManager::getDeltaTime(){
	return deltaTime;
}

float IOManager::getLastTime(){
	return lastTime;
}

void IOManager::setCurrentIOHandler(IOHandler* iOHandler){
	currentIOHandler = iOHandler;
}