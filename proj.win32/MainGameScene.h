#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	MainGameScene();
};

class MainGameLayer : public Layer
{
private:
	Array*    _dolphins;

public:
	MainGameLayer();
	~MainGameLayer();
 
	void onEnterTransitionDidFinish();
    void menuBackCallback(Object* pSender);
	void addDolphin(float dt);
	void addRocks();
	void addRope();
};


#endif // __MAINTITLE_SCENE_H__
