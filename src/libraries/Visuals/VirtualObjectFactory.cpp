/*
 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>


VirtualObject* VirtualObjectFactory::createVirtualObject(){
	return new VirtualObject();
}
VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: filename wird im System gefunden
	//TODO: assimp Mesh incl Materialien werden erstellt und befuellt
	//TODO: Mesh und Material wird gelesen und in neuer GraphicsComponent gespeichert
	//TODO: SPÄTER: Wenn moeglich mehr als eine GraphicComponente aus einem Mesh lesen
	//TODO: GraphicsComponent(s) and virtualOBject.addGraphicComponent weitergeben.
	return virtualObject;
}
VirtualObject* VirtualObjectFactory::createVirtualObject(vector<GraphicsComponent*> graphcomps){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: alle GraphicsComponents werden an das VO übergeben

	return virtualObject;
}
VirtualObject* VirtualObjectFactory::copyVirtualObject(VirtualObject vo){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: variable wird überfuehrt

	return virtualObject;
}
