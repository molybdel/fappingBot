#include "MenuScene.h"
#include "PlayScene.h"
#include "OverLayer.h"
#include "cocos2d.h"
USING_NS_CC;

Scene * MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize;
	Vec2 origin;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto menuBackground = Sprite::create("MenuBackground.png");
	menuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(menuBackground);

	auto titleGame = Sprite::create("Title.png");
	titleGame->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 * 3);
	this->addChild(titleGame);

	//Button
	auto playBtn = MenuItemImage::create("PlayBtn.png", "playBtn.png", CC_CALLBACK_0(MenuScene::openOverLayer, this));
	auto menu = Menu::create(playBtn, nullptr);
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(menu);
	return true;
}

void MenuScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}

void MenuScene::openOverLayer()
{
	auto overlayer = OverLayer::create();
	overlayer->setScore(0);
	//overlayer->setPosition(origin.x, origin.y);
	this->addChild(overlayer);
}
