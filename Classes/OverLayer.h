#ifndef OVER_LAYER_H
#define OVER_LAYER_H
#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class OverLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(OverLayer);

	void setScore(int _score);
private:
	int score;
	void gotoMenuScene();
	void gotoPlayScene();
	LabelTTF* scoreLabel;
};

#endif // !OVER_LAYER_H

