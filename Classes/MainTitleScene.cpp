#include "MainTitleScene.h"
#include "../Classes/HelloWorldScene.h"
#include "MainGameScene.h"
#include "UtilFunc.h"
#include "MenuLabel.h"
#include "Sound.h"
#include "Tags.h"
#include "Resource.h"
#include "ScoreRecord.h"
#include "AppMacros.h"
#include "AdmobJNI.h"

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
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = Director::getInstance()->getVisibleOrigin();
    cocos2d::Size winSize = Director::getInstance()->getWinSize();

	// High Score label
	ScoreRecordLayer::addHighScoreLabel(this, Color3B::WHITE);

	// Title label
    /*Size blockSize = Size(winSize.width, 200);
	LabelTTF *labelTitle = LabelTTF::create("Grand Blue", FONT_TITLE_FILE, TITLE_FONT_SIZE, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);*/
	/* NEW
	Size blockSize = Size(winSize.width, winSize.height/2);
	LabelTTF *labelTitle = LabelTTF::create("Grand\n Blue", FONT_TITLE_FILE, TITLE_FONT_SIZE, 
										blockSize, Label::HAlignment::RIGHT, Label::VAlignment::TOP);
	labelTitle->setColor(Color3B::BLUE);
	labelTitle->setZOrder(1);
	labelTitle->setPosition(Point(winSize.width/2, winSize.height/2 + (winSize.height/20)));
	addChild(labelTitle);
	*/

	// ----- main menu -----
	MenuLabelLayer* labelMainLayer = MenuLabelLayer::create();
	labelMainLayer->initWithLabel("Dive!", 3.0f);
	labelMainLayer->addMenuItem("Option", 3.0f);
	labelMainLayer->addMenuItem("Exit", 2.0f);
	labelMainLayer->createMenu();
	labelMainLayer->setZOrder(1);
	labelMainLayer->setPosition(0, -(winSize.height/5));

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

	String* strMusic;
	if(Sound::isMusicOn())
		strMusic = String::create("Music on");
	else
		strMusic = String::create("Music off");

	String* strEffect;
	if(Sound::isEffectOn())
		strEffect = String::create("Effect on");
	else
		strEffect = String::create("Effect off");

	labelOptionLayer->addMenuItem(strMusic->getCString(), 2.0f);
	labelOptionLayer->addMenuItem(strEffect->getCString(), 2.0f);
	labelOptionLayer->createMenu();
	labelOptionLayer->setZOrder(1);
	labelOptionLayer->setPosition(0, -(winSize.height/5));

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
    Sprite* sprite = Sprite::create(s_Title);
    sprite->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	// background music
	Sound::playBackgroundMusic(true);

	// ADMOB JNI
	AdmobJNI::setAdmobVisible(true, false);

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
	// ADMOB JNI
	AdmobJNI::setAdmobVisible(false, false);

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

	String* strMusic;
	if(Sound::isMusicOn())
		strMusic = String::create("Music on");
	else
		strMusic = String::create("Music off");

	lyr->renameMenuItem(1, strMusic->getCString());
}

void MainTitleLayer::togglEffectCallback(Object* pSender)
{
	Sound::toggleEffect();

	// refresh option music label
	MenuLabelLayer* lyr = (MenuLabelLayer*)getChildByTag(kTagMLTitleOption);

	String* strEffect;
	if(Sound::isEffectOn())
		strEffect = String::create("Effect on");
	else
		strEffect = String::create("Effect off");

	lyr->renameMenuItem(2, strEffect->getCString());
}