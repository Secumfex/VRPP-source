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

class AnimationLoop {
public:
	AnimationLoop();
	virtual ~AnimationLoop();

	std::vector<Node*> mNodes;

	void updateNodes(float t);
	void addNode(Node* node);
	void setDuration(float t);
	void setCorrectOffsetMatrix();
	void setStartTransformation(glm::mat4 armature);

private:
	glm::mat4 mStartMatrix;
	float duration;
	float pasttime;
};

#endif /* ANIMATIONLOOP_H_ */
