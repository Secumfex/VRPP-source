/*
 * VirtualObjectFactory.h
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#ifndef VIRTUALOBJECTFACTORY_H_
#define VIRTUALOBJECTFACTORY_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Patterns/Singleton.h>
#include <Visuals/VirtualObject.h>
#include "MaterialManager.h"
#include <vector>
#include <Tools/NoAssimpVirtualObjectFactory.h>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using namespace std;

/// class which creates Virtual Objects by reading 3D model files
class VirtualObjectFactory : public Singleton<VirtualObjectFactory> {
	friend class Singleton<VirtualObjectFactory>;

    VirtualObjectFactory();

//---------------MEMBER VARIABLES--------------------

VirtualObject* mCube;
GraphicsComponent* mScreenFillTriangle;


//---------------MEMBER FUNCTIONS--------------------
public:

VirtualObject* createNonAssimpVO();//creates a Cube from the NonAssimpFactory
GraphicsComponent* getTriangle();//creates a single triangle for screenfilling

VirtualObject* createVirtualObject(std::string filename, float mass = 0.0);//creates a VO from a system file with a certain mass

private:

void set_float4(float f[4], float a, float b, float c, float d);
void color4_to_float4(const aiColor4D *c, float f[4]);
};

#endif /* VIRTUALOBJECTFACTORY_H_ */
