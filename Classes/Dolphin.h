#ifndef __DOLPHIN_H__
#define __DOLPHIN_H__

#include "cocos2d.h"

USING_NS_CC;

class DolphinLayer : public Layer, public Clonable
{
public:
	virtual bool init();
	CREATE_FUNC(DolphinLayer);

	~DolphinLayer();
	virtual DolphinLayer* clone() const;
	bool initWithPlist(const char* plist);
	void removeMyself(float dt);

	// sprite
	SpriteFrame *frm_dolphin;
	Sprite *sprt_dolphin;
	bool isHeadToLeft;

	// action
	void spriteFlipY(Object* pSender);
	void spriteUnflipY(Object* pSender);
	void spriteMoveFinished(Object* pSender);

	void actionSequence(Layer* spr, int actualY, int actualDuration);
	void actionBezier(Layer* spr, int actualY);

	// touch event
    Rect getRect();
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	// Bye Point
	bool isBye;
	static const int st_byePoint = 3;
	int byePoint;
	Sprite *sprt_bye;

	void aliveDolphinTouched();

	void byePointUp();
	void refreshByeSprite();
	void actionTint(Sprite* sprt);
	void comboForFeverUp();
	void actionBlinkAndRemove(Sprite* sprt);
	void playDolphinSound();

	// attach to diver
	bool isAttachedToDiver;
	Rect getDolphinRect();
	void attachToDiver(int diverPosX, int diverPosY);

	// love action
	void runLoveAction();

};

#endif