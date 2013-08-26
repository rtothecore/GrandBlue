#ifndef __SCORE_RECORD_H__
#define __SCORE_RECORD_H__

#include "cocos2d.h"

USING_NS_CC;

class ScoreRecordLayer : public Layer
{
public:
	CREATE_FUNC(ScoreRecordLayer);
	virtual bool init();

	static bool is1stScore(int newScore);
	static void writeScoreToPlist(int score);
	static int readScoreFromPlist();

	static void addHighScoreLabel(Layer* lyr, Color3B color);
};

#endif