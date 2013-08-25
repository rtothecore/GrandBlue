#include "MainGameScene5.h"
#include "Seahorse.h"
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
#include "MainGameScene6.h"

//------------------------------------------------------------------
//
// MainGameScene5
//
//------------------------------------------------------------------
bool MainGameScene5::init()
{
	MainGameLayer5 *mainGameLayer5 = MainGameLayer5::create();
    addChild(mainGameLayer5, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer5
//
//------------------------------------------------------------------
bool MainGameLayer5::init()
{
	iMaxFeet = 200;
	iTagForMarinelife = kTagLayerSeahorse;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer5::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer5::addMarinelife), 3 );

	// Sound
	//Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer5::playBubbleEffect), 2);

	// Combo Label
	addComboLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer5::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer5::checkFeet), 1.0f );
}

void MainGameLayer5::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(5);
}

void MainGameLayer5::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer5::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer5::addMarinelife(float dt)
{
	for(int i=0; i<4; i++)
	{
		SeahorseLayer* seahorseL = SeahorseLayer::create();
		addChild(seahorseL, 0, kTagLayerSeahorse);
	}
}

void MainGameLayer5::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer5::goToNextGameScene()
{
	Scene *scene = MainGameScene6::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer5::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.2f);
}