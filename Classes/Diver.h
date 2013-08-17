#ifndef __DIVER_H__
#define __DIVER_H__

#include "cocos2d.h"

USING_NS_CC;

class DiverLayer : public Layer, public Clonable
{
public:
	virtual bool init();
	CREATE_FUNC(DiverLayer);

	~DiverLayer(void);
	virtual DiverLayer* clone() const;
	bool initWithPlist(const char* plist);
	void removeMyself(float dt);

	// sprite
	SpriteFrame *frm_diver;
	Sprite *sprt_diver;

	// action
	void spriteFlipY(Object* pSender);
	void spriteUnflipY(Object* pSender);
	void spriteMoveFinished(Object* pSender);

	void actionSequence(Layer* spr, int actualY, int actualDuration);
	void actionBezier(Layer* spr, int actualY);
	void actionMoveStacked(Layer *lyr, int destX, int destY);

	// touch event
    Rect getRect();
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	// Health Point
	static const int st_healthpoint = 3;
	Sprite *sprt_hp;
	int healthPoint;
	void decreaseHealthPoint(Touch* touch);

	// get collisioned dolphin
	Rect getDiverRect();
	int attachedDolphins;
	void refreshDiverPositionWithDolphin();
	void actionDownMoveBy(int yDelta);
};

#endif
