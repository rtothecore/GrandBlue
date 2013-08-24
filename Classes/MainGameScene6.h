#ifndef __MAINGAME_SCENE6_H__
#define __MAINGAME_SCENE6_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene6 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene6);
};

class MainGameLayer6 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer6);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE6_H__