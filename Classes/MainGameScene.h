#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include "MainGameBase.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene);
};

class MainGameLayer : public MainGameBaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer);
	void onEnterTransitionDidFinish();

	void addDolphin(float dt);
	void addDiver();
	void addRocks();
	void addRope();
	void addBackground();

	void goToNextGameScene();
};

#endif // __MAINTITLE_SCENE_H__
