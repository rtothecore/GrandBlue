#include "DiveFeet.h"
#include "MenuLabel.h"
#include "Tags.h"

bool DiveFeetLayer::init()
{
	currentDivedFeet = 0;
	diveStep = 1;

	return true;
}

void DiveFeetLayer::initWithLabel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// create feet label
	char chrDiveFeet[9] = {0};
	sprintf(chrDiveFeet, "%d Feet", currentDivedFeet);
	auto labelFeet = LabelBMFont::create(chrDiveFeet, "fonts/Blippo.fnt");
	labelFeet->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	labelFeet->setScale(3.0f);
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
	((LabelBMFont*)getChildByTag(kTagLabelDiveFeet))->setString(chrDiveFeet);
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

