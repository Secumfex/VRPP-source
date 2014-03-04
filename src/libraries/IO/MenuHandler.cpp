#include "MenuHandler.h"

MenuHandler::MenuHandler(){


}
MenuHandler::~MenuHandler(){


}

void MenuHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

}
void MenuHandler::setOrientation(GLFWwindow* window, double xpos, double ypos){
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
