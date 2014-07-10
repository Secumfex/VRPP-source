/*
 * AnimationLoop.h
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#ifndef ANIMATIONLOOP_H_
#define ANIMATIONLOOP_H_

#include <Animation/Bone.h>
#include <Animation/Node.h>
#include <vector>

	/*! @brief AnimationLoop.
	 *
	 *	a this animation loop is a domain for the scene graph and its bones. the animation loop updates the node and manages time input.
	 */

class AnimationLoop {
public:

	/** \brief constructor
	*
	* Default constructor with no values.
	*/

	AnimationLoop();

	/** \brief constructor
	 *
	 *this constructor copies every component of the input graphicscomponent
	 *
	 * @param gc
	 */

	AnimationLoop(AnimationLoop* aniloop);

	/** \brief destructor
	*
	* clears the allocated memory.
	*/

	virtual ~AnimationLoop();

	/** \brief updates the rootnodes about animation time
	 *
	 * @param float t : animation time
	 */

	void updateNodes(float t);

	/** \brief adds a rootnode
	 *
	 * @param Node* node : new root node
	 */

	void addNode(Node* node);

	/** \brief setter
	 *
	 *sets the duration of an animation
	 *
	 * @param float t : duration
	 */

	void setDuration(float t);

	/** \brief getter
	 *
	 * @return duration
	 */

	float getDuration();

	/** \brief getter
	 *
	 * @return rootnodes
	 */

	std::vector<Node*> getNodes();

private:

	std::vector<Node*> mNodes;/**< root node */
	float duration;/**< animation duration */

};

#endif /* ANIMATIONLOOP_H_ */
