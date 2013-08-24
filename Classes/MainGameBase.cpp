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

bool MainGameBaseLayer::init()
{
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

void MainGameBaseLayer::addComboLabel()
{
	// combo label
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/4);
    float fontSize = 18;

	char chrComboLabel[20] = {0};
	sprintf(chrComboLabel, "Bye: %d\nCombo: %d", MainGameDataLayer::getByeCount(), MainGameDataLayer::getComboCount());
	auto labelCombo = LabelTTF::create(chrComboLabel, FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::LEFT, Label::VAlignment::CENTER);
	labelCombo->setPosition( Point(winSize.width - labelCombo->getContentSize().width/4, labelCombo->getContentSize().height/4) );
    addChild(labelCombo, 2, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameBaseLayer::comboLabelRefresh), 0.5);
}

void MainGameBaseLayer::addMarinelife(float dt)
{
}

void MainGameBaseLayer::comboLabelRefresh(float dt)
{
	LabelTTF* labelCombo = (LabelTTF*)getChildByTag(kTagMainGameMenuLabel);
	char chrMarinelifeBye[30] = {0};
	sprintf(chrMarinelifeBye, "Bye: %d\nCombo: %d", ((FeverLayer*)getChildByTag(kTagFever))->getMarinelifeBye(), 
			((FeverLayer*)getChildByTag(kTagFever))->getTouchCombo() );
	labelCombo->setString(chrMarinelifeBye);
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
	if ( !containsMarinelifeLocation(touch) )
	{
		// reset Touch Combo
		log("TOUCH MISS!!!!");
		((FeverLayer*)getChildByTag(kTagFever))->resetTouchCombo();

		return false;
	}

    return true;
}

void MainGameBaseLayer::ccTouchMoved(Touch* touch, Event* event)
{
}

void MainGameBaseLayer::ccTouchEnded(Touch* touch, Event* event)
{    
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

			if( !diverL->isLove
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
					diveWithTimes(2);
					//diveWithTimes(8);
				else
					diveWithTimes(1);
					//diveWithTimes(4);
			} else {
				diveWithTimes(0);
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

	(1 == timesValue) ? colorRope = Color3B::RED : colorRope = Color3B::ORANGE;
	ropeL->setColorToAllSprite(colorRope);

	ropeL->setTimeScale(timesValue);
	rocks->setTimeScale(timesValue);
}

void MainGameBaseLayer::toEndGameSceneWithLove()
{
	EndGameScene *scene = EndGameScene::create();

	// clone Diver
	DiverLayer* diverCloneL = ((DiverLayer*)getChildByTag(kTagLayerDiver))->clone();
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
	if( iMaxFeet <= divefeetL->getDivedFeet() )
	{
		readyToGoNextScene();
	}
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
										  ((DiverLayer*)getChildByTag(kTagLayerDiver))->lovePoint );
}

void MainGameBaseLayer::saveAllGameData()
{
	saveDiverData();
	saveDivedFeetData();
	saveFeverData();
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