/*
 * Node.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Raphimulator
 */

#include <Animation/Node.h>

Node::Node(std::vector<Node*> node) {
	mChildren = node;
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
if(mTimes.size() == 0)
	time = 0.0;

using namespace std;
//cout << "At time "<< time << " for Node " << mName <<endl;
//cout << "(" << pos.x << "/" << pos.y << "/" << pos.z <<")" <<endl;
//cout << "(" << scale.x << "/" << scale.y << "/" << scale.z <<")" <<endl;
//cout << "(" << rotation.w << "/" << rotation.x << "/" << rotation.y << "/" << rotation.z <<")" <<endl;
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

void Node::updateBone(float t, glm::mat4 parent_mat){

	float next_time = t;


	if(mTimes.size()<2)
		return;

	int index = getTimeIndex(t);
	int index02 = (index + 1) % mTimes.size();
	float start = mTimes[index];
	float end = mTimes[index02];

	t = t - start;
	end = end - start;
	t = t / end;

	glm::vec3 pos = (mPositions[index] * (1 - t)) + (mPositions[index02] * t);
	glm::vec3 scale = (mScales[index] * (1 - t)) + (mScales[index02] * t);
	glm::quat rotate = (mRotations[index] * (1 - t)) + (mRotations[index02] * t);

//	glm::mat4 transform = parent_mat * glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rotate) * glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 transform = parent_mat * glm::mat4_cast(rotate);

//	mBone->setAnimationMatrix(glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rotate) * glm::scale(glm::mat4(1.0f), scale));
	mBone->setAnimationMatrix(transform);

	unsigned int i;
	for (i = 0; i < mChildren.size(); ++i) {
		mChildren[i]->updateBone(next_time, transform);
	}

}
int Node::getTimeIndex(float t){
	int index = 0;
	if(mTimes.size() == 1)
		return index;
	unsigned int i;
	for (i = 1; i < mTimes.size(); ++i) {
		if(mTimes[i-1] <= t && mTimes[i] >= t ){
			index = i-1;
		}
	}
	return index;
}
