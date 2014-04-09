#include "HUDElement.h"

using namespace std;

	HUDElement::HUDElement(glm::vec3 pos){
		position = pos;
	}

	HUDElement::~HUDElement(){
	}

	void HUDElement::setPosition(glm::vec3 pos){
		position = pos;
	}

	glm::vec3 HUDElement::getPosition(){
		return position;
	}
