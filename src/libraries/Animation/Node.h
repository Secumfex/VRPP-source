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

class Node {
public:
	Node(std::vector<Node*> node);
	virtual ~Node();

	void setName(std::string name);
	std::string getName();
	std::vector<Node*> getChildren();

private:
	std::vector<Node*> mChildren;
	std::string mName;
};

#endif /* NODE_H_ */
