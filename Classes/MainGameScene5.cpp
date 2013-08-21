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
	iMaxFeet = 100;
	iTagForMarinelife = kTagLayerSeahorse;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Menu
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainGameLayer5::menuBackCallback, this));

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
	schedule( schedule_selector(MainGameLayer5::addSeahorse), 3 );

	// Sound
	Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer5::playBubbleEffect), 2);

	// Menu Label - bye
	MenuLabelLayer* mLabel_Bye = MenuLabelLayer::create();
	mLabel_Bye->initWithLabel("Seahorse's Bye", 1.0f);
	mLabel_Bye->addMenuItem("0", 1.0f);
	mLabel_Bye->createMenu();
	mLabel_Bye->setZOrder(1);
	mLabel_Bye->setPosition(0, -200);
	addChild(mLabel_Bye, 1, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameLayer5::byeMenuLabelRefresh), 0.5);

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	FeverLayer* feverL = MainGameDataLayer::loadFever();
	addChild(feverL, 1, kTagFever);

	// collision detect 
	schedule(schedule_selector(MainGameLayer5::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer5::checkFeet), 1.0f );
}

void MainGameLayer5::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
}

void MainGameLayer5::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1, 3);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer5::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0, 15);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer5::addSeahorse(float dt)
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
	/*Scene *scene = MainGameScene5::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);*/
}