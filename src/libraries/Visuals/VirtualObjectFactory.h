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
	GraphicsComponent* mQuad;				/**< a Quad GraphicsComponent */
	GraphicsComponent* mHalfScreenQuadLeft;	/**< a Half Screen filling Quad GraphicsComponent the left side of the screen*/
	GraphicsComponent* mHalfScreenQuadRight;	/**< a Half Screen filling Quad GraphicsComponent for the right side of the screen */
	Bone* mDefaultBone;
	AnimationLoop* mDefaultAnimation;


	//---------------MEMBER FUNCTIONS--------------------
public:

	enum BodyType {CUBE, SPHERE, PLANE, MESH, OTHER};	/**< possible body types of a virtual object */

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

	enum HalfScreen {LEFT,RIGHT};

	/** \brief getter
	 *
	 * @return
	 */
	GraphicsComponent* getHalfScreenQuad( HalfScreen side);

	/** \brief getter
	 *
	 * @return a quad
	 */
	GraphicsComponent* getQuad();


	/** \brief create default VO
	 *
	 * @return virtual object
	 */
	VirtualObject* createVirtualObject();

//	<<<<<<< HEAD
//
//			/** \brief create VO
//			 *
//			 * @param filename
//			 * @param bodyType
//			 * @param mass defines the behavior of the rigid body in the physics world
//			 * @param collisionFlag a collision flag, see PhysicsComponent constructor for reference
//			 * @param blenderAxes defines whether the file uses world_axes of Blender ( Z is up, Y is depth ), which is common in Blender exported Collada files
//			 * @return virtual object
//			 */
//			VirtualObject* createVirtualObject(std::string filename, BodyType bodyType = OTHER, float mass = 0.0f, int collisionFlag = 1, bool blenderAxes = false);
//
//	/** \brief create VO
//	 *
//	 * @param graphcomps vector of graphic component
//	 */
//	VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
//	=======
			/** \brief create VO
			 *
			 * @param filename
			 * @param bodyType
			 * @param mass defines the behavior of the rigid body in the physics world
			 * @return virtual object
			 */
			VirtualObject* createVirtualObject(std::string filename, BodyType bodyType = OTHER, float mass = 0.0f, int collisionFlag = 1, bool blenderAxes = false);

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

	/** \brief checks if a file was created in blender
	 *
	 * @param filename : the file to check
	 */
	bool checkIfBlender(std::string filename);

	/** \brief checks if a file was created in blender
	 *
	 * @param map<string, Bone*> bones : a hashmap of bones
	 * @param aiScene* pScene : the scene to extract the animation from
	 * @param bool isBlender : a bool if this scene comes from blender
	 * @return a new animation
	 */

	AnimationLoop* makeAnimation(map<std::string, Bone*> bones, const aiScene* pScene, bool isBlender);

	/** \brief makes a node hierarchy of a scene
	 *
	 * @param aiNode* node : the root node of assimps node stucture
	 * @return an array of nodes
	 */

	vector<Node*> getNodeChildren(aiNode* node);

	/** \brief inserts bones into nodes
	 *
	 * @param map<string, Bone*> bones : a hashmap of bones
	 * @param Node* node : a node from our scene graph
	 */

	void setBones(Node* node, map<std::string, Bone*> bones);

	/** \brief extracts assimps transformations and inserts them into our nodes
	 *
	 * @param Node* node : a node from our scene graph
	 * @param aiNodeAnim* nodeanim : animated nodes from assimp
	 * @param bool isBlender : a bool if this scene comes from blender
	 */

	void setNodeTransform(Node* node, aiNodeAnim* nodeanim, bool isBlender);
};

#endif /* VIRTUALOBJECTFACTORY_H_ */
