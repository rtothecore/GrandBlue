#include "Fever.h"
#include "Sound.h"
#include "ProgressBar.h"
#include "UtilFunc.h"
#include "Tags.h"
#include "Diver.h"

enum {
	kTagFeverProgressBar = 1,
};

bool FeverLayer::init()
{
	bFeverMode = false;
	iMarineLifeBye = 0;
	iTouchCombo = 0;

	initProgressBar();

	return true;
}

void FeverLayer::initProgressBar()
{
	ProgressBarLayer* pbLayer = ProgressBarLayer::create();
	pbLayer->initWithSize(UtilFunc::getWinSize().width, 10, 5);
	pbLayer->setPosition(0, 0);
	addChild(pbLayer, 1, kTagFeverProgressBar);
}

void FeverLayer::refreshProgressBar()
{
	((ProgressBarLayer*)getChildByTag(kTagFeverProgressBar))->setProgressWithTagetVal(iTouchCombo);
}

void FeverLayer::increaseTouchCombo()
{
	if(!bFeverMode)
	{
		iTouchCombo++;
		refreshProgressBar();

		checkFever();
	}
}

void FeverLayer::resetTouchCombo()
{
	if(!bFeverMode)
	{
		iTouchCombo = 0;
		refreshProgressBar();
	}
}

void FeverLayer::checkFever()
{
	if(st_touchComboForFever <= iTouchCombo)
	{
		intoTheFever();
		scheduleOnce( schedule_selector(FeverLayer::endFever), st_feverTime );
	} 
}

void FeverLayer::intoTheFever()
{
	log("Fever Time!!!");

	bFeverMode = true;

	// add fever label
	addFeverLabel();

	// fever music
	Sound::playFeverMusic(true);

	// run Diver's fever mode
	((DiverLayer*)getParent()->getChildByTag(kTagLayerDiver))->runFevermodeAction();
}

void FeverLayer::addFeverLabel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto labelFever = LabelBMFont::create("Fever Time!!!!", "fonts/Blippo.fnt");
	labelFever->setScale(4.0f);

	Point dstPoint = Point(visibleSize.width/4, visibleSize.height/2 + labelFever->getContentSize().height*2);
	int offset = (int) (visibleSize.width/2 + 50);

	labelFever->setPosition(  Point( dstPoint.x + offset, dstPoint.y) );
	labelFever->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );

	addChild(labelFever, 1, kTagLabelFever);
}

void FeverLayer::endFever(float dt)
{
	log("End Fever...");

	bFeverMode = false;
	resetTouchCombo();

	// remove fever label
	removeChildByTag(kTagLabelFever);

	// background music
	Sound::playBackgroundMusic(true);

	// exit Diver's fever mode
	((DiverLayer*)getParent()->getChildByTag(kTagLayerDiver))->exitFevermodeAction();
}

int FeverLayer::getTouchDamage()
{
	return bFeverMode ? st_touchDamageFever : st_touchDamage;
}

bool FeverLayer::isFever()
{
	return bFeverMode;
}

int FeverLayer::getTouchComboForFever()
{
	return st_touchComboForFever;
}

int FeverLayer::getTouchCombo()
{
	return iTouchCombo;
}

void FeverLayer::increaseMarinelifeBye()
{
	iMarineLifeBye++;
}

int FeverLayer::getMarinelifeBye()
{
	return iMarineLifeBye;
}

void FeverLayer::setTouchCombo(int touchComboVal)
{
	iTouchCombo = touchComboVal;
}

void FeverLayer::setMarinelifeBye(int mlByeVal)
{
	iMarineLifeBye = mlByeVal;
}