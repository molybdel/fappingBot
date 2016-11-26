#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
private:
	void gotoPlayScene();
	void openOverLayer();
};

#endif // !MENU_SCENE_H

