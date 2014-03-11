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
VirtualObject* mSphere;
GraphicsComponent* mScreenFillTriangle;


//---------------MEMBER FUNCTIONS--------------------
public:
enum BodyType {CUBE, SPHERE, PLANE, OTHER};

VirtualObject* createNonAssimpVO();
VirtualObject* createNonAssimpSphere();
GraphicsComponent* getTriangle();

VirtualObject* createVirtualObject();
VirtualObject* createVirtualObject(std::string filename, BodyType bodyType = OTHER, float mass = 0.0f);
VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
VirtualObject* copyVirtualObject(VirtualObject vo);




private:

void set_float4(float f[4], float a, float b, float c, float d);
void color4_to_float4(const aiColor4D *c, float f[4]);
};

#endif /* VIRTUALOBJECTFACTORY_H_ */
