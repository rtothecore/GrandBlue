#ifndef __SPRITE_REPEATER_H__
#define __SPRITE_REPEATER_H__

#include "cocos2d.h"

USING_NS_CC;

class SpriteRepeater : public Sprite
{

public:
	static SpriteRepeater* createWithTexture(Texture2D* aTexture, int zValue, int durValue);
	virtual bool initWithTexture(Texture2D* aTexture, int zValue, int durValue);
	virtual void actionSequence(Sprite* spr, int destX, int destY, int actualDuration);
	virtual void moveFinished(Object* pSender);
};

class Rope : public SpriteRepeater
{
public:
	Rope(void);
	~Rope(void);
};

class Rocks : public SpriteRepeater
{
public:
	Rocks(void);
	~Rocks(void);
};

#endif