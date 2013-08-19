#include "MainGameData.h"
#include "DiveFeet.h"

bool MainGameDataLayer::isSaveDiver;

bool MainGameDataLayer::init()
{
	MainGameDataLayer::isSaveDiver = false;

	return true;
}

void MainGameDataLayer::saveDiver(DiverLayer* diverL)
{
	UserDefault::getInstance()->setFloatForKey("diverPosX", diverL->getPositionX());
	UserDefault::getInstance()->setFloatForKey("diverPosY", diverL->getPositionY());

	UserDefault::getInstance()->setFloatForKey("diverAncX", diverL->getAnchorPoint().x);
	UserDefault::getInstance()->setFloatForKey("diverAncY", diverL->getAnchorPoint().y);

	UserDefault::getInstance()->setIntegerForKey("diverLovePoint", diverL->lovePoint);
	UserDefault::getInstance()->setBoolForKey("diverIsLove", diverL->isLove);

	MainGameDataLayer::isSaveDiver = true;
}

DiverLayer* MainGameDataLayer::loadDiver()
{
	DiverLayer* ret = DiverLayer::create();

	if( MainGameDataLayer::isSaveDiver )
	{
		ret->setPosition( Point(UserDefault::getInstance()->getFloatForKey("diverPosX"), 
								UserDefault::getInstance()->getFloatForKey("diverPosY")) );
		ret->setAnchorPoint( Point(UserDefault::getInstance()->getFloatForKey("diverAncX"), 
								   UserDefault::getInstance()->getFloatForKey("diverAncY")) );
		ret->lovePoint = UserDefault::getInstance()->getIntegerForKey("diverLovePoint");
		ret->isLove = UserDefault::getInstance()->getBoolForKey("diverIsLove");

		ret->refreshDiver();
	}

	return ret;
}

bool MainGameDataLayer::isSaveDivedFeet;

void MainGameDataLayer::saveDivedFeet(DiveFeetLayer* diveFeetL)
{
	diveFeetL->stopDive();
	UserDefault::getInstance()->setIntegerForKey("divedFeet", diveFeetL->getDivedFeet());

	MainGameDataLayer::isSaveDivedFeet = true;
}

DiveFeetLayer* MainGameDataLayer::loadDivedFeet()
{
	DiveFeetLayer* ret = DiveFeetLayer::create();

	if(MainGameDataLayer::isSaveDivedFeet)
	{
		ret->setDivedFeet( UserDefault::getInstance()->getIntegerForKey("divedFeet") );
	}

	return ret;
}

bool MainGameDataLayer::isSaveFever;

void MainGameDataLayer::saveFever(FeverLayer* feverL)
{
	UserDefault::getInstance()->setIntegerForKey("marinelifeBye", feverL->getMarinelifeBye());
	UserDefault::getInstance()->setIntegerForKey("touchCombo", feverL->getTouchCombo());

	MainGameDataLayer::isSaveFever = true;
}

FeverLayer* MainGameDataLayer::loadFever()
{
	FeverLayer* ret = FeverLayer::create();

	if(MainGameDataLayer::isSaveFever)
	{
		ret->setMarinelifeBye( UserDefault::getInstance()->getIntegerForKey("marinelifeBye") );
		ret->setTouchCombo( UserDefault::getInstance()->getIntegerForKey("touchCombo") );

		ret->refreshProgressBar();
	}

	return ret;
}