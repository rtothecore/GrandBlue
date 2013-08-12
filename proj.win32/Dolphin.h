#ifndef __DOLPHIN_H__
#define __DOLPHIN_H__

#include "cocos2d.h"

USING_NS_CC;

class Dolphin : public Sprite, public TargetedTouchDelegate, public Clonable
{
public:
	Dolphin(void);
	~Dolphin(void);

	// action
	int getRandomRangeValue(int minVal, int maxVal);

	void spriteFlipY(Object* pSender);
	void spriteUnflipY(Object* pSender);
	void spriteMoveFinished(Object* pSender);

	void actionSequence(Sprite* spr, int actualY, int actualDuration);
	void actionBezier(Sprite* spr, int actualY);

	// touch event
    Rect getRect();
    bool initWithTexture(Texture2D* aTexture);
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);
    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

    virtual Dolphin* clone() const;

    static Dolphin* createWithTexture(Texture2D* aTexture);

	void removeMyself(float dt);

	// Health Point
	static const int st_healthpoint = 3;
	Sprite *sprt_hp;
	int healthPoint;
	void decreaseHealthPoint(Touch* touch);
};

#endif