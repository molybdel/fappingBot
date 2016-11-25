#include "PlayScene.h"
#include "cocos2d.h"
#include "OverLayer.h"

USING_NS_CC;

Scene * PlayScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	// 'layer' is an autorelease object
	auto layer = PlayScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	isDead = false;

	Sprite * menuBackground = Sprite::create("PlayBackground.png");
	menuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(menuBackground);

	pixel = new Pixel(this);

	//Event Listener
	//Listener để lắng nghe event chuột, vì ở đây mình làm trên win32 nên mình sử dụng chuột
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PlayScene::onMouseDown, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener,this);

	//Contact listener
	//Listener để lắng nghe va chạm, ở phần setContactTestBitmask nó sẽ gọi đến hàm này nếu có va chạm
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Update
	//Cái này dùng để gọi hàm update đã kế thừa bên trên qua mỗi frame
	this->scheduleUpdate();

	// pipe mới đc tạo sau mỗi 2s
	this->schedule(schedule_selector(PlayScene::createPipe, this), 2.0f);

	listPipes.push_back(new Pipe(this));

	//Score
	//Điểm số, LabelTTF sẽ tạo chữ bằng font .ttf
	score = 0;
	scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 50);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);

	this->addChild(scoreLabel, 50);


	return true;
}

void PlayScene::onMouseDown(Event * event)
{
	EventMouse* mouse = (EventMouse*) event;
	if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
		pixel->Flap();
		//rơi sau 0.1s
		this->scheduleOnce(schedule_selector(PlayScene::pixelFall), 0.1);
	}
}

void PlayScene::update(float dt)
{
	for (std::list<Pipe*>::iterator pipe = listPipes.begin(); pipe != listPipes.end(); pipe++)
	{
		if ((*pipe)->isMoveFinished)
		{
			CC_SAFE_DELETE((*pipe));
			listPipes.remove(*pipe);
			break;
		}
	}

	//nếu chết
	pixel->Update();
	if (isDead || pixel->isDead) {
		//xóa label
		this->removeChild(scoreLabel);
		//pause game, stop update
		this->pause();
		auto childs = this->getChildren();
		for each (auto child in childs)
		{
			child->pause();
		}

		auto overlayer = OverLayer::create();
		overlayer->setScore(score);
		overlayer->setPosition(origin.x, origin.y);
		this->addChild(overlayer);
	}
}

void PlayScene::onExit()
{
	Layer::onExit();
	CC_SAFE_DELETE(pixel);
	while (!listPipes.empty())
	{
		CC_SAFE_DELETE(listPipes.front());
		listPipes.pop_front();
	}
}

bool PlayScene::onContactBegin(PhysicsContact & contact)
{
	//lấy 2 cái đối tượng mà nó va chạm với nhau ra
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	//Nếu A và B là PIPE và PIXEL thì tèo
	if ((shapeA->getCategoryBitmask() == eObjectBitmask::PIPE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
		(shapeB->getCategoryBitmask() == eObjectBitmask::PIPE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
	{
		//Teo...
		isDead = true;
	}
	else
	{
		//Nếu mà PIXEL va chạm với LINE thì
		if ((shapeA->getCategoryBitmask() == eObjectBitmask::LINE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
			(shapeB->getCategoryBitmask() == eObjectBitmask::LINE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
		{
			//Cộng điểm lên
			score++;
			scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		}
	}

	return true;
}

void PlayScene::pixelFall(float dt)
{
	pixel->Fall();
}

void PlayScene::createPipe(float dt)
{
	listPipes.push_back(new Pipe(this));
}
