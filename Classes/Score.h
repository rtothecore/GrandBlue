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
	static const int feverCount_score = 1000;
	//static const int attachedMarinelifeCount_score = 1000;

	bool isNewRecord;

	int resultScore;
	int countedResultScore;
	int countStep;

	void initWithGameResult();
	void showGameResult(int divedFeet, int byeCount, int attachedMLCount, int feverCount);
	void startScoreAction();
	void countingScore(float dt);

	void addResultScoreLabel(int resultScore);
	void addNewRecordLabel(int newRecordScore);

	void addLapCountLabel(int lapCount);
};

#endif