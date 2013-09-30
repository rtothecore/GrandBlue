#include "MainGameBase.h"
#include "MainTitleScene.h"
#include "MenuLabel.h"
#include "Fever.h"
#include "MarineLife.h"
#include "Diver.h"
#include "DiveFeet.h"
#include "EndGameScene.h"
#include "Tags.h"
#include "Sound.h"
#include "MainGameData.h"
#include "SpriteRepeater.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "ScoreRecord.h"
#include "AppMacros.h"
#include "AdmobJNI.h"

bool MainGameBaseLayer::init()
{
	pOldTouched = Point(0, 0);
	bTouchNMoved = false;

	return true;
}

MainGameBaseLayer::~MainGameBaseLayer()
{
	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
}

void MainGameBaseLayer::onEnterTransitionDidFinish()
{
}

void MainGameBaseLayer::addPlayStatusLabel()
{
	// combo label
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/4, winSize.height/4);

	String* strStatusLabel = String::createWithFormat("Bye: %d\nFever: %d\nLap: %d", 
														 MainGameDataLayer::getByeCount(), 
														 MainGameDataLayer::getFeverCount(), 
														 MainGameDataLayer::getDiverLapCount());
	
	auto labelStatus = LabelTTF::create(strStatusLabel->getCString(), FONT_MENU_FILE, STATUS_FONT_SIZE, 
										blockSize, Label::HAlignment::LEFT, Label::VAlignment::CENTER);

	labelStatus->setPosition( Point(winSize.width - labelStatus->getContentSize().width/2, labelStatus->getContentSize().height/3) );
    addChild(labelStatus, 2, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameBaseLayer::playStatusLabelRefresh), 0.5);

	// High Score label
	ScoreRecordLayer::addHighScoreLabel(this, Color3B::BLUE);
}

void MainGameBaseLayer::addMarinelife(float dt)
{
}

void MainGameBaseLayer::playStatusLabelRefresh(float dt)
{
	LabelTTF* labelStatus = (LabelTTF*)getChildByTag(kTagMainGameMenuLabel);

	String* strGameStatus = String::createWithFormat("Bye: %d\nFever: %d\nLap: %d", 
							((FeverLayer*)getChildByTag(kTagFever))->getMarinelifeBye(), 
							((FeverLayer*)getChildByTag(kTagFever))->getFeverCount(),
							((DiverLayer*)getChildByTag(kTagLayerDiver))->lapCount);
	labelStatus->setString(strGameStatus->getCString());
}

bool MainGameBaseLayer::containsMarinelifeLocation(Touch* touch)
{
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;
	
	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( iTagForMarinelife == ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(!marinelifeL)
				break;

			if( !marinelifeL->getRect().containsPoint(convertTouchToNodeSpaceAR(touch)) )
				return false;
		}
	}

	return true;
}

bool MainGameBaseLayer::ccTouchBegan(Touch* touch, Event* event)
{
	// save old touch point
	pOldTouched = Point( touch->getLocation().x, touch->getLocation().y );

	bTouchNMoved = false;

    return true;
}

void MainGameBaseLayer::ccTouchMoved(Touch* touch, Event* event)
{
	// calculate displacement (old touch point - new touch point)
	Point pDisplacement = Point( touch->getLocation().x - pOldTouched.x, 
		                         touch->getLocation().y - pOldTouched.y );

	// Diver move by pDispalcement
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	diverL->moveByDisplacement(pDisplacement);

	// save old touch point
	pOldTouched = Point( touch->getLocation().x, touch->getLocation().y );

	bTouchNMoved = true;
}

void MainGameBaseLayer::ccTouchEnded(Touch* touch, Event* event)
{    
	if ( !bTouchNMoved && !containsMarinelifeLocation(touch) )
	{
		log("TOUCH MISS!!!!");
		((FeverLayer*)getChildByTag(kTagFever))->resetTouchCombo();
	}
}

void MainGameBaseLayer::detectCollision(float dt)
{
	checkCollision();
}

void MainGameBaseLayer::checkCollision()
{
	MarineLifeLayer* marinelifeL;
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	Rope* ropeL = (Rope*)getChildByTag(kTagRope);
	Object* pObj = NULL;

	Array *arrChildren = getChildren();

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		// Check between "diver" and "marinelife"
		if( iTagForMarinelife == ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(!marinelifeL)
				break;

			//if( !diverL->isLove
			if(	5 > diverL->lovePoint
				&& !marinelifeL->isBye
				&& !marinelifeL->isAttachedToDiver 
				&& marinelifeL->getMarineLifeRect().intersectsRect(diverL->getDiverRect()) )
			{
				if( ((FeverLayer*)getChildByTag(kTagFever))->isFever() )
				{
					marinelifeL->aliveMarineLifeTouched();
				} 
				else
				{
					marinelifeL->attachToDiver(diverL->getPosition().x, diverL->getPosition().y);
					diverL->refreshDiverPositionWithDolphin();

					if(diverL->isLove)
					{
						saveAllGameResult();
						toEndGameSceneWithLove();
					}
				}
			}
		}
		// Check between "diver" and "rope"
		else if( kTagRope == ((Node*)pObj)->getTag() )
		{
			ropeL = static_cast<Rope*>(pObj);

			if(!ropeL)
				break;

			if( ropeL->getSpriteRepeaterRect().intersectsRect(diverL->getDiverRect()) )
			{
				if( ((FeverLayer*)getChildByTag(kTagFever))->isFever() )
					diveWithTimes(2*(diverL->lapCount));
					//diveWithTimes(8);
				else
					diveWithTimes(1*(diverL->lapCount));
					//diveWithTimes(4);
			} else {
				diveWithTimes(0+((diverL->lapCount-1)*1));
				//diveWithTimes(2);
			}
		}
	}
}

