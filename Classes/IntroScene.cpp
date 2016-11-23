#include "IntroScene.h"
#include "MenuScene.h"
USING_NS_CC;

Scene* IntroScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = IntroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//// my code
	//

	auto introBackground = Sprite::create("IntroBackGround.png");
	introBackground->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(introBackground);

	this->scheduleOnce(schedule_selector(IntroScene::gotoMenuScene), 5.0f);
	return true;
}


void IntroScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void IntroScene::gotoMenuScene(float dt)
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuscene);
}
