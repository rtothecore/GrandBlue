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
	iMaxFeet = 60;
	iTagForMarinelife = kTagLayerSquid;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Menu
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainGameLayer3::menuBackCallback, this));

    Menu* menu = Menu::create(diveItem, NULL);
	menu->setPosition( Point(origin.x + visibleSize.width/2, visibleSize.height - visibleSize.height/5) );
    this->addChild(menu, 1);

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
	schedule( schedule_selector(MainGameLayer3::addSquid), 3 );

	// Sound
	Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer3::playBubbleEffect), 2);

	// Menu Label - bye
	MenuLabelLayer* mLabel_Bye = MenuLabelLayer::create();
	mLabel_Bye->initWithLabel("Squid's Bye", 1.0f);
	mLabel_Bye->addMenuItem("0", 1.0f);
	mLabel_Bye->createMenu();
	mLabel_Bye->setZOrder(1);
	mLabel_Bye->setPosition(0, -200);
	addChild(mLabel_Bye, 1, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameLayer3::byeMenuLabelRefresh), 0.5);

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	FeverLayer* feverL = MainGameDataLayer::loadFever();
	addChild(feverL, 1, kTagFever);

	// collision detect 
	schedule(schedule_selector(MainGameLayer3::detectCollision));
}

void MainGameLayer3::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
}

void MainGameLayer3::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1, 3);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer3::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0, 15);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer3::addSquid(float dt)
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
	/*Scene *scene = MainGameScene3::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);*/
}