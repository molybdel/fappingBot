#include "Pixel.h"
#include "Definitions.h"
Pixel::Pixel(Layer * layer)
{
	// cá giá tri jcuar màn hình hiện tại
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	// tạo sprite cho pixel và set vị trí
	pixelTexture = Sprite::create("Pixel.png");
	pixelTexture->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	// tạo PhysicsBody cho pixelTexture
	pixelBody = PhysicsBody::createBox(pixelTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	//gán giá trị để set va chạm
	pixelBody->setCategoryBitmask(eObjectBitmask::PIXEL);

	//Gán CollisionBitmask cho body
	//Hiểu đơn giản là "Tao có thể chạm với PIPE"
	//pixelBody->setCollisionBitmask(eObjectBitmask::PIPE);
	//Gán ContactTestBitmask cho body, tương tự Collision mà nó sẽ gọi các hàm onContact...
	//Hiểu đơn giản là "Tao sẽ gọi cho onContact... khi chạm với PIPE hoặc LINE"
	pixelBody->setContactTestBitmask(eObjectBitmask::PIPE || eObjectBitmask::LINE);

	//gans body cho Sprite 
	pixelTexture->setPhysicsBody(pixelBody);

	layer->addChild(pixelTexture, 100);

	isFalling = true;

	velocityY = 0.0f;

	rotation = 0.0f;

	isDead = false;

}
