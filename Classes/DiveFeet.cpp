#include "DiveFeet.h"
#include "MenuLabel.h"
#include "Tags.h"
#include "Resource.h"

bool DiveFeetLayer::init()
{
	currentDivedFeet = 0;
	diveStep = 1;

	return true;
}

void DiveFeetLayer::initWithLabel()
{
	// create feet label
	char chrDiveFeet[9] = {0};
	sprintf(chrDiveFeet, "%d Feet", currentDivedFeet);

	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/20);
    float fontSize = 18;
	auto labelFeet = LabelTTF::create(chrDiveFeet, FONT_MENU_FILE, fontSize, 
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

	// rename menu label
	char chrDiveFeet[9] = {0};
	sprintf(chrDiveFeet, "%d Feet", currentDivedFeet);
	((LabelTTF*)getChildByTag(kTagLabelDiveFeet))->setString(chrDiveFeet);
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
}

