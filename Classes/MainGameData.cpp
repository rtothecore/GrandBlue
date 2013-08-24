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

void MainGameDataLayer::resetDiver()
{
	UserDefault::getInstance()->setFloatForKey("diverPosX", 0);
	UserDefault::getInstance()->setFloatForKey("diverPosY", 0);

	UserDefault::getInstance()->setFloatForKey("diverAncX", 0);
	UserDefault::getInstance()->setFloatForKey("diverAncY", 0);

	UserDefault::getInstance()->setIntegerForKey("diverLovePoint", 0);
	UserDefault::getInstance()->setBoolForKey("diverIsLove", 0);

	MainGameDataLayer::isSaveDiver = false;
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

void MainGameDataLayer::resetDivedFeet()
{
	UserDefault::getInstance()->setIntegerForKey("divedFeet", 0);

	MainGameDataLayer::isSaveDivedFeet = false;
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

void MainGameDataLayer::resetFever()
{
	UserDefault::getInstance()->setIntegerForKey("marinelifeBye", 0);
	UserDefault::getInstance()->setIntegerForKey("touchCombo", 0);

	MainGameDataLayer::isSaveFever = false;
}

void MainGameDataLayer::resetAllData()
{
	resetDiver();
	resetDivedFeet();
	resetFever();
}

void MainGameDataLayer::saveAllGameResult(int DivedFeet, int ByeCount, int LovePoint)
{
	UserDefault::getInstance()->setIntegerForKey("divedFeet", DivedFeet);
	UserDefault::getInstance()->setIntegerForKey("marinelifeBye", ByeCount);
	UserDefault::getInstance()->setIntegerForKey("diverLovePoint", LovePoint);
}

int MainGameDataLayer::getDivedFeet()
{
	if( UserDefault::getInstance()->getIntegerForKey("divedFeet") )
		return UserDefault::getInstance()->getIntegerForKey("divedFeet");
	else
		return 0;
}

int MainGameDataLayer::getByeCount()
{
	if( UserDefault::getInstance()->getIntegerForKey("marinelifeBye") )
		return UserDefault::getInstance()->getIntegerForKey("marinelifeBye");
	else
		return 0;
}

int MainGameDataLayer::getLovePoint()
{
	if( UserDefault::getInstance()->getIntegerForKey("diverLovePoint") )
		return UserDefault::getInstance()->getIntegerForKey("diverLovePoint");
	else
		return 0;
}

int MainGameDataLayer::getComboCount()
{
	if( UserDefault::getInstance()->getIntegerForKey("touchCombo") )
		return UserDefault::getInstance()->getIntegerForKey("touchCombo");
	else
		return 0;
}
