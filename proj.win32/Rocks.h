#ifndef __ROCKS_H__
#define __ROCKS_H__

#include "cocos2d.h"

USING_NS_CC;

class Rocks : public Sprite
{
public:
	Rocks(void);
	~Rocks(void);

	static Rocks* createWithTexture(Texture2D* aTexture);
	bool initWithTexture(Texture2D* aTexture);
	void actionSequence(Sprite* spr, int destX, int destY, int actualDuration);
	void rockUpFinished(Object* pSender);
};

#endif