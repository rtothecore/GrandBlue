#include "DiveFeet.h"
#include "MenuLabel.h"
#include "Tags.h"
#include "Resource.h"
#include "GrandBlueConfig.h"
#include "AppMacros.h"

bool DiveFeetLayer::init()
{
	currentDivedFeet = 0;
	diveStep = 1;
	sceneDivedFeet = 0;

	return true;
}

void DiveFeetLayer::initWithLabel()
{
	// create feet label
	String* strDiveFeet = String::createWithFormat("%d Feet", currentDivedFeet);

	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/20);

	auto labelFeet = LabelTTF::create(strDiveFeet->getCString(), FONT_MENU_FILE, DIVEFEET_FONT_SIZE, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	labelFeet->setPosition(Point(winSize.width/2, winSize.height/2));

    addChild(labelFeet, 1, kTagLabelDiveFeet);
}

void DiveFeetLayer::startDive()
{
	initWithLabel();

	schedule( schedule_selector(DiveFeetLayer::incrementDiveFeet), 1.0f );
}

void DiveFeetLayer::stopDive()
{
	unschedule( schedule_selector(DiveFeetLayer::incrementDiveFeet) );
}

void DiveFeetLayer::incrementDiveFeet(float dt)
{
	currentDivedFeet += diveStep;

	sceneDivedFeet += diveStep;

	// rename menu label
	String* strDiveFeet = String::createWithFormat("%d Feet", currentDivedFeet);
	((LabelTTF*)getChildByTag(kTagLabelDiveFeet))->setString(strDiveFeet->getCString());
}

void DiveFeetLayer::setDiveStepWithTime(int diveStepVal, float timeVal)
{
	diveStep = diveStepVal;
	scheduleOnce( schedule_selector(DiveFeetLayer::resetDiveStep), timeVal );
}

void DiveFeetLayer::resetDiveStep(float dt)
{
	diveStep = 1;
}

void DiveFeetLayer::setDiveStep(int diveStepVal)
{
	diveStep = diveStepVal;
}

int DiveFeetLayer::getDivedFeet()
{
	return currentDivedFeet;
}

void DiveFeetLayer::setDivedFeet(int divedFeetValue)
{
	currentDivedFeet = divedFeetValue;

	sceneDivedFeet = currentDivedFeet % MAX_DIVE_FEET_AT_ONE_SCENE;
}

bool DiveFeetLayer::isMaxDivedFeetAtScene(int maxDivedFeet)
{
	if(maxDivedFeet <= sceneDivedFeet)
	{
		return true;
	}

	return false;
}

