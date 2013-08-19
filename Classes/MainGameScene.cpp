#include "MainGameScene.h"
#include "Dolphin.h"
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
#include "MainGameScene2.h"
#include "MainGameData.h"
#include "UtilFunc.h"

//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
bool MainGameScene::init()
{
	MainGameLayer *mainGameLayer = MainGameLayer::create();
    addChild(mainGameLayer, 0, kTagGameSceneLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------
bool MainGameLayer::init()
{
	iMaxFeet = 20;
	iTagForMarinelife = kTagLayerDolphin;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Menu
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainGameLayer::menuBackCallback, this));

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

void MainGameLayer::onEnterTransitionDidFinish()
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

	// Add dolphin layer
	schedule( schedule_selector(MainGameLayer::addDolphin), 3 );

	// Sound
	Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer::playBubbleEffect), 2);

	// Menu Label - dolphin bye
	MenuLabelLayer* mLabel_DolphinBye = MenuLabelLayer::create();
	mLabel_DolphinBye->initWithLabel("Dolphin's Bye", 1.0f);
	mLabel_DolphinBye->addMenuItem("0", 1.0f);
	mLabel_DolphinBye->createMenu();
	mLabel_DolphinBye->setZOrder(1);
	mLabel_DolphinBye->setPosition(0, -200);
	addChild(mLabel_DolphinBye, 1, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameLayer::byeMenuLabelRefresh), 0.5);

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	FeverLayer* feverL = MainGameDataLayer::loadFever();
	addChild(feverL, 1, kTagFever);

	// collision detect
	schedule(schedule_selector(MainGameLayer::detectCollision));

	// check feet
	schedule( schedule_selector(MainGameLayer::checkFeet), 1.0f );
}

void MainGameLayer::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
}

void MainGameLayer::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1, 3);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0, 15);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer::addDolphin(float dt)
{
	for(int i=0; i<4; i++)
	{
		DolphinLayer* dolphinL = DolphinLayer::create();
		addChild(dolphinL, 0, kTagLayerDolphin);
	}
}

void MainGameLayer::addDiver()
{
	DiverLayer* diverL = MainGameDataLayer::loadDiver();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer::goToNextGameScene()
{
	Scene *scene = MainGameScene2::create();
	addAttachedMarinelife((Layer*)scene->getChildByTag(kTagGameSceneLayer));
	Director::getInstance()->replaceScene(scene);
}