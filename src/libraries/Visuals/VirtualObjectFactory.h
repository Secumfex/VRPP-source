/*
 * VirtualObjectFactory.h
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#ifndef VIRTUALOBJECTFACTORY_H_
#define VIRTUALOBJECTFACTORY_H_

#include <Patterns/Singleton.h>
#include <Visuals/VirtualObject.h>
#include <vector>

using namespace std;

class VirtualObjectFactory : public Singleton<VirtualObjectFactory> {
	friend class Singleton<VirtualObjectFactory>;
//---------------MEMBER VARIABLES--------------------

//---------------MEMBER FUNCTIONS--------------------
public:

	static void hello();

static VirtualObject* createVirtualObject();
static VirtualObject* createVirtualObject(char* filename);
static VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
static VirtualObject* copyVirtualObject(VirtualObject vo);

};

#endif /* VIRTUALOBJECTFACTORY_H_ */
