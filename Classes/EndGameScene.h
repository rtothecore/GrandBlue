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

	// end game with love
	void runLoveEvent();
	void actionLove(float dt);

	// continue
	void addContinueMenu(float dt);
	void continueGameCallback(Object* pSender);
	void endGameCallback(Object* pSender);

	// score
	void addScoreLabel();
};

#endif