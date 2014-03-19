/*
 * Bone.h
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#ifndef BONE_H_
#define BONE_H_

#include <vector>
#include <string>

class Bone {
public:
	Bone(std::string name);
	virtual ~Bone();

	std::vector<Bone> children;
};

#endif /* BONE_H_ */