void MainGameBaseLayer::diveWithTimes(int timesValue)
{
	Color3B colorRope;
	Rope* ropeL = (Rope*)getChildByTag(kTagRope);
	Rocks* rocks = (Rocks*)getChildByTag(kTagRocks);

	((DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet))->setDiveStep(timesValue);
	
	(0 == timesValue) ? ropeL->setColor(Color3B::RED) :ropeL->setColor(Color3B::ORANGE);

	ropeL->setTimeScale(timesValue);
	rocks->setTimeScale(timesValue);
}

void MainGameBaseLayer::toEndGameSceneWithLove()
{
	// ADMOB JNI
	AdmobJNI::setAdmobVisible(false, true);

	EndGameScene *scene = EndGameScene::create();

	// clone Diver
	DiverLayer* diverCloneL = ((DiverLayer*)getChildByTag(kTagLayerDiver))->clone();
	diverCloneL->refreshLoveSprite();
	scene->addChild(diverCloneL, 1, kTagLayerDiver);

	// clone Marinelife
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagForMarinelifes < ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(marinelifeL && marinelifeL->isAttachedToDiver)
			{
				MarineLifeLayer* marinelifeCloneL = marinelifeL->clone();
				marinelifeCloneL->attachToDiver(marinelifeL->getPositionX(), marinelifeL->getPositionY());
				scene->addChild(marinelifeCloneL, 0, kTagForMarinelifes);
			}
		}
	}

	// start love event
	scene->runLoveEvent();

	Director::getInstance()->replaceScene(scene);
}

void MainGameBaseLayer::playBubbleEffect(float dt) 
{
	Sound::playBubbleEffect();
}

void MainGameBaseLayer::checkFeet(float dt)
{
	DiveFeetLayer* divefeetL = (DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet);
	if( divefeetL->isMaxDivedFeetAtScene(iMaxFeet) )
	{
		readyToGoNextScene();
	}
	/*if( iMaxFeet <= divefeetL->getDivedFeet() )
	{
		readyToGoNextScene();
	}*/
}

void MainGameBaseLayer::readyToGoNextScene()
{
	// ---- WARNING : Can't call child class's addMarinelife()  -----
	/*unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.2f);*/
}

void MainGameBaseLayer::checkRemainUnattachedMarinlife(float dt)
{
	if(!existUnattachedMarinlife())
	{
		saveAllGameData();
		goToNextGameScene();
	} 
}

bool MainGameBaseLayer::existUnattachedMarinlife()
{
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagForMarinelifes < ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(marinelifeL && !marinelifeL->isAttachedToDiver)
			{
				return true;
			}
		}
	}

	return false;
}

void MainGameBaseLayer::saveAllGameResult()
{
	MainGameDataLayer::saveAllGameResult( ((DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet))->getDivedFeet(), 
										  ((FeverLayer*)getChildByTag(kTagFever))->getMarinelifeBye(), 
										  ((DiverLayer*)getChildByTag(kTagLayerDiver))->lovePoint, 
										  ((FeverLayer*)getChildByTag(kTagFever))->getFeverCount(),
										  ((DiverLayer*)getChildByTag(kTagLayerDiver))->lapCount);
}

void MainGameBaseLayer::saveAllGameData()
{
	saveDiverData();
	saveDivedFeetData();
	saveFeverData();
	saveRocksData();
}

void MainGameBaseLayer::saveDiverData()
{
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	MainGameDataLayer::saveDiver(diverL);
}

void MainGameBaseLayer::saveDivedFeetData()
{
	DiveFeetLayer* diveFeetL = (DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet);
	MainGameDataLayer::saveDivedFeet(diveFeetL);
}

void MainGameBaseLayer::saveFeverData()
{
	FeverLayer* feverL = (FeverLayer*)getChildByTag(kTagFever);
	MainGameDataLayer::saveFever(feverL);
}

void MainGameBaseLayer::saveRocksData()
{
	Rocks* rocksS = (Rocks*)getChildByTag(kTagRocks);
	MainGameDataLayer::saveRocks(rocksS);
}

void MainGameBaseLayer::addAttachedMarinelife(Layer* lyr)
{
	// clone marinelife
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagForMarinelifes < ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(marinelifeL && marinelifeL->isAttachedToDiver)
			{
				MarineLifeLayer* marinelifeCloneL = marinelifeL->clone();
				marinelifeCloneL->attachToDiver(marinelifeL->getPositionX(), marinelifeL->getPositionY());
				lyr->addChild(marinelifeCloneL, 0, iTagForMarinelife);
			}
		}
	}
}

void MainGameBaseLayer::goToNextGameScene()
{
}

void MainGameBaseLayer::addFever()
{
	FeverLayer* feverL = MainGameDataLayer::loadFever();
	addChild(feverL, 1, kTagFever);
	feverL->checkFeverOnNewScene();
}