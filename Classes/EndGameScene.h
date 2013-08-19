#ifndef __ENDGAME_SCENE_H__
#define __ENDGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class EndGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(EndGameScene);

	int iTagForMarinelife;
	void initWithMarinelifeTag(int tagVal);

	// end game with love
	void runLoveEvent();
	void actionLove(float dt);
};

#endif