#ifndef __MARINE_LIFE_H__
#define __MARINE_LIFE_H__

#include "cocos2d.h"

USING_NS_CC;

class MarineLifeLayer : public Layer, public Clonable
{
public:
	CREATE_FUNC(MarineLifeLayer);

	bool isBye;
	static const int st_byePoint = 3;
	int byePoint;
	bool isHeadToLeft;
	bool isAttachedToDiver;

	Rect getRect();

protected:
	// sprite
	Sprite *sprt_bye;
	SpriteFrame *frm_marineLife;
	Sprite *sprt_marineLife;

	// end
	void removeMyself(float dt);

	// action
	void actionSequence(Layer* spr, int actualY, int actualDuration);
	void actionBezier(Layer* spr, int actualY);
	void spriteFlipY(Object* pSender);
	void spriteUnflipY(Object* pSender);
	void spriteMoveFinished(Object* pSender);

	// touch event
    void onEnter();
    void onExit();
	bool ccTouchBegan(Touch* touch, Event* event);
    void ccTouchMoved(Touch* touch, Event* event);
    void ccTouchEnded(Touch* touch, Event* event);

	// bye
	void byePointUp();
	void refreshByeSprite();
	void actionTint(Sprite* sprt);
	void comboForFeverUp();
	void actionBlinkAndRemove(Sprite* sprt);
		
public:
	void aliveMarineLifeTouched();

	// attach to diver
	Rect getMarineLifeRect();
	void attachToDiver(int diverPosX, int diverPosY);
	void runAfterDiver(float dt);

	// love action
	void runLoveAction();

	// -- For Overriding --
	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual MarineLifeLayer* clone() const;
	virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif