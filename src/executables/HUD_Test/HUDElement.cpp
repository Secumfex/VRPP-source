#include "HUDElement.h"

using namespace std;

	HUDElement::HUDElement(glm::vec3 pos, glm::vec3 offset, float scale){
		position = pos;
		this->offset = offset;
		this->scale = scale;

		HUD_texture = NULL;
	}

	HUDElement::~HUDElement(){
	}

	void HUDElement::setTexture(Texture* texture){
		HUD_texture = texture;
	}

	Texture* HUDElement::getTexture(){
		return HUD_texture;
	}

	void HUDElement::setPosition(glm::vec3 pos){
		position = pos;
	}

	glm::vec3 HUDElement::getPosition(){
		return position;
	}

	void HUDElement::setOffset(glm::vec3 offset){
		this->offset = offset;
	}

	void HUDElement::setOffset(float x, float y){
		offset.x = x;
		offset.y = y;
	}

	glm::vec3 HUDElement::getOffset(){
		return offset;
	}
