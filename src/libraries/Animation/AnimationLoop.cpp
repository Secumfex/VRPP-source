/*
 * AnimationLoop.cpp
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#include "Animation/AnimationLoop.h"

AnimationLoop::AnimationLoop() {
}

AnimationLoop::AnimationLoop(AnimationLoop* aniloop){
	unsigned int i;

	for (i = 0; i < aniloop->getNodes().size(); ++i) {
		this->addNode(aniloop->getNodes()[i]);
	}
	this->setDuration(aniloop->getDuration());
}

AnimationLoop::~AnimationLoop() {
	// TODO Auto-generated destructor stub
}

void AnimationLoop::updateNodes(float t){
	unsigned int i;
	float next_time = fmod(t, duration);

	for (i = 0; i < mNodes.size(); ++i) {
		mNodes[i]->updateBone(next_time, glm::mat4());
	}
}
void AnimationLoop::addNode(Node* node){
	mNodes.push_back(node);
}
void AnimationLoop::setDuration(float t){
	duration = t;
}
float AnimationLoop::getDuration(){
	return duration;
}
std::vector<Node*> AnimationLoop::getNodes(){
	return mNodes;
}
