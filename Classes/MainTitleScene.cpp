#include "MainTitleScene.h"
#include "../Classes/HelloWorldScene.h"
#include "MainGameScene.h"
#include "UtilFunc.h"
#include "MenuLabel.h"
#include "Sound.h"
#include "Tags.h"

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
    auto labelTitle = LabelBMFont::create("Grand Blue", "fonts/Blippo.fnt");
	labelTitle->setColor(Color3B::BLUE);
	labelTitle->setScale(8.0f);
	labelTitle->setZOrder(1);
	labelTitle->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(labelTitle);

	// ----- main menu -----
	MenuLabelLayer* labelMainLayer = MenuLabelLayer::create();
	labelMainLayer->initWithLabel("Dive!", 3.0f);
	labelMainLayer->addMenuItem("Option", 3.0f);
	labelMainLayer->addMenuItem("Exit", 2.0f);
	labelMainLayer->createMenu();
	labelMainLayer->setZOrder(1);
	labelMainLayer->setPosition(0, -100);

	// set "Dive!" callback
	Menu* labelMainMenu = (Menu*)labelMainLayer->getChildByTag(0);
	MenuItemLabel* labelMenuItemDive = (MenuItemLabel*)labelMainMenu->getChildByTag(0);
	labelMenuItemDive->setCallback( CC_CALLBACK_1(MainTitleLayer::menuDiveCallback, this) );

	// set "Option" callback
	MenuItemLabel* labelMenuItemOption = (MenuItemLabel*)labelMainMenu->getChildByTag(1);
	labelMenuItemOption->setCallback( CC_CALLBACK_1(MainTitleLayer::menuOptionCallback, this) );

	// set "Exit" callback
	MenuItemLabel* labelMenuItemExit = (MenuItemLabel*)labelMainMenu->getChildByTag(2);
	labelMenuItemExit->setCallback( CC_CALLBACK_1(MainTitleLayer::menuCloseCallback, this) );

	addChild(labelMainLayer, 1, kTagMLTitleMain);

	//----- option menu -----
	MenuLabelLayer* labelOptionLayer = MenuLabelLayer::create();
	labelOptionLayer->initWithLabel("Back", 3.0f);

	char chrMusic[12] = {0};
	if(Sound::isMusicOn())
		sprintf(chrMusic, "Music on");
	else
		sprintf(chrMusic, "Music off");

	char chrEffect[12] = {0};
	if(Sound::isEffectOn())
		sprintf(chrEffect, "Effect on");
	else
		sprintf(chrEffect, "Effect off");

	labelOptionLayer->addMenuItem(chrMusic, 2.0f);
	labelOptionLayer->addMenuItem(chrEffect, 2.0f);
	labelOptionLayer->createMenu();
	labelOptionLayer->setZOrder(1);
	labelOptionLayer->setPosition(0, -100);

	//set "back" callback
	Menu* labelOptionMenu = (Menu*)labelOptionLayer->getChildByTag(0);
	MenuItemLabel* labelMenuItem = (MenuItemLabel*)labelOptionMenu->getChildByTag(0);
	labelMenuItem->setCallback( CC_CALLBACK_1(MainTitleLayer::backToMainMenuCallback, this) );

	//set "music" callback
	labelMenuItem = (MenuItemLabel*)labelOptionMenu->getChildByTag(1);
	labelMenuItem->setCallback( CC_CALLBACK_1(MainTitleLayer::togglMusicCallback, this) );

	//set "effect" callback
	labelMenuItem = (MenuItemLabel*)labelOptionMenu->getChildByTag(2);
	labelMenuItem->setCallback( CC_CALLBACK_1(MainTitleLayer::togglEffectCallback, this) );

	labelOptionLayer->setVisible(false);

	addChild(labelOptionLayer, 1, kTagMLTitleOption);

    // Background Sprite
    Sprite* sprite = Sprite::create("title_grandBlue.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}

void MainTitleLayer::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();
	/*Scene *scene = HelloWorld::scene();
	Director::getInstance()->pushScene(scene);*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainTitleLayer::menuDiveCallback(Object* pSender) 
{
	Scene *scene = TransitionSlideInB::create(2, MainGameScene::create());
	Director::getInstance()->pushScene(scene);
}

void MainTitleLayer::menuOptionCallback(Object* pSender)
{
	// hide main layer
	MenuLabelLayer* lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleMain);
	lyr->setVisible(false);

	// show option layer
	lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleOption);
	lyr->setVisible(true);
}

void MainTitleLayer::backToMainMenuCallback(Object* pSender)
{
	// hide option layer
	MenuLabelLayer* lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleOption);
	lyr->setVisible(false);

	// show main layer
	lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleMain);
	lyr->setVisible(true);
}

void MainTitleLayer::togglMusicCallback(Object* pSender)
{
	Sound::toggleMusic();

	// refresh option music label
	MenuLabelLayer* lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleOption);
	MenuItemLabel* labelMenuItem = (MenuItemLabel*)lyr->getChildByTag(1);

	char chrMusic[12] = {0};
	if(Sound::isMusicOn())
		sprintf(chrMusic, "Music on");
	else
		sprintf(chrMusic, "Music off");

	lyr->renameMenuItem(1, chrMusic);
}

void MainTitleLayer::togglEffectCallback(Object* pSender)
{
	Sound::toggleEffect();

	// refresh option music label
	MenuLabelLayer* lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleOption);
	MenuItemLabel* labelMenuItem = (MenuItemLabel*)lyr->getChildByTag(2);

	char chrEffect[12] = {0};
	if(Sound::isEffectOn())
		sprintf(chrEffect, "Effect on");
	else
		sprintf(chrEffect, "Effect off");

	lyr->renameMenuItem(2, chrEffect);
}