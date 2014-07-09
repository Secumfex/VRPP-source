/*
 * Node.h
 *
 *  Created on: 25.03.2014
 *      Author: Raphimulator
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include <Animation/Bone.h>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

class Node {

	/*! @brief Node.
	 *
	 *	a node is a piece in the tree-hierarchy of the scene-graph. it contains transformations and/or bones
	 */

public:

	/** \brief constructor
	*
	* creates a node with an array of children
	* @param  std::vector<Node*> node
	*/

	Node(std::vector<Node*> node);

	/** \brief destructor
	*
	* clears the allocated memory.
	*/

	virtual ~Node();

	/** \brief setter
	*
	* sets the Node's name.
	*
	* @param string name : new name
	*/

	void setName(std::string name);

	/** \brief setter
	*
	* sets the Node's bone.
	*
	* @param Bone* bone : new bone
	*/

	void setBone(Bone* bone);

	/** \brief setter
	*
	* sets the Node's scene transformation.
	*
	* @param glm::mat4 mat : new scene transformation
	*/

	void setNodeMatrix(glm::mat4 mat);

	/** \brief getter
	*
	* @return the node's name
	*/

	std::string getName();

	/** \brief getter
	*
	* @return the node's children
	*/

	std::vector<Node*> getChildren();

	/** \brief getter
	*
	* @return the node's bone
	*/

	Bone* getBone();

	/** \brief updates the node's children about it's parent-transformation
	 *
	 * @param float t : animation time
	 * @param mat4 parent_mat : parent's matrix
	 */

	void updateBone(float t, glm::mat4 parent_mat = glm::mat4(1.0f));

	/** \brief adds a node's transformation for a certain time
	 *
	 * @param float time : animation time
	 * @param vec3 pos : node's translation-transformation at 'time'
	 * @param vec3 scale : node's scale-transformation at 'time'
	 * @param vec3 rotation : node's rotation-transformation at 'time'
	 */

	void addTransformation(glm::vec3 pos, glm::vec3 scale, glm::quat rotation, float time);

private:
	int getTimeIndex(float t);/**< returns index for a given time period */

	Bone* mBone;/**< bone pointer */

	std::vector<float> mTimes;/**< array of time-steps */
	std::vector<glm::vec3> mPositions;/**< array of position-steps */
	std::vector<glm::vec3> mScales;/**< array of scale-steps */
	std::vector<glm::quat> mRotations;/**< array of rotation-steps */
	std::vector<Node*> mChildren;/**< array of children */
	std::string mName;/**< name */
	glm::mat4 mNodeTransform;/**< array of transformation matrices */
};

#endif /* NODE_H_ */
