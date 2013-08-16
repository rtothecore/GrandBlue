#include "MainTitleScene.h"
#include "../Classes/HelloWorldScene.h"
#include "MainGameScene.h"
#include "UtilFunc.h"

//------------------------------------------------------------------
//
// MainTitleScene
//
//------------------------------------------------------------------
bool MainTitleScene::init()
{
	MainTitleLayer *mainTitleLayer = MainTitleLayer::create();
    addChild(mainTitleLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainTitleLayer
//
//------------------------------------------------------------------
bool MainTitleLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// Title Label
    LabelTTF* label = LabelTTF::create("Grand Blue", "Consolas", 40);
	label->setColor(cocos2d::Color3B(0, 0, 255));
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height- visibleSize.height/4));
    this->addChild(label, 1);

	// Menu Item
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainTitleLayer::menuDiveCallback, this));
	diveItem->setPosition(Point(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height/2));

	// create menu, it's an autorelease object
    Menu* menu = Menu::create(diveItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	//menu->addChild(diveItem, 1);

    // Background Sprite
    Sprite* sprite = Sprite::create("title_grandBlue.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}


void MainTitleLayer::menuCloseCallback(Object* pSender)
{
    //Director::getInstance()->end();
	Scene *scene = HelloWorld::scene();
	Director::getInstance()->pushScene(scene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainTitleLayer::menuDiveCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInB::create(2, MainGameScene::create());
	Director::getInstance()->pushScene(scene);
}