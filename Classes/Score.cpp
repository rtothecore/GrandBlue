#include "Score.h"
#include "Tags.h"
#include "MainGameData.h"
#include "Sound.h"
#include "Resource.h"
#include "ScoreRecord.h"

bool ScoreLayer::init()
{
	countedResultScore = 0;
	isNewRecord = false;

	initWithGameResult();
	

	return true;
}

void ScoreLayer::initWithGameResult()
{
	int divedFeet = MainGameDataLayer::getDivedFeet();
	int byeCount = MainGameDataLayer::getByeCount();
	int attachedMarinelifeCount = MainGameDataLayer::getLovePoint();
	int feverCount = MainGameDataLayer::getFeverCount();

	resultScore = (divedFeet * divedFeet_score) + 
		          (byeCount * byeCount_score) +
				  (feverCount * feverCount_score);
				  //(attachedMarinelifeCount * attachedMarinelifeCount_score);

	countStep = resultScore / 10;

	// show game result
	showGameResult(divedFeet, byeCount, attachedMarinelifeCount, feverCount);

	// if score greater than record, write plist as a 1st score
	if(ScoreRecordLayer::is1stScore(resultScore))
	{
		isNewRecord = true;
		//create label about congratulation with new record
		addNewRecordLabel(resultScore);
	} 
	else 
	{
		addResultScoreLabel(resultScore);
	}

	// start count score
	startScoreAction();
	
}

void ScoreLayer::showGameResult(int divedFeet, int byeCount, int attachedMLCount, int feverCount)
{
	char chrGameResult[70] = {0};
	sprintf(chrGameResult, "Dive: %d x 10\nBye: %d x 100\nFever: %d x 1000", divedFeet, byeCount, feverCount);

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
	char chrScore[40] = {0};
	
	if(isNewRecord)
		sprintf(chrScore, "New High Score!\n%d", countedResultScore);
	else
		sprintf(chrScore, "\nScore: %d", countedResultScore);
	
	labelScore->setString(chrScore);

	if(resultScore <= countedResultScore)
	{
		unschedule(schedule_selector(ScoreLayer::countingScore));
	}
}

void ScoreLayer::addResultScoreLabel(int resultScore)
{
	// create score label
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/5);
	float fontSize = 18;

	String* strScore = String::createWithFormat("\nScore:%d", resultScore);

	auto labelScore = LabelTTF::create(strScore->getCString(), FONT_MENU_FILE, fontSize, 
		blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	labelScore->setPosition(Point(winSize.width/2, winSize.height/2));
	labelScore->setColor(Color3B::YELLOW);
	addChild(labelScore, 1, kTagLabelScore);
}

void ScoreLayer::addNewRecordLabel(int newRecordScore)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/8);
    float fontSize = 18;

	String* strNewRecord = String::createWithFormat("New High Score!\n%d", newRecordScore);

	auto labelNewRecord = LabelTTF::create(strNewRecord->getCString(), FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	//Point dstPoint = Point(winSize.width/4, winSize.height/2 + labelNewRecord->getContentSize().height*2);
	Point dstPoint = Point(winSize.width/4, winSize.height/2);
	int offset = (int) (winSize.width/2 + 50);

	labelNewRecord->setPosition(  Point( dstPoint.x + offset, dstPoint.y) );
	labelNewRecord->setColor(Color3B::YELLOW);
	labelNewRecord->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );

	addChild(labelNewRecord, 1, kTagLabelScore);
}

//void ScoreLayer::countingNewRecordScore(float dt)
//{
//	countedResultScore += countStep;
//
//	LabelTTF* labelScore = ((LabelTTF*)getChildByTag(kTagLabelNewRecordScore));
//	char chrScore[15] = {0};
//	sprintf(chrScore, "Congratulation!\nNew Record Score!\n%d", countedResultScore);
//	labelScore->setString(chrScore);
//
//	if(resultScore <= countedResultScore)
//	{
//		unschedule(schedule_selector(ScoreLayer::countingScore));
//	}
//}

