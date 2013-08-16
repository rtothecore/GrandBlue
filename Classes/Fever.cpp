#include "Fever.h"
#include "Sound.h"
#include "ProgressBar.h"
#include "UtilFunc.h"

enum {
	kTagFeverProgressBar = 1,
};

bool FeverLayer::init()
{
	bFeverMode = false;
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

	// fever music
	Sound::playFeverMusic(true);
}

void FeverLayer::endFever(float dt)
{
	log("End Fever...");

	bFeverMode = false;
	resetTouchCombo();

	// background music
	Sound::playBackgroundMusic(true);
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