#ifndef __MAINGAME_SCENE7_H__
#define __MAINGAME_SCENE7_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene7 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene7);
};

class MainGameLayer7 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer7);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE7_H__