/*
 * AnimationLoop.cpp
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#include "Animation/AnimationLoop.h"

AnimationLoop::AnimationLoop() {
	// TODO Auto-generated constructor stub

}

AnimationLoop::~AnimationLoop() {
	// TODO Auto-generated destructor stub
}

void AnimationLoop::updateNodes(float t){
	unsigned int i;
	float next_time = fmod(t, duration);

//	std::cout << "Rootnode is ";

	for (i = 0; i < mNodes.size(); ++i) {
		mNodes[i]->updateBone(next_time);
	}
//	std::cout << std::endl;
}
void AnimationLoop::addNode(Node* node){
	mNodes.push_back(node);
}
void AnimationLoop::setDuration(float t){
	duration = t;
}
void AnimationLoop::setCorrectOffsetMatrix(){
	unsigned int i;

	for (i = 0; i < mNodes.size(); ++i) {
			mNodes[i]->setCorrectOffsetMatrix(glm::mat4());
		}
}
