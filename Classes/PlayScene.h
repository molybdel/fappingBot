#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "cocos2d.h"
#include "Pixel.h"
#include "Pipe.h"
class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void onMouseDown(Event* event);
	void update(float dt);
	void onExit();
	bool onContactBegin(PhysicsContact & contact);
private:
	Size visibleSize;
	Vec2 origin;

	//Pixel để mình điều khiển
	Pixel* pixel;
	void pixelFall(float dt);

	//Hàm tạo Pipe, với listPipes
	void createPipe(float dt);
	void pipeMoveFinished();
	std::list<Pipe*> listPipes;

	bool isDead;

	//Hiển thi điểm số
	LabelTTF* scoreLabel;
	int score;
};

#endif // !PLAY_SCENE_H
