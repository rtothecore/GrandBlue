#include "MainGameScene.h"
#include "MainTitleScene.h"
#include "Dolphin.h"
#include "Diver.h"
#include "Resource.h"
#include "SpriteRepeater.h"
#include "Sound.h"
#include "Background.h"
#include "MenuLabel.h"
#include "ProgressBar.h"

enum {
    kTagBackground = 1,
    kTagLabelDolphin = 2,
	kTagFeverProgressBar = 3,
};

//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
MainGameScene::MainGameScene()
{
    MainGameLayer *mainGameLayer = new MainGameLayer();
    addChild(mainGameLayer);
    mainGameLayer->release();
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------
MainGameLayer::MainGameLayer()
{ 
	iDolphinBye = 0;
	bFeverMode = false;
	iDolphinTouchFeverRequire = st_feverRequire;
	iDolphinTouch = 0;
	iTouchDamage = st_touchDamage;

	_dolphins = NULL;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Menu
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainGameLayer::menuBackCallback, this));
	diveItem->setPosition(Point(origin.x + visibleSize.width/2, origin.y + diveItem->getContentSize().height/2));

    Menu* menu = Menu::create(diveItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	// Add background sprite
	addBackground();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MainGameLayer::playBubbleEffect(float dt) 
{
	Sound::playBubbleEffect();
}

MainGameLayer::~MainGameLayer()
{
    _dolphins->release();

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
}

void MainGameLayer::onEnterTransitionDidFinish()
{
	// Run Background effect
	BackgroundLayer* bgLayer = (BackgroundLayer*)getChildByTag(kTagBackground);
	bgLayer->runEffect();

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

	// Menu Label
	MenuLabelLayer* mLabel_DolphinBye = new MenuLabelLayer("Dolphin's Bye");
	mLabel_DolphinBye->addMenuItem("0");
	mLabel_DolphinBye->createMenu();
	mLabel_DolphinBye->setZOrder(1);
	addChild(mLabel_DolphinBye, 1, kTagLabelDolphin);
	schedule(schedule_selector(MainGameLayer::menuLabelDolphinRefresh), 0.5);

	// Fever Progress Bar
	Size visibleSize = Director::getInstance()->getVisibleSize();
	pbLayer = new ProgressBarLayer(visibleSize.width, 10, 5);
	pbLayer->setPosition(0, 0);
	addChild(pbLayer, 1, kTagFeverProgressBar);
}

void MainGameLayer::menuLabelDolphinRefresh(float dt)
{
	MenuLabelLayer* mLabelL = (MenuLabelLayer*)getChildByTag(kTagLabelDolphin);
	char chrDolphinBye[12] = {0};
	sprintf(chrDolphinBye, "%d/%d/%d", MainGameLayer::iDolphinBye, MainGameLayer::iDolphinTouchFeverRequire, MainGameLayer::iDolphinTouch);

	if(bFeverMode)
	{ 
		mLabelL->renameMenuItem(0, "Fever Time!!!!");
	} else {
		mLabelL->renameMenuItem(0, "Dolphin's Bye");
	}

	mLabelL->renameMenuItem(1, chrDolphinBye);
}

void MainGameLayer::menuBackCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInT::create(2, MainTitle::scene());
	Director::getInstance()->pushScene(scene);
}

void MainGameLayer::addBackground()
{
	BackgroundLayer* bgLayer = BackgroundLayer::create();
	addChild(bgLayer, 0, kTagBackground);
}

void MainGameLayer::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = (Rocks*)Rocks::createWithTexture(rocksTexture, 1, 3);
	addChild(rocks);
}

void MainGameLayer::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = (Rope*)Rope::createWithTexture(ropeTexture, 0, 15);
	addChild(rope);
}

void MainGameLayer::addDolphin(float dt)
{
	Array *dolphinsM = Array::createWithCapacity(4);
    
	DolphinLayer* dolphinL = DolphinLayer::createWithPlist();
    dolphinsM->addObject( dolphinL );
    
	dolphinL = DolphinLayer::createWithPlist();
	dolphinsM->addObject( dolphinL );

	dolphinL = DolphinLayer::createWithPlist();
	dolphinsM->addObject( dolphinL );

	dolphinL = DolphinLayer::createWithPlist();
	dolphinsM->addObject( dolphinL );
	
    _dolphins = dolphinsM->clone();
    _dolphins->retain();
    
    Object* pObj = NULL;
    CCARRAY_FOREACH(_dolphins, pObj)
    {
        dolphinL = static_cast<DolphinLayer*>(pObj);

        if(!dolphinL)
            break;

        addChild(dolphinL);
    }
}

void MainGameLayer::addDiver()
{
	Diver* diver = Diver::createWithPlist();
	addChild(diver);
}

void MainGameLayer::increaseDolphinBye()
{
	MainGameLayer::iDolphinBye++;
}

void MainGameLayer::increaseTouchCombo()
{
	if(!bFeverMode)
	{
		pbLayer->increaseProgress(1);

		MainGameLayer::iDolphinTouch++;
		MainGameLayer::checkFever();
	}
}

void MainGameLayer::resetTouchCombo()
{
	if(!bFeverMode)
	{
		MainGameLayer::iDolphinTouch = 0;
		pbLayer->emptyProgress();
	}
}

bool MainGameLayer::containsDolphinLocation(Touch* touch)
{
	DolphinLayer* dolphinL;
	Object* pObj = NULL;

	if(NULL != _dolphins)
	{
		CCARRAY_FOREACH(_dolphins, pObj)
		{
			dolphinL = static_cast<DolphinLayer*>(pObj);

			if(!dolphinL)
				break;

			if( !dolphinL->getRect().containsPoint(convertTouchToNodeSpaceAR(touch)) )
				return false;
		}
	}

	return true;
}

bool MainGameLayer::ccTouchBegan(Touch* touch, Event* event)
{
	if ( !containsDolphinLocation(touch) )
	{
		// MainGameLayer dolphin touch for fever RESET
		CCLog("TOUCH MISS!!!!");
		MainGameLayer::resetTouchCombo();

		return false;
	}

    return true;
}

void MainGameLayer::ccTouchMoved(Touch* touch, Event* event)
{
}

void MainGameLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void MainGameLayer::checkFever()
{
	if(MainGameLayer::iDolphinTouchFeverRequire <= MainGameLayer::iDolphinTouch)
	{
		intoTheFever();
		scheduleOnce( schedule_selector(MainGameLayer::endFever), st_feverTime );
	} 
}

void MainGameLayer::intoTheFever()
{
	CCLog("Fever Time!!!");
	bFeverMode = true;
	MainGameLayer::iTouchDamage = MainGameLayer::st_touchDamageFever;

	// Sound - fever music
	Sound::stopBackgroundMusic();
	Sound::playFeverMusic(true);
}

void MainGameLayer::endFever(float dt)
{
	CCLog("End Fever...");
	bFeverMode = false;
	MainGameLayer::iTouchDamage = MainGameLayer::st_touchDamage;

	MainGameLayer::resetTouchCombo();

	// Sound - background music
	Sound::stopFeverMusic();
	Sound::playBackgroundMusic(true);

	// ProgressBar
	pbLayer->emptyProgress();
}