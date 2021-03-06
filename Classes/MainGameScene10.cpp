#include "MainGameScene10.h"
#include "Brain.h"
#include "MenuLabel.h"
#include "Resource.h"
#include "SpriteRepeater.h"
#include "Sound.h"
#include "Background.h"
#include "ProgressBar.h"
#include "DiveFeet.h"
#include "Fever.h"
#include "Diver.h"
#include "Tags.h"
#include "MainGameData.h"
#include "GrandBlueConfig.h"
#include "MainGameScene.h"
#include "AdmobJNI.h"

//------------------------------------------------------------------
//
// MainGameScene10
//
//------------------------------------------------------------------
bool MainGameScene10::init()
{
	MainGameLayer10 *MainGameLayer10 = MainGameLayer10::create();
    addChild(MainGameLayer10, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer10
//
//------------------------------------------------------------------
bool MainGameLayer10::init()
{
	iMaxFeet = MAX_DIVE_FEET_AT_ONE_SCENE;
	iTagForMarinelife = kTagLayerBrain;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(true, true);

	return true;
}

void MainGameLayer10::onEnterTransitionDidFinish()
{
	// Run Background effect
	/*BackgroundLayer* bgLayer = (BackgroundLayer*)getChildByTag(kTagBackground);
	bgLayer->runEffect();*/

	// Add rocks sprite
	addRocks();

	// Add rope sprite
	addRope();

	// Add diver layer
	addDiver();

	// Add marinelife layer
	addMarinelife(0);
	schedule( schedule_selector(MainGameLayer10::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer10::playBubbleEffect), 2);

	// Combo Label
	addPlayStatusLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer10::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer10::checkFeet), 1.0f );
}

void MainGameLayer10::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(10);
}

void MainGameLayer10::addRocks()
{
	Rocks* rocks = MainGameDataLayer::loadRocks();
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer10::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer10::addMarinelife(float dt)
{
	for(int i=0; i<4; i++)
	{
		BrainLayer* brainL = BrainLayer::create();
		addChild(brainL, 0, kTagLayerBrain);
	}
}

void MainGameLayer10::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer10::goToNextGameScene()
{
	Scene *scene = MainGameScene::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer10::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	// increase Lap count;
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	diverL->increaseLapCount();

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.02f);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(false, true);
}