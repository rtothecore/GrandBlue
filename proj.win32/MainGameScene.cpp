#include "MainGameScene.h"
#include "MainTitleScene.h"
#include "Dolphin.h"
#include "Diver.h"
#include "Resource.h"
#include "SpriteRepeater.h"
#include "Sound.h"
#include "Background.h"

enum {
    kTagBackground = 1,
    kTagLabel = 2,
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
}

void MainGameLayer::playBubbleEffect(float dt) 
{
	Sound::playBubbleEffect();
}

MainGameLayer::~MainGameLayer()
{
    _dolphins->release();
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
	//diver->autorelease();
	addChild(diver);
}