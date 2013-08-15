#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene);
};

class MainGameLayer : public Layer
{
private:
	Array*    _dolphins;

public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer);
	
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
