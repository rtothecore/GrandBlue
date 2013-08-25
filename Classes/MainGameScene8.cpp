#include "MainGameScene8.h"
#include "Jellyfish.h"
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
#include "MainGameScene9.h"

//------------------------------------------------------------------
//
// MainGameScene8
//
//------------------------------------------------------------------
bool MainGameScene8::init()
{
	MainGameLayer8 *MainGameLayer8 = MainGameLayer8::create();
    addChild(MainGameLayer8, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer8
//
//------------------------------------------------------------------
bool MainGameLayer8::init()
{
	iMaxFeet = 320;
	iTagForMarinelife = kTagLayerJellyfish;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer8::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer8::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer8::playBubbleEffect), 2);

	// Combo Label
	addComboLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer8::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer8::checkFeet), 1.0f );
}

void MainGameLayer8::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(8);
}

void MainGameLayer8::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer8::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer8::addMarinelife(float dt)
{
	for(int i=0; i<5; i++)
	{
		JellyfishLayer* jellyfishL = JellyfishLayer::create();
		addChild(jellyfishL, 0, kTagLayerJellyfish);
	}
}

void MainGameLayer8::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer8::goToNextGameScene()
{
	Scene *scene = MainGameScene9::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer8::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.2f);
}