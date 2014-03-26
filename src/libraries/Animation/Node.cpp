/*
 * Node.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Raphimulator
 */

#include <Animation/Node.h>

Node::Node(std::vector<Node*> node) {
	mChildren = node;
	addTransformation(glm::vec3(0.0f), glm::vec3(1.0f), glm::quat(glm::mat4()), 0.0f);
}

Node::~Node() {
}

void Node::setName(std:: string name){
	mName = name;
}
std::string Node::getName(){
	return mName;
}

std::vector<Node*> Node::getChildren(){
	return mChildren;
}

void Node::addTransformation(glm::vec3 pos, glm::vec3 scale, glm::quat rotation, float time){
	mPositions.push_back(pos);
	mScales.push_back(scale);
	mRotations.push_back(rotation);
	mTimes.push_back(time);
}
void Node::setBone(Bone* bone){
	mBone = bone;
}

Bone* Node::getBone(){
	return mBone;
}

void Node::updateBone(float t){
	if(mTimes.size()<2)
		return;
	float next_time = t;
	t = fmod(t, mTimes[mTimes.size() - 1]);

	int index = getTimeIndex(t);
	int index02 = index % mTimes.size();
	float start = mTimes[index];
	float end = mTimes[index02];

	t = t - start;
	end = end - start;
	t = t / end;


	glm::vec3 pos = (mPositions[index] * (1 - t)) + (mPositions[index02] * t);
	glm::vec3 scale = (mScales[index] * (1 - t)) + (mScales[index02] * t);
	glm::quat rotate = (mRotations[index] * (1 - t)) + (mRotations[index02] * t);

	mBone->setAnimationMatrix(glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rotate) * glm::scale(glm::mat4(1.0f), scale));

	unsigned int i;
	for (i = 0; i < mChildren.size(); ++i) {
		mChildren[i]->updateBone(next_time);
	}
}
int Node::getTimeIndex(float t){
	int index = 0;
	if(mTimes.size() == 1)
		return index;
	unsigned int i;
	for (i = 1; i < mTimes.size(); ++i) {
		if(mTimes[i-1] <= t || mTimes[i] >= t )
			index = i-1;
	}
	return index;
}
