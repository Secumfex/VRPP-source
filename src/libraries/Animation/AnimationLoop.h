/*
 * AnimationLoop.h
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#ifndef ANIMATIONLOOP_H_
#define ANIMATIONLOOP_H_

class AnimationLoop {
public:
	AnimationLoop();
	virtual ~AnimationLoop();

private:
	float duration;
	float pasttime;
};

#endif /* ANIMATIONLOOP_H_ */
