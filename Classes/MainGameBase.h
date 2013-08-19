#ifndef __MAIN_GAME_BASE_H__
#define __MAIN_GAME_BASE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameBaseLayer : public Layer
{
public:
	CREATE_FUNC(MainGameBaseLayer);
	~MainGameBaseLayer();

	// touch event
	bool containsMarinelifeLocation(Touch* touch);

	// collision check
	void detectCollision(float dt);
	bool checkCollision();

	// falled in love event
	void toEndGameSceneWithLove();

	void checkFeet(float dt);

	// sound
	void playBubbleEffect(float dt);

	// save
	void saveAllGameData();
	void saveDiverData();
	void addAttachedMarinelife(Layer* lyr);
	void saveDivedFeetData();
	void saveFeverData();

	// -- For Overriding --
	int iMaxFeet;
	int iTagForMarinelife;

	virtual bool init();

	virtual void onEnterTransitionDidFinish();
	virtual void menuBackCallback(Object* pSender);
	virtual void byeMenuLabelRefresh(float dt);

	virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	virtual void goToNextGameScene();
};

#endif