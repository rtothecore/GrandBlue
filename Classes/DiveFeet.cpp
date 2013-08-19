#include "DiveFeet.h"
#include "MenuLabel.h"

enum {
    kTagMLDiveFeet = 1,
};

bool DiveFeetLayer::init()
{
	currentDivedFeet = 0;
	diveStep = 1;

	//initWithLabel();

	return true;
}

void DiveFeetLayer::initWithLabel()
{
	// create menu label
	MenuLabelLayer* ml_diveFeet = MenuLabelLayer::create();
	char chrFeet[9] = {0};
	sprintf(chrFeet, "%d Feet", currentDivedFeet);
	ml_diveFeet->initWithLabel(chrFeet, 2.0f);
	ml_diveFeet->createMenu();
	addChild(ml_diveFeet, 1, kTagMLDiveFeet);
}

void DiveFeetLayer::startDive()
{
	initWithLabel();

	schedule( schedule_selector(DiveFeetLayer::incrementDiveFeet), 2.0f );
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
	((MenuLabelLayer*)getChildByTag(kTagMLDiveFeet))->renameMenuItem(0, chrDiveFeet);
}

void DiveFeetLayer::setDiveStep(int diveStepVal, float timeVal)
{
	diveStep = diveStepVal;
	scheduleOnce( schedule_selector(DiveFeetLayer::resetDiveStep), timeVal );
}

void DiveFeetLayer::resetDiveStep(float dt)
{
	diveStep = 1;
}

int DiveFeetLayer::getDivedFeet()
{
	return currentDivedFeet;
}

void DiveFeetLayer::setDivedFeet(int divedFeetValue)
{
	currentDivedFeet = divedFeetValue;
}

