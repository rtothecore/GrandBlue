#include "MainGameData.h"

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