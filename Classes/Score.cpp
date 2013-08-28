#include "Score.h"
#include "Tags.h"
#include "MainGameData.h"
#include "Sound.h"
#include "Resource.h"
#include "ScoreRecord.h"
#include "Particle.h"
#include "AppMacros.h"

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
	int lapCount = MainGameDataLayer::getDiverLapCount();

	resultScore = ( (divedFeet * divedFeet_score) + 
		            (byeCount * byeCount_score) +
				    (feverCount * feverCount_score) ) * lapCount;
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

	// add rapCount Label
	if(1 < lapCount)
	{
		addLapCountLabel(lapCount);
	}

	// start count score
	startScoreAction();
	
}

void ScoreLayer::showGameResult(int divedFeet, int byeCount, int attachedMLCount, int feverCount)
{
	String* strGameResult = String::createWithFormat("Dive: %d x 10\nBye: %d x 100\nFever: %d x 1000", 
		                                              divedFeet, byeCount, feverCount);

	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/5);

	auto labelGameResult = LabelTTF::create(strGameResult->getCString(), FONT_MENU_FILE, RESULT_FONT_SIZE, 
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
	String* strScore;

	if(isNewRecord)
		strScore = String::createWithFormat("New High Score!\n%d", countedResultScore);
	else
		strScore = String::createWithFormat("\nScore: %d", countedResultScore);
	
	labelScore->setString(strScore->getCString());

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

	String* strScore = String::createWithFormat("\nScore:%d", resultScore);

	auto labelScore = LabelTTF::create(strScore->getCString(), FONT_MENU_FILE, SCORE_FONT_SIZE, 
		blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	labelScore->setPosition(Point(winSize.width/2, winSize.height/2));
	labelScore->setColor(Color3B::YELLOW);
	addChild(labelScore, 1, kTagLabelScore);

	// particle effect
	String* particlePlist;
	0 < (rand() % 2) ? particlePlist = String::create("particles/MagicianFloor_score.plist") : particlePlist = String::create("particles/Cosmos_score.plist");
	ParticleSystem* _emitter = ParticleLayer::createWithParticlePlist(particlePlist->getCString());
	_emitter->setPosition(winSize.width/2, 0);
	addChild(_emitter);
}

void ScoreLayer::addNewRecordLabel(int newRecordScore)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/5);

	String* strNewRecord = String::createWithFormat("New High Score!\n%d", newRecordScore);

	auto labelNewRecord = LabelTTF::create(strNewRecord->getCString(), FONT_MENU_FILE, SCORE_FONT_SIZE, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	Point dstPoint;
	if( 1 < MainGameDataLayer::getDiverLapCount() )
	{
		dstPoint = Point(winSize.width/4, winSize.height/2 - labelNewRecord->getContentSize().height/4);
	} else {
		dstPoint = Point(winSize.width/4, winSize.height/2);
	}
	int offset = (int) (winSize.width/2 + 50);

	labelNewRecord->setPosition(  Point( dstPoint.x + offset, dstPoint.y) );
	labelNewRecord->setColor(Color3B::YELLOW);
	labelNewRecord->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );

	addChild(labelNewRecord, 1, kTagLabelScore);

	// sound
	Sound::playHighScoreEffect();

	// particle effect
	ParticleSystem* _emitter = ParticleLayer::createWithParticlePlist("particles/FireWorks_highscore.plist");
	_emitter->setPosition(0, 0);
	addChild(_emitter);
}

void ScoreLayer::addLapCountLabel(int lapCount)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/8);

	String* strLapCount = String::createWithFormat("X %d Lap", lapCount);

	auto labelLapCount = LabelTTF::create(strLapCount->getCString(), FONT_MENU_FILE, LAP_FONT_SIZE, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	Point dstPoint = Point(winSize.width/4, winSize.height/2 + labelLapCount->getContentSize().height/2);
	int offset = (int) (winSize.width/2 + 50);

	labelLapCount->setPosition(  Point( dstPoint.x + offset, dstPoint.y) );
	labelLapCount->setColor(Color3B::YELLOW);
	labelLapCount->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );

	addChild(labelLapCount, 1);
}
