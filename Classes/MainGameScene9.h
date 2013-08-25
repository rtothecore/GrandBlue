#ifndef __MAINGAME_SCENE9_H__
#define __MAINGAME_SCENE9_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene9 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene9);
};

class MainGameLayer9 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer9);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE9_H__