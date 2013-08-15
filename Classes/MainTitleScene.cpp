#include "MainTitleScene.h"
#include "../Classes/HelloWorldScene.h"
#include "MainGameScene.h"
#include "UtilFunc.h"

USING_NS_CC;

Scene* MainTitle::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    MainTitle *layer = MainTitle::create();	// init() È£Ãâ

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainTitle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
    MenuItemImage *closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(MainTitle::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	*/

	//ADDED.
	MenuItemImage *diveItem = MenuItemImage::create(
										"menu_dive.png", 
										"menu_dive_selected.png", 
										CC_CALLBACK_1(MainTitle::menuDiveCallback, this));
	diveItem->setPosition(Point(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height/2));

	// create menu, it's an autorelease object
    Menu* menu = Menu::create(diveItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	//menu->addChild(diveItem, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    LabelTTF* label = LabelTTF::create("Grand Blue", "Consolas", 40);
	label->setColor(cocos2d::Color3B(0, 0, 255));

    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height - 100));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    Sprite* sprite = Sprite::create("title_grandBlue.png");
	UtilFunc::setSizeToScreenSize(sprite);
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}


void MainTitle::menuCloseCallback(Object* pSender)
{
    //Director::getInstance()->end();
	Scene *scene = HelloWorld::scene();
	Director::getInstance()->pushScene(scene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainTitle::menuDiveCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInB::create(2, new MainGameScene());
	Director::getInstance()->pushScene(scene);
}