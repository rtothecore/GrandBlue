#include "MainGameScene.h"
#include "MainTitleScene.h"
#include "Dolphin.h"
#include "Resource.h"
#include "Rocks.h"

USING_NS_CC;

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

	// 메뉴
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

	// 배경(돌) 이미지
	//addRocks();

	// 밧줄 이미지 (나중에 클래스로 분리해야 함)
	Sprite* sprt_line = Sprite::create("line_group.png");
    sprt_line->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprt_line, 0);

	// 다이버 이미지 (나중에 클래스로 분리해야 함)
	Sprite* sprt_diver = Sprite::create("diver.png");
	sprt_diver->setPosition(Point(visibleSize.width/2 + origin.x + sprt_diver->getContentSize().width/4, visibleSize.height/2 + origin.y + 200));
    this->addChild(sprt_diver, 0);

	// 돌고래 생성
	schedule( schedule_selector(MainGameLayer::addDolphin), 3 );
}

MainGameLayer::~MainGameLayer()
{
    _dolphins->release();
}

void MainGameLayer::onEnterTransitionDidFinish()
{
	// 배경(돌) 이미지
	addRocks();
}

void MainGameLayer::menuBackCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInT::create(2, MainTitle::scene());
	Director::getInstance()->pushScene(scene);
}

void MainGameLayer::addRocks()
{
	Texture2D* rocksTexture = TextureCache::getInstance()->addImage(s_Rocks);
	Rocks* rocks = Rocks::createWithTexture(rocksTexture);
	addChild(rocks);
}

void MainGameLayer::addDolphin(float dt)
{
	Texture2D* dolphinTexture = TextureCache::getInstance()->addImage(s_Dolphin);
    
    Array *dolphinsM = Array::createWithCapacity(4);
    
    Dolphin* dolphin = Dolphin::createWithTexture(dolphinTexture);
    dolphinsM->addObject( dolphin );
    
	dolphin = Dolphin::createWithTexture(dolphinTexture);
	dolphinsM->addObject( dolphin );

	dolphin = Dolphin::createWithTexture(dolphinTexture);
	dolphinsM->addObject( dolphin );

	dolphin = Dolphin::createWithTexture(dolphinTexture);
	dolphinsM->addObject( dolphin );

    _dolphins = dolphinsM->clone();
    _dolphins->retain();
    
    Object* pObj = NULL;
    CCARRAY_FOREACH(_dolphins, pObj)
    {
        dolphin = static_cast<Dolphin*>(pObj);

        if(!dolphin)
            break;

        addChild(dolphin);
    }
}
