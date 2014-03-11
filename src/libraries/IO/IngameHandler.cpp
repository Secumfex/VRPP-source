#include "IngameHandler.h"

#include <iostream>

IngameHandler::IngameHandler(){

}

IngameHandler::~IngameHandler(){

}

void IngameHandler::setOrientation(GLFWwindow* window, double xpos, double ypos){
	int Width, Height;
		glfwGetWindowSize(window, &Width, &Height);

		if (xPos == -1 && yPos == -1){	//has never been called before
			xPos = Width/2;
			yPos = Height/2;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	    }
	    else{	// has been called before --> mouse somewhere around middle of window and hidden
		    float gotPhi 	= camObject->getPhi();
		    float gotTheta 	= camObject->getTheta();
		    camObject->setPhi(	gotPhi 		+ mouseSpeed * float(Width / 2 - xpos));			//Horizontal
		    camObject->setTheta(gotTheta 	+ mouseSpeed * float(Height / 2 - ypos));		//Vertikal
		}
		glfwSetCursorPos(window, Width/2, Height/2);

}


void IngameHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
			glm::vec3 gotPosition = camObject->getPosition();

			// Move forward
			if (key == GLFW_KEY_W && action == GLFW_PRESS){
				camObject->setSpeedForward(speed_movement);

			}

			// Move backward
			if (key == GLFW_KEY_S && action == GLFW_PRESS){
				camObject->setSpeedForward(-speed_movement);

			}

			// Strafe right
			if (key == GLFW_KEY_D && action == GLFW_PRESS){
				camObject->setSpeedRight(speed_movement);

			}

			// Strafe left
			if (key == GLFW_KEY_A && action == GLFW_PRESS){
				camObject->setSpeedRight(-speed_movement);

			}

			if (key == GLFW_KEY_W && action == GLFW_RELEASE){
				camObject->setSpeedForward(0.0);
			}

			if (key == GLFW_KEY_S && action == GLFW_RELEASE){
				camObject->setSpeedForward(0.0);
			}

			if (key == GLFW_KEY_D && action == GLFW_RELEASE){
				camObject->setSpeedRight(0.0);
			}

			if (key == GLFW_KEY_A && action == GLFW_RELEASE){
				camObject->setSpeedRight(0.0);
			}

			// Fast movement
			if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS){
				float currentSpeedRight = camObject->getSpeedRight();
				float currentSpeedForward = camObject->getSpeedForward();
				camObject->setSpeedRight(currentSpeedRight*speed);
				camObject->setSpeedForward(currentSpeedForward*speed);
				float cam =camObject->getSpeedForward();

			}
			if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE){
				float currentSpeedRight = camObject->getSpeedRight();
				float currentSpeedForward = camObject->getSpeedForward();
				camObject->setSpeedRight(currentSpeedRight/speed);
				camObject->setSpeedForward(currentSpeedForward/speed);
				float cam =camObject->getSpeedForward();
			}
			if (action != GLFW_RELEASE){	// 	so listeners are only called on pess event, not on release ( i.e. twice )
					notify(key);				//	notify listeners
				}
		}


void IngameHandler::mouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	if(action == GLFW_PRESS){

		glm::vec3 from = camObject->getPosition();
		from += camObject->getViewDirection() * 0.6f;
		glm::vec3 to = from + camObject->getViewDirection()*1000.0f;
		
		selectionHandler->trySelection(from, to);

		std::cout<<selectionHandler->somethingIsSelected()<< " , " << selectionHandler->getCurrentSelection() << std::endl;
	}
	IOHandler::mouseButton_callback(window,button,action,mods);
}