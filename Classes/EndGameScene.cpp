#include "EndGameScene.h"
#include "Diver.h"
#include "MarineLife.h"
#include "MainGameBase.h"
#include "Tags.h"
#include "MenuLabel.h"
#include "MainGameScene.h"
#include "MainGameData.h"
#include "MainTitleScene.h"
#include "Score.h"

bool EndGameScene::init()
{
	return true;
}

void EndGameScene::runLoveEvent()
{
	scheduleOnce( schedule_selector(EndGameScene::actionLove), 3);
}

void EndGameScene::actionLove(float dt)
{
	// marinelife love action
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagForMarinelifes == ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(marinelifeL && marinelifeL->isAttachedToDiver)
				marinelifeL->runLoveAction();
		}
	}

	// diver love action
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	diverL->runLoveAction();

	// score
	addScoreLabel();

	// continue menu
	scheduleOnce( schedule_selector(EndGameScene::addContinueMenu), 2.0f );
}

void EndGameScene::addContinueMenu(float dt)
{
	MenuLabelLayer* labelContinue = MenuLabelLayer::create();
	labelContinue->initWithLabel("Continue", 3.0f);
	labelContinue->addMenuItem("Exit", 3.0f);
	labelContinue->createMenu();
	labelContinue->setZOrder(1);
	labelContinue->setPosition(0, -100);

	// set "continue" callback
	Menu* labelMenu = (Menu*)labelContinue->getChildByTag(0);
	MenuItemLabel* labelMenuItem = (MenuItemLabel*)labelMenu->getChildByTag(0);
	labelMenuItem->setCallback( CC_CALLBACK_1(EndGameScene::continueGameCallback, this) );

	// set "exit" callback
	labelMenuItem = (MenuItemLabel*)labelMenu->getChildByTag(1);
	labelMenuItem->setCallback( CC_CALLBACK_1(EndGameScene::endGameCallback, this) );

	addChild(labelContinue);
}

void EndGameScene::addScoreLabel()
{
	// score
	ScoreLayer* scoreL = ScoreLayer::create();
	addChild(scoreL, 2);
}

void EndGameScene::continueGameCallback(Object* pSender)
{
	MainGameDataLayer::resetAllData();

	Scene* scene = MainGameScene::create();
	Director::getInstance()->replaceScene(scene);
}

void EndGameScene::endGameCallback(Object* pSender)
{
	MainGameDataLayer::resetAllData();

	Scene *scene = TransitionSlideInT::create(2, MainTitleScene::create());
	Director::getInstance()->replaceScene(scene);
}