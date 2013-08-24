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
	void checkCollision();

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

	// ready go to next scene
	bool existUnattachedMarinlife();
	void checkRemainUnattachedMarinlife(float dt);

	// dive control
	void diveWithTimes(int timesValue);

	// for score
	void saveAllGameResult();

	// fever
	void addFever();

	// -- For Overriding --
	int iMaxFeet;
	int iTagForMarinelife;

	virtual bool init();

	virtual void onEnterTransitionDidFinish();
	virtual void addComboLabel();
	virtual void addMarinelife(float dt);
	virtual void comboLabelRefresh(float dt);

	virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	virtual void readyToGoNextScene();
	virtual void goToNextGameScene();


};

#endif