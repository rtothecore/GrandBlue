#ifndef __MAINGAME_SCENE4_H__
#define __MAINGAME_SCENE4_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene4 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene4);
};

class MainGameLayer4 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer4);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE4_H__