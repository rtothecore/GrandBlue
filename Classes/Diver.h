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

	// sprite
	SpriteFrame *frm_diver;
	Sprite *sprt_diver;

	// action
	void spriteMoveFinished(Object* pSender);
	void actionMoveStacked(Layer *lyr, int destX, int destY);

	// touch event
    Rect getRect();
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(Touch* touch);

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	// Love Point
	bool isLove;
	static const unsigned int st_maxLovePoint = 5;
	unsigned int lovePoint;
	unsigned int lapCount;
	Sprite *sprt_love;
	void refreshLoveSprite();
	void increaseLovePoint();
	void increaseLapCount();
	void runLoveAction();

	// get collisioned dolphin
	Rect getDiverRect();
	void refreshDiverPositionWithDolphin();

	// refresh diver
	void refreshDiver();

	void runFevermodeAction();
	void exitFevermodeAction();
	void runMeetMarinelifeAction();

	void moveByDisplacement(Point displace);
};

#endif
