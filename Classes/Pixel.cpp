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
void Pixel::Flap()
{
	//Bay
	isFalling = false;
}

void Pixel::Fall()
{
	//Rơi
	isFalling = true;
}

void Pixel::Update()
{
	//Nếu mà nó đang rơi
	if (isFalling)
	{
		//Mà nó ở vị trí bên trên cạnh phía dưới
		if (pixelTexture->getPositionY() > pixelTexture->getContentSize().height / 2)
		{
			//Pixel đang rơi
			//Thì sẽ cộng thêm -1 (trừ đi 1) cho Y, tốc độ rơi ngày càng nhanh, và xoay cộng thêm 3
			velocityY += -1;
			rotation += 3;
		}
		//Nếu không
		else
		{
			//Nó sẽ không rơi nữa, không xoay luôn
			velocityY = 0;
			rotation = 0;

			//Cho pixel nằm ở dưới đáy
			pixelTexture->setPositionY(pixelTexture->getContentSize().height / 2);

			//Và ta sẽ chết
			isDead = true;
		}
	}
	//Nếu mà nó không có rơi
	else
	{
		//Mà nó ở dưới cái trần bên trên
		if (pixelTexture->getPositionY() < visibleSize.height - pixelTexture->getContentSize().height / 2)
		{
			//Pixel đang bay lên
			//Thì mới tăng bay lên (tăng Y)
			velocityY = 10;
			rotation += -10;
		}
		//Nếu nó đụng trần bên trên
		else
		{
			//Thì sẽ không bay lên được
			velocityY = 0;
			rotation = 0;
		}
	}

	//Cuối cùng ta set vị trí và góc xoay cho Sprite thôi :D
	pixelTexture->setPosition(Point(pixelTexture->getPositionX(), pixelTexture->getPositionY() + velocityY));
	pixelTexture->setRotation(rotation);
}
