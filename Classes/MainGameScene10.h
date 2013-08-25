#ifndef __MAINGAME_SCENE10_H__
#define __MAINGAME_SCENE10_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene10 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene10);
};

class MainGameLayer10 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer10);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE10_H__