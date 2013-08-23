#include "Score.h"
#include "Tags.h"
#include "MainGameData.h"
#include "Sound.h"
#include "Resource.h"

bool ScoreLayer::init()
{
	countedResultScore = 0;
	initWithGameResult();

	return true;
}

void ScoreLayer::initWithGameResult()
{
	int divedFeet = MainGameDataLayer::getDivedFeet();
	int byeCount = MainGameDataLayer::getByeCount();
	int attachedMarinelifeCount = MainGameDataLayer::getLovePoint();

	resultScore = (divedFeet * divedFeet_score) + 
		          (byeCount * byeCount_score) + 
				  (attachedMarinelifeCount * attachedMarinelifeCount_score);

	countStep = resultScore / 10;

	// create score label
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/5);
    float fontSize = 18;

	auto labelScore = LabelTTF::create("\nScore:0", FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	labelScore->setPosition(Point(winSize.width/2, winSize.height/2));
	labelScore->setColor(Color3B::YELLOW);
    addChild(labelScore, 1, kTagLabelScore);

	// show game result
	showGameResult(divedFeet, byeCount, attachedMarinelifeCount);

	// start count score
	startScoreAction();
}

void ScoreLayer::showGameResult(int divedFeet, int byeCount, int attachedMLCount)
{
	char chrGameResult[70] = {0};
	sprintf(chrGameResult, "Dive: %d x 10\nBye: %d x 100\nMarinelife: %d x 1000", divedFeet, byeCount, attachedMLCount);

	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/5);
    float fontSize = 18;
	auto labelGameResult = LabelTTF::create(chrGameResult, FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	labelGameResult->setPosition(Point(winSize.width/2, (winSize.height/2) + (labelGameResult->getContentSize().height)));
	addChild(labelGameResult);
}

void ScoreLayer::startScoreAction()
{
	schedule(schedule_selector(ScoreLayer::countingScore), 0.1f);

	//sound
	Sound::playScoreEffect();
}

void ScoreLayer::countingScore(float dt)
{
	countedResultScore += countStep;

	LabelTTF* labelScore = ((LabelTTF*)getChildByTag(kTagLabelScore));
	char chrScore[15] = {0};
	sprintf(chrScore, "\nScore: %d", countedResultScore);
	labelScore->setString(chrScore);

	if(resultScore <= countedResultScore)
	{
		unschedule(schedule_selector(ScoreLayer::countingScore));
	}
}

