#include "MainGameData.h"
#include "DiveFeet.h"
#include "Resource.h"

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

	UserDefault::getInstance()->setIntegerForKey("diverLapCount", diverL->lapCount);

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
		ret->lapCount = UserDefault::getInstance()->getIntegerForKey("diverLapCount");

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
	UserDefault::getInstance()->setIntegerForKey("diverLapCount", 1);

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
	UserDefault::getInstance()->setBoolForKey("feverMode", feverL->isFever());
	UserDefault::getInstance()->setIntegerForKey("feverCount", feverL->getFeverCount());

	MainGameDataLayer::isSaveFever = true;
}

FeverLayer* MainGameDataLayer::loadFever()
{
	FeverLayer* ret = FeverLayer::create();

	if(MainGameDataLayer::isSaveFever)
	{
		ret->setMarinelifeBye( UserDefault::getInstance()->getIntegerForKey("marinelifeBye") );
		ret->setTouchCombo( UserDefault::getInstance()->getIntegerForKey("touchCombo") );
		ret->setFever( UserDefault::getInstance()->getBoolForKey("feverMode") );
		ret->setFeverCount( UserDefault::getInstance()->getIntegerForKey("feverCount") );

		ret->refreshProgressBar();
	}

	return ret;
}

void MainGameDataLayer::resetFever()
{
	UserDefault::getInstance()->setIntegerForKey("marinelifeBye", 0);
	UserDefault::getInstance()->setIntegerForKey("touchCombo", 0);
	UserDefault::getInstance()->setIntegerForKey("feverCount", 0);

	MainGameDataLayer::isSaveFever = false;
}

bool MainGameDataLayer::isSaveRocks = false;

void MainGameDataLayer::saveRocks(Rocks* rocks)
{
	UserDefault::getInstance()->setFloatForKey("rocksPosition", rocks->stopActionAndGetPositionY());

	MainGameDataLayer::isSaveRocks = true;
}

Rocks* MainGameDataLayer::loadRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* ret = Rocks::create();

	if(MainGameDataLayer::isSaveRocks)
	{
		ret->setStartY( UserDefault::getInstance()->getFloatForKey("rocksPosition") );
	}
	ret->initWithTexture(rocksTexture, 1);

	return ret;
}

void MainGameDataLayer::resetRocks()
{
	UserDefault::getInstance()->setFloatForKey("rocksPosition", 0);

	MainGameDataLayer::isSaveRocks = false;
}

void MainGameDataLayer::resetAllData()
{
	resetDiver();
	resetDivedFeet();
	resetFever();
	resetRocks();
}

void MainGameDataLayer::saveAllGameResult(int DivedFeet, int ByeCount, int LovePoint, int FeverCount, int DiverLapCount)
{
	UserDefault::getInstance()->setIntegerForKey("divedFeet", DivedFeet);
	UserDefault::getInstance()->setIntegerForKey("marinelifeBye", ByeCount);
	UserDefault::getInstance()->setIntegerForKey("diverLovePoint", LovePoint);
	UserDefault::getInstance()->setIntegerForKey("feverCount", FeverCount);
	UserDefault::getInstance()->setIntegerForKey("diverLapCount", DiverLapCount);
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

int MainGameDataLayer::getFeverCount()
{
	if( UserDefault::getInstance()->getIntegerForKey("feverCount") )
		return UserDefault::getInstance()->getIntegerForKey("feverCount");
	else
		return 0;
}

int MainGameDataLayer::getDiverLapCount()
{
	if( UserDefault::getInstance()->getIntegerForKey("diverLapCount") )
		return UserDefault::getInstance()->getIntegerForKey("diverLapCount");
	else
		return 1;
}
