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
