#ifndef __MAINGAME_SCENE3_H__
#define __MAINGAME_SCENE3_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene3 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene3);
};

class MainGameLayer3 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer3);
	void onEnterTransitionDidFinish();

	void addMarinelife(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
	void readyToGoNextScene();
};

#endif // __MAINTITLE_SCENE3_H__