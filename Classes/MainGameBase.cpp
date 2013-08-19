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

void MainGameBaseLayer::increaseMarineLifeBye()
{
	MainGameBaseLayer::iMarineLifeBye++;
}

void MainGameBaseLayer::onEnterTransitionDidFinish()
{
}

void MainGameBaseLayer::menuBackCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInT::create(2, MainTitleScene::create());
	Director::getInstance()->pushScene(scene);
}

void MainGameBaseLayer::byeMenuLabelRefresh(float dt)
{
	MenuLabelLayer* mLabelL = (MenuLabelLayer*)getChildByTag(kTagMainGameMenuLabel);
	char chrDolphinBye[12] = {0};
	sprintf(chrDolphinBye, "%d/%d/%d", MainGameBaseLayer::iMarineLifeBye, 
										((FeverLayer*)getChildByTag(kTagFever))->getTouchComboForFever(), 
										((FeverLayer*)getChildByTag(kTagFever))->getTouchCombo() );

	if( ((FeverLayer*)getChildByTag(kTagFever))->isFever() )
	{
		mLabelL->renameMenuItem(0, "Fever Time!!!!");
	} else {
		mLabelL->renameMenuItem(0, "MarineLife's Bye");
	}

	mLabelL->renameMenuItem(1, chrDolphinBye);
}

bool MainGameBaseLayer::containsMarinelifeLocation(Touch* touch)
{
	/* ORIGINAL
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	DolphinLayer* dolphinL;
	

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagLayerDolphin == ((Node*)pObj)->getTag() )
		{
			dolphinL = static_cast<DolphinLayer*>(pObj);

			if(!dolphinL)
				break;

			if( !dolphinL->getRect().containsPoint(convertTouchToNodeSpaceAR(touch)) )
				return false;
		}
	}*/

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
	/* ORIGINAL
	DolphinLayer* dolphinL;
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	Object* pObj = NULL;

	Array *arrChildren = getChildren();

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagLayerDolphin == ((Node*)pObj)->getTag() )
		{
			dolphinL = static_cast<DolphinLayer*>(pObj);

			if(!dolphinL)
				break;

			if( !diverL->isLove
				&& !dolphinL->isBye
				&& !dolphinL->isAttachedToDiver 
				&& dolphinL->getMarineLifeRect().intersectsRect(diverL->getDiverRect()) )
			{
				log("Dolphin meet diver~^^");

				dolphinL->attachToDiver(diverL->getPosition().x, diverL->getPosition().y);
				diverL->refreshDiverPositionWithDolphin();
				((DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet))->setDiveStep(5, 5);

				if(diverL->isLove)
				{
					toEndGameSceneWithLove();
				}

				return true;
			}
		}
	}*/

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
	// ORIGINAL
	//EndGameScene *scene = EndGameScene::create();

	//// clone Diver
	//DiverLayer* diverCloneL = ((DiverLayer*)getChildByTag(kTagLayerDiver))->clone();
	//scene->addChild(diverCloneL, 1, kTagLayerDiver);

	//// clone Dolphin
	//Array *arrChildren = getChildren();
	//Object* pObj = NULL;
	//DolphinLayer* dolphinL;

	//CCARRAY_FOREACH(arrChildren, pObj)
	//{
	//	if( kTagLayerDolphin == ((Node*)pObj)->getTag() )
	//	{
	//		dolphinL = static_cast<DolphinLayer*>(pObj);

	//		if(dolphinL && dolphinL->isAttachedToDiver)
	//		{
	//			DolphinLayer* dolphinCloneL = dolphinL->clone();
	//			dolphinCloneL->attachToDiver(dolphinL->getPositionX(), dolphinL->getPositionY());
	//			scene->addChild(dolphinCloneL, 0, kTagLayerDolphin);
	//		}
	//	}
	//}

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
	if( iMaxFeet <= divefeetL->getCurrentFeet() )
	{
		saveDiverData();
		goToNextGameScene();
	}
}

void MainGameBaseLayer::saveDiverData()
{
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	MainGameDataLayer::saveDiver(diverL);
}

void MainGameBaseLayer::addAttachedMarinelife(Layer* lyr)
{
	// clone marinelife
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( iTagForMarinelife == ((Node*)pObj)->getTag() )
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