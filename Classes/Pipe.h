#ifndef __PIPE_H__
#define __PILE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Pipe {
public:
	Pipe(Layer* layer);
	void moveFineshed();
	bool isMoveFinished;

private:
	Sprite * topTexture, *bottomTexture;
	PhysicsBody* topBody, *bottomBody;
	Size visibleSize;
	Vec2 origin;
	float velocityX;
	float endPositionX;
};

#endif // !__PIPE_H__\
#pragma once
