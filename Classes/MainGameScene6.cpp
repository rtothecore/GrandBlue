#include "MainGameScene6.h"
#include "Mermaid.h"
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
#include "MainGameScene7.h"

//------------------------------------------------------------------
//
// MainGameScene6
//
//------------------------------------------------------------------
bool MainGameScene6::init()
{
	MainGameLayer6 *MainGameLayer6 = MainGameLayer6::create();
    addChild(MainGameLayer6, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer6
//
//------------------------------------------------------------------
bool MainGameLayer6::init()
{
	iMaxFeet = 240;
	iTagForMarinelife = kTagLayerMermaid;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void MainGameLayer6::onEnterTransitionDidFinish()
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
	schedule( schedule_selector(MainGameLayer6::addMarinelife), 3 );

	// Sound
	//Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer6::playBubbleEffect), 2);

	// Combo Label
	addComboLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer6::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer6::checkFeet), 1.0f );
}

void MainGameLayer6::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(6);
}

void MainGameLayer6::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer6::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer6::addMarinelife(float dt)
{
	for(int i=0; i<7; i++)
	{
		MermaidLayer* seahorseL = MermaidLayer::create();
		addChild(seahorseL, 0, kTagLayerMermaid);
	}
}

void MainGameLayer6::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer6::goToNextGameScene()
{
	Scene *scene = MainGameScene7::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer6::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.2f);
}