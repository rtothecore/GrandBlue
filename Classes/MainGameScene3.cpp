#include "MainGameScene3.h"
#include "Squid.h"
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
#include "MainGameScene4.h"

//------------------------------------------------------------------
//
// MainGameScene3
//
//------------------------------------------------------------------
bool MainGameScene3::init()
{
	MainGameLayer3 *mainGameLayer3 = MainGameLayer3::create();
    addChild(mainGameLayer3, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer3
//
//------------------------------------------------------------------
bool MainGameLayer3::init()
{
	iMaxFeet = 120;
	iTagForMarinelife = kTagLayerSquid;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer3::onEnterTransitionDidFinish()
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

	// Add turtle layer
	schedule( schedule_selector(MainGameLayer3::addMarinelife), 3 );

	// Sound
	//Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer3::playBubbleEffect), 2);

	// Combo Label
	addComboLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer3::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer3::checkFeet), 1.0f );
}

void MainGameLayer3::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(3);
}

void MainGameLayer3::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer3::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer3::addMarinelife(float dt)
{
	for(int i=0; i<4; i++)
	{
		SquidLayer* squidL = SquidLayer::create();
		addChild(squidL, 0, kTagLayerSquid);
	}
}

void MainGameLayer3::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer3::goToNextGameScene()
{
	Scene *scene = MainGameScene4::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer3::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.2f);
}