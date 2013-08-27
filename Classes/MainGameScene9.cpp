#include "MainGameScene9.h"
#include "Orca.h"
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
#include "MainGameScene10.h"
#include "GrandBlueConfig.h"

//------------------------------------------------------------------
//
// MainGameScene9
//
//------------------------------------------------------------------
bool MainGameScene9::init()
{
	MainGameLayer9 *MainGameLayer9 = MainGameLayer9::create();
    addChild(MainGameLayer9, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer9
//
//------------------------------------------------------------------
bool MainGameLayer9::init()
{
	iMaxFeet = MAX_DIVE_FEET_AT_ONE_SCENE;
	iTagForMarinelife = kTagLayerOrca;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer9::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer9::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer9::playBubbleEffect), 2);

	// Combo Label
	addPlayStatusLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer9::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer9::checkFeet), 0.25f );
}

void MainGameLayer9::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(9);
}

void MainGameLayer9::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer9::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer9::addMarinelife(float dt)
{
	for(int i=0; i<3; i++)
	{
		OrcaLayer* orcaL = OrcaLayer::create();
		addChild(orcaL, 0, kTagLayerOrca);
	}
}

void MainGameLayer9::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer9::goToNextGameScene()
{
	Scene *scene = MainGameScene10::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer9::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.02f);
}