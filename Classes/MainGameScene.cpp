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
#include "Fever.h"
#include "DiveFeet.h"

enum {
    kTagBackground = 1,
    kTagLabelDolphin = 2,
	kTagFever = 3,
	kTagLayerDiver = 4,
	kTagLayerDiveFeet = 5,
};

//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
bool MainGameScene::init()
{
	MainGameLayer *mainGameLayer = MainGameLayer::create();
    addChild(mainGameLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------
bool MainGameLayer::init()
{
	iDolphinBye = 0;
	_dolphins = NULL;

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

	addChild(mLabel_DolphinBye, 1, kTagLabelDolphin);
	schedule(schedule_selector(MainGameLayer::menuLabelDolphinRefresh), 0.5);

	// Menu Label - dive feet
	DiveFeetLayer* diveFeetL = DiveFeetLayer::create();
	diveFeetL->startDive();
	addChild(diveFeetL, 1, kTagLayerDiveFeet);
	
	// Fever
	FeverLayer* feverL = FeverLayer::create();
	addChild(feverL, 1, kTagFever);

	// collision detect between Dolphin and Diver
	schedule(schedule_selector(MainGameLayer::detectCollisionBitwinDolphinNDiver), 0.5);
}

void MainGameLayer::menuLabelDolphinRefresh(float dt)
{
	MenuLabelLayer* mLabelL = (MenuLabelLayer*)getChildByTag(kTagLabelDolphin);
	char chrDolphinBye[12] = {0};
	sprintf(chrDolphinBye, "%d/%d/%d", MainGameLayer::iDolphinBye, 
										((FeverLayer*)getChildByTag(kTagFever))->getTouchComboForFever(), 
										((FeverLayer*)getChildByTag(kTagFever))->getTouchCombo() );

	if( ((FeverLayer*)getChildByTag(kTagFever))->isFever() )
	{
		mLabelL->renameMenuItem(0, "Fever Time!!!!");
	} else {
		mLabelL->renameMenuItem(0, "Dolphin's Bye");
	}

	mLabelL->renameMenuItem(1, chrDolphinBye);
}

void MainGameLayer::menuBackCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInT::create(2, MainTitleScene::create());
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
	Rocks* rocks = Rocks::create();
	rocks->initWithTexture(rocksTexture, 1, 3);
	addChild(rocks);
}

void MainGameLayer::addRope()
{
	Texture2D* ropeTexture = TextureCache::getInstance()->addImage(s_Rope);
	Rope* rope = Rope::create();
	rope->initWithTexture(ropeTexture, 0, 15);
	addChild(rope);
}

void MainGameLayer::addDolphin(float dt)
{
	Array *dolphinsM = Array::createWithCapacity(4);
    
	DolphinLayer* dolphinL = DolphinLayer::create();
    dolphinsM->addObject( dolphinL );
    
	dolphinL = DolphinLayer::create();
	dolphinsM->addObject( dolphinL );

	dolphinL = DolphinLayer::create();
	dolphinsM->addObject( dolphinL );

	dolphinL = DolphinLayer::create();
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
	DiverLayer* diverL = DiverLayer::create();
	addChild(diverL, 1, kTagLayerDiver);
}

void MainGameLayer::increaseDolphinBye()
{
	MainGameLayer::iDolphinBye++;
}

void MainGameLayer::detectCollisionBitwinDolphinNDiver(float dt)
{
	checkCollisionBitwinDolphinNDiver();
}

bool MainGameLayer::checkCollisionBitwinDolphinNDiver()
{
	DolphinLayer* dolphinL;
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	Object* pObj = NULL;

	if(NULL != _dolphins)
	{
		CCARRAY_FOREACH(_dolphins, pObj)
		{
			dolphinL = static_cast<DolphinLayer*>(pObj);

			if(!dolphinL)
				break;

			if( !dolphinL->isAttachedToDiver &&
				 dolphinL->getDolphinRect().intersectsRect(diverL->getDiverRect()) )
			{
					dolphinL->attachToDiver(diverL->getPosition().x, diverL->getPosition().y);
					diverL->refreshDiverPositionWithDolphin();
					((DiveFeetLayer*)getChildByTag(kTagLayerDiveFeet))->setDiveStep(diverL->attachedDolphins + 1);
					CCLOG("Dolphin meet diver~^^");
					return true;
			}
		}
	}

	return false;
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
		// reset Touch Combo
		log("TOUCH MISS!!!!");
		((FeverLayer*)getChildByTag(kTagFever))->resetTouchCombo();

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