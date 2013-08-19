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
	iMaxFeet = 40;
	iTagForMarinelife = kTagLayerTurtle;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Menu
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainGameLayer2::menuBackCallback, this));

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
	schedule( schedule_selector(MainGameLayer2::addTurtle), 3 );

	// Sound
	Sound::playBackgroundMusic(true);
	schedule( schedule_selector(MainGameLayer2::playBubbleEffect), 2);

	// Menu Label - turtle bye
	MenuLabelLayer* mLabel_TurtleBye = MenuLabelLayer::create();
	mLabel_TurtleBye->initWithLabel("Turtle's Bye", 1.0f);
	mLabel_TurtleBye->addMenuItem("0", 1.0f);
	mLabel_TurtleBye->createMenu();
	mLabel_TurtleBye->setZOrder(1);
	mLabel_TurtleBye->setPosition(0, -200);
	addChild(mLabel_TurtleBye, 1, kTagMainGameMenuLabel);
	schedule(schedule_selector(MainGameLayer2::byeMenuLabelRefresh), 0.5);

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = MainGameDataLayer::loadDivedFeet();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	//FeverLayer* feverL = FeverLayer::create();
	FeverLayer* feverL = MainGameDataLayer::loadFever();
	addChild(feverL, 1, kTagFever);

	// collision detect 
	schedule(schedule_selector(MainGameLayer2::detectCollision));
}

void MainGameLayer2::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
}

void MainGameLayer2::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1, 3);
	addChild(rocks, 1, kTagRocks);
}

void MainGameLayer2::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0, 15);
	addChild(rope, 0, kTagRope);
}

void MainGameLayer2::addTurtle(float dt)
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
	/*Scene *scene = TransitionSlideInT::create(2, MainGameScene2::create());
	Director::getInstance()->pushScene(scene);*/
}