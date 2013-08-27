#include "Fever.h"
#include "Sound.h"
#include "ProgressBar.h"
#include "UtilFunc.h"
#include "Tags.h"
#include "Diver.h"
#include "Resource.h"
#include "AppMacros.h"
#include "Particle.h"

enum {
	kTagFeverProgressBar = 1,
};

bool FeverLayer::init()
{
	bFeverMode = false;
	iMarineLifeBye = 0;
	iFeverCount = 0;
	iTouchCombo = 0;

	initProgressBar();

	return true;
}

void FeverLayer::setFever(bool isFever)
{
	bFeverMode = isFever;
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

void FeverLayer::checkFeverOnNewScene()
{
	if(st_touchComboForFever <= iTouchCombo)
	{
		intoTheFever();

		LabelTTF* labelFever = (LabelTTF*)getChildByTag(kTagLabelFever);
		labelFever->setString("Fever Time x2!!!! ");

		scheduleOnce( schedule_selector(FeverLayer::endFever), st_feverTime );
	} 
}

void FeverLayer::intoTheFever()
{
	bFeverMode = true;

	// add fever label
	addFeverLabel();

	// particle effect
	ParticleSystem* _emitter = ParticleLayer::createWithParticlePlist("particles/BlueRing_fever.plist");
	_emitter->setPosition(UtilFunc::getWinSize().width/2, UtilFunc::getWinSize().height/2);
	addChild(_emitter, kTagParticleFever);

	// fever music
	Sound::playFeverMusic(true);

	// fever count++
	iFeverCount++;

	// run Diver's fever mode
	((DiverLayer*)getParent()->getChildByTag(kTagLayerDiver))->runFevermodeAction();
}

void FeverLayer::addFeverLabel()
{
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width, winSize.height/20);

	auto labelFever = LabelTTF::create("Fever Time!!!! ", FONT_MENU_FILE, FEVER_FONT_SIZE, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);

	Point dstPoint = Point(winSize.width/4, winSize.height/2 + labelFever->getContentSize().height*2);
	int offset = (int) (winSize.width/2 + 50);

	labelFever->setPosition(  Point( dstPoint.x + offset, dstPoint.y) );
	labelFever->setColor(Color3B::YELLOW);
	labelFever->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );

	addChild(labelFever, 1, kTagLabelFever);
}

void FeverLayer::endFever(float dt)
{
	bFeverMode = false;
	resetTouchCombo();

	// remove fever label
	removeChildByTag(kTagLabelFever);

	// background music
	Sound::playBackgroundMusic(true);

	// exit Diver's fever mode
	((DiverLayer*)getParent()->getChildByTag(kTagLayerDiver))->exitFevermodeAction();

	// remove particle
	removeChildByTag(kTagParticleFever);
}

int FeverLayer::getTouchDamage()
{
	return bFeverMode ? st_touchDamageFever : st_touchDamage;
}

bool FeverLayer::isFever()
{
	return bFeverMode;
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

int FeverLayer::getFeverCount()
{
	return iFeverCount;
}

void FeverLayer::setFeverCount(int feverVal)
{
	iFeverCount = feverVal;
}