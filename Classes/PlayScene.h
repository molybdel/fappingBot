#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "cocos2d.h"
class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
private:

};

#endif // !PLAY_SCENE_H
