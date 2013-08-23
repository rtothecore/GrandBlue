#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"

USING_NS_CC;

class ScoreLayer : public Layer
{
public:
	CREATE_FUNC(ScoreLayer);
	virtual bool init();

	static const int divedFeet_score = 10;
	static const int byeCount_score = 100;
	static const int attachedMarinelifeCount_score = 1000;

	int resultScore;
	int countedResultScore;
	int countStep;

	void initWithGameResult();
	void showGameResult(int divedFeet, int byeCount, int attachedMLCount);
	void startScoreAction();
	void countingScore(float dt);
};

#endif