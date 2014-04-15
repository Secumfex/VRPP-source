#include "HUDSystem.h"

HUDSystem::HUDSystem(){

}

HUDSystem::HUDSystem(std::vector<HUDElement*> hudElements){
	HUDElements = hudElements;
}

HUDSystem::~HUDSystem(){

}

void HUDSystem::addHUDElement(HUDElement* hudElement){
	HUDElements.push_back(hudElement);
}

std::vector<HUDElement*> HUDSystem::getHUDElements(){
	return HUDElements;
}
