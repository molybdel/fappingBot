#include "Pipe.h"
#include "Definitions.h"

Pipe::Pipe(Layer * layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	// gán vân tốc x cho pipe // pipe di chuyển theo chiều ngang
	velocityX = 120.0f;

	// tạo pipe phía dưới
	bottomTexture = Sprite::create("Pipe.png");

	// random tọa độ của Y cho pipe dưới trong khoảng -1/4 chiều cao của hình pipe -> 1/3 chiều cao của hình pipe
	float randomY = RandomHelper::random_int(-(int)(bottomTexture->getContentSize().height / 4), (int)(bottomTexture->getContentSize().height / 3));

	//Và gán vị trí cho nó
	bottomTexture->setPosition(origin.x + visibleSize.width + bottomTexture->getContentSize().width / 2, origin.y + randomY);

	// tạo physicsBody 
	bottomBody = PhysicsBody::createBox(bottomTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	//Body mặc định là dynamic, có nghĩa là "động" -> sẽ di chuyển nếu bị tác động vật lý
	//nếu setDynamic(false) nó sẽ không di chuyển
	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::PIPE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	bottomTexture->setPhysicsBody(bottomBody);
	layer->addChild(bottomTexture);

	// Pipe trên
	topTexture = Sprite::create("Pipe.png");

	// khoảng trống giữa pipe trên và dưới là 220
	topTexture->setPosition(bottomTexture->getPositionX(), bottomTexture->getPositionY() + topTexture->getContentSize().height + 220);
	topBody = PhysicsBody::createBox(topTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	topBody->setDynamic(false);
	topBody->setCategoryBitmask(eObjectBitmask::PIPE);
	topBody->setCollisionBitmask(0);
	topBody->setContactTestBitmask(eObjectBitmask::PIXEL);
	topTexture->setPhysicsBody(topBody);
	layer->addChild(topTexture);

	//Score Line
	//Là đối tượng để mình tính điểm nếu Pixel đi qua nó
	auto scoreLine = Node::create();
	scoreLine->setPosition(Point(bottomTexture->getContentSize().width, bottomTexture->getContentSize().height + 110));
	auto lineBody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	lineBody->setDynamic(false);

	lineBody->setCategoryBitmask(eObjectBitmask::LINE);
	lineBody->setCollisionBitmask(0);
	lineBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	scoreLine->setPhysicsBody(lineBody);
	bottomTexture->addChild(scoreLine);

	// pipe di chuyển 
	endPositionX = origin.x - bottomTexture->getContentSize().width / 2;
	isMoveFinished = false;

	// thời gian di chuyển = visibleSize.width / veloccityX
	// khi di chuyển đến end point --> call func moveFinished()

	bottomTexture->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.width / velocityX, Point(endPositionX, bottomTexture->getPositionY())),CallFunc::create(CC_CALLBACK_0(Pipe::moveFineshed, this))));
	topTexture->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.width / velocityX, Point(endPositionX, topTexture->getPositionY())), CallFunc::create(CC_CALLBACK_0(Pipe::moveFineshed, this))));
}

void Pipe::moveFineshed()
{
	topTexture->removeFromParent();
	bottomTexture->removeFromParent();
	isMoveFinished = true;
}



