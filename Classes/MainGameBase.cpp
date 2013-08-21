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
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// combo label
	auto labelCombo = LabelBMFont::create("Bye:999\nCombo:999", "fonts/Blippo.fnt");
	labelCombo->setPosition(visibleSize.width - labelCombo->getContentSize().width*2, labelCombo->getContentSize().height*2 );
	labelCombo->setScale(2.0f);
    addChild(labelCombo, 2, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameBaseLayer::comboLabelRefresh), 0.5);
}

void MainGameBaseLayer::addMarinelife(float dt)
{
}

void MainGameBaseLayer::comboLabelRefresh(float dt)
{
	LabelBMFont* labelCombo = (LabelBMFont*)getChildByTag(kTagMainGameMenuLabel);
	char chrMarinelifeBye[30] = {0};

	sprintf(chrMarinelifeBye, "Bye:%d\nCombo:%d", ((FeverLayer*)getChildByTag(kTagFever))->getMarinelifeBye(), 
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

bool MainGameBaseLayer::checkCollision()
{
	MarineLifeLayer* marinelifeL;
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	Object* pObj = NULL;

	Array *arrChildren = getChildren();

	CCARRAY_FOREACH(arrChildren, pObj)
	{
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
				log("Marinelife meet diver~^^");

				marinelifeL->attachToDiver(diverL->getPosition().x, diverL->getPosition().y);
				diverL->refreshDiverPositionWithDolphin();
				((DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet))->setDiveStep(5, 5);

				if(diverL->isLove)
				{
					toEndGameSceneWithLove();
				}

				return true;
			}
		}
	}

	return false;
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