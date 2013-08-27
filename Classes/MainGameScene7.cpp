#include "MainGameScene7.h"
#include "Ray.h"
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
#include "MainGameScene8.h"
#include "GrandBlueConfig.h"

//------------------------------------------------------------------
//
// MainGameScene7
//
//------------------------------------------------------------------
bool MainGameScene7::init()
{
	MainGameLayer7 *MainGameLayer7 = MainGameLayer7::create();
    addChild(MainGameLayer7, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer7
//
//------------------------------------------------------------------
bool MainGameLayer7::init()
{
	iMaxFeet = MAX_DIVE_FEET_AT_ONE_SCENE;
	iTagForMarinelife = kTagLayerRay;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer7::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer7::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer7::playBubbleEffect), 2);

	// Combo Label
	addPlayStatusLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer7::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer7::checkFeet), 1.0f );
}

void MainGameLayer7::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(7);
}

void MainGameLayer7::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer7::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer7::addMarinelife(float dt)
{
	for(int i=0; i<5; i++)
	{
		RayLayer* rayL = RayLayer::create();
		addChild(rayL, 0, kTagLayerRay);
	}
}

void MainGameLayer7::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer7::goToNextGameScene()
{
	Scene *scene = MainGameScene8::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer7::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.02f);
}