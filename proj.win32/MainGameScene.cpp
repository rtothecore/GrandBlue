#include "MainGameScene.h"
#include "MainTitleScene.h"
#include "Dolphin.h"
#include "Resource.h"
#include "SpriteRepeater.h"

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

    // 배경(바다_빛) 이미지 (나중에 클래스로 분리해야 함)
    Sprite* sprite = Sprite::create("underTheSea_light.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	// 다이버 이미지 (나중에 클래스로 분리해야 함)
	Sprite* sprt_diver = Sprite::create("diver.png");
	sprt_diver->setPosition(Point(visibleSize.width/2 + origin.x + sprt_diver->getContentSize().width/4, visibleSize.height/2 + origin.y + 200));
    this->addChild(sprt_diver, 0);
}

MainGameLayer::~MainGameLayer()
{
    _dolphins->release();
}

void MainGameLayer::onEnterTransitionDidFinish()
{
	// Add rocks sprite
	addRocks();

	// Add rope sprite
	addRope();

	// Add dolphin layer
	//addDolphin(0);
	schedule( schedule_selector(MainGameLayer::addDolphin), 3 );
}

void MainGameLayer::menuBackCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInT::create(2, MainTitle::scene());
	Director::getInstance()->pushScene(scene);
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
