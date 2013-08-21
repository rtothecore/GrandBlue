#ifndef __MAINGAME_SCENE2_H__
#define __MAINGAME_SCENE2_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene2 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene2);
};

class MainGameLayer2 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer2);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE2_H__