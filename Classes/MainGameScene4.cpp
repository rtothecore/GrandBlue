#include "MainGameScene4.h"
#include "Starfish.h"
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
#include "MainGameScene5.h"
#include "GrandBlueConfig.h"
#include "AdmobJNI.h"

//------------------------------------------------------------------
//
// MainGameScene4
//
//------------------------------------------------------------------
bool MainGameScene4::init()
{
	MainGameLayer4 *mainGameLayer4 = MainGameLayer4::create();
    addChild(mainGameLayer4, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer4
//
//------------------------------------------------------------------
bool MainGameLayer4::init()
{
	iMaxFeet = MAX_DIVE_FEET_AT_ONE_SCENE;
	iTagForMarinelife = kTagLayerStarfish;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(true, true);

	return true;
}

void MainGameLayer4::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer4::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer4::playBubbleEffect), 2);

	// Combo Label
	addPlayStatusLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer4::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer4::checkFeet), 1.0f );
}

void MainGameLayer4::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(4);
}

void MainGameLayer4::addRocks()
{
	Rocks* rocks = MainGameDataLayer::loadRocks();
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer4::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer4::addMarinelife(float dt)
{
	for(int i=0; i<7; i++)
	{
		StarfishLayer* starfishL = StarfishLayer::create();
		addChild(starfishL, 0, kTagLayerStarfish);
	}
}

void MainGameLayer4::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer4::goToNextGameScene()
{
	Scene *scene = MainGameScene5::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer4::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.02f);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(false, true);
}