#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	MainGameScene();
};

class MainGameLayer : public Layer
{
private:
	Array*    _dolphins;

public:
	MainGameLayer();
	~MainGameLayer();
 
	void onEnterTransitionDidFinish();
    void menuBackCallback(Object* pSender);
	void addDolphin(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	// Dolphin bye count
	int iDolphinBye; 
	void increaseDolphinBye();

	// Touch Fever
	bool bFeverMode;
	int iDolphinTouchFeverRequire;	// fever requirements
	int iDolphinTouch;
	void increaseTouchCombo();
	void resetTouchCombo();
	void checkFever();
	void intoTheFever();
	void endFever(float dt);

	static const int st_feverRequire = 5;
	static const int st_touchDamage = 1;
	static const int st_touchDamageFever = 3;
	static const int st_feverTime = 10;
	int iTouchDamage;

	// Sound
	void playBubbleEffect(float dt);

	// Label
	void menuLabelDolphinRefresh(float dt);

	// touch event
    bool containsDolphinLocation(Touch* touch);

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);
};


#endif // __MAINTITLE_SCENE_H__
