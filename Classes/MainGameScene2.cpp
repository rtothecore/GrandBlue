#include "MainGameScene2.h"
#include "Turtle.h"
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
#include "MainGameScene3.h"
#include "GrandBlueConfig.h"
#include "AdmobJNI.h"

//------------------------------------------------------------------
//
// MainGameScene2
//
//------------------------------------------------------------------
bool MainGameScene2::init()
{
	MainGameLayer2 *mainGameLayer2 = MainGameLayer2::create();
    addChild(mainGameLayer2, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer2
//
//------------------------------------------------------------------
bool MainGameLayer2::init()
{
	iMaxFeet = MAX_DIVE_FEET_AT_ONE_SCENE;
	iTagForMarinelife = kTagLayerTurtle;

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(true, true);

	return true;
}

void MainGameLayer2::onEnterTransitionDidFinish()
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
	addMarinelife(0);
	schedule( schedule_selector(MainGameLayer2::addMarinelife), 3 );

	// Sound
	schedule( schedule_selector(MainGameLayer2::playBubbleEffect), 2);

	// Combo Label
	addPlayStatusLabel();

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	addFever();

	// collision detect 
	schedule(schedule_selector(MainGameLayer2::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer2::checkFeet), 1.0f );
}

void MainGameLayer2::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
	bgLayer->incrementBlue(2);
}

void MainGameLayer2::addRocks()
{
	Rocks* rocks = MainGameDataLayer::loadRocks();
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer2::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer2::addMarinelife(float dt)
{
	for(int i=0; i<4; i++)
	{
		TurtleLayer* turtleL = TurtleLayer::create();
		addChild(turtleL, 0, kTagLayerTurtle);
	}
}

void MainGameLayer2::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer2::goToNextGameScene()
{
	Scene *scene = MainGameScene3::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}

void MainGameLayer2::readyToGoNextScene()
{
	unschedule( schedule_selector(MainGameBaseLayer::checkFeet) );
	unschedule( schedule_selector(MainGameBaseLayer::addMarinelife) );

	schedule(schedule_selector(MainGameBaseLayer::checkRemainUnattachedMarinlife), 0.02f);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(false, true);
}