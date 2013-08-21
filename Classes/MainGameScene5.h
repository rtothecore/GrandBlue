#ifndef __MAINGAME_SCENE5_H__
#define __MAINGAME_SCENE5_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene5 : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene5);
};

class MainGameLayer5 : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer5);
	void onEnterTransitionDidFinish();

	void addSeahorse(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
};

#endif // __MAINTITLE_SCENE5_H__