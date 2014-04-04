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

	///constructor
	VirtualObjectFactory();

	//---------------MEMBER VARIABLES--------------------

	VirtualObject* mCube;					/**< !docu pls! */
	GraphicsComponent* mScreenFillTriangle;	/**< !docu pls! */
	Bone* mDefaultBone;
	AnimationLoop* mDefaultAnimation;


	//---------------MEMBER FUNCTIONS--------------------
public:

	enum BodyType {CUBE, SPHERE, PLANE, OTHER};	/**< possible body types of a virtual object */

	/** \brief
	 *
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return mCube
	 */
	VirtualObject* createNonAssimpVO(float mass = 0.0f);

	/** \brief getter
	 *
	 * @return
	 */
	GraphicsComponent* getTriangle();


	/** \brief create default VO
	 *
	 * @return virtual object
	 */
	VirtualObject* createVirtualObject();

	/** \brief create VO
	 *
	 * @param filename
	 * @param bodyType
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return virtual object
	 */
	VirtualObject* createVirtualObject(std::string filename, BodyType bodyType = OTHER, float mass = 0.0f);

	/** \brief create VO
	 *  @param graphcomps vector of graphic component
	 * @return virtual object
	 */
	VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);

	/** \brief !docu pls!
	 *
	 * @param vo
	 * @return virtual object
	 */
	VirtualObject* copyVirtualObject(VirtualObject vo);




private:
	/** \brief setter
	 *
	 * @param f[4]
	 * @param a,b,c,d
	 */
	void set_float4(float f[4], float a, float b, float c, float d);

	/** \brief !docu pls!
	 *
	 * @param c
	 * @param f[4]
	 */
	void color4_to_float4(const aiColor4D *c, float f[4]);

	bool checkIfBlender(std::string filename);

	AnimationLoop* makeAnimation(map<std::string, Bone*> bones, const aiScene* pScene);

	vector<Node*> getNodeChildren(aiNode* node);


	void setBones(Node* node, map<std::string, Bone*> bones);

	void setNodeTransform(Node* node, aiNodeAnim* nodeanim);

};

#endif /* VIRTUALOBJECTFACTORY_H_ */
