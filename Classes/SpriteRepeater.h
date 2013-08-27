#ifndef __SPRITE_REPEATER_H__
#define __SPRITE_REPEATER_H__

#include "cocos2d.h"

USING_NS_CC;

class SpriteRepeater : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(SpriteRepeater);

	float actionDurVal;

	Scheduler* schedRepeatMove;
	void createActionManager();
	void setTimeScale(float scale);

	Rect getSpriteRepeaterRect();

	// Y postion 
	float stopActionAndGetPositionY();
	float startY;
	void setStartY(float startYVal);

	// -- For Overriding --
	virtual bool initWithTexture(Texture2D* aTexture, int zValue);
	virtual void actionSequence(Sprite* spr, int destX, int destY);
	virtual void moveFinished(Object* pSender);
	
};

class Rope : public SpriteRepeater
{
public:
	virtual bool init();
	CREATE_FUNC(Rope);
};

class Rocks : public SpriteRepeater
{
public:
	virtual bool init();
	CREATE_FUNC(Rocks);
};

#endif