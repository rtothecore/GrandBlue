#include "MarineLife.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Sound.h"
#include "MainGameScene.h"
#include "Fever.h"
#include "Diver.h"

enum {
	kTagFever = 3,
	kTagLayerDiver = 4,
};

bool MarineLifeLayer::init()
{
	//isBye = false;
	//byePoint = 0;
	//isHeadToLeft = true;
	//isAttachedToDiver = false;

	//initWithPlist(p_Dolphin, s_Dolphin);

	////touch
	//Director* director = Director::getInstance();
    //director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
	//return true;
	return true;
}

MarineLifeLayer* MarineLifeLayer::clone() const
{
	MarineLifeLayer* ret = MarineLifeLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());

	//Added
	ret->isBye = isBye;
	ret->byePoint = byePoint;
	ret->isHeadToLeft = isHeadToLeft;
	ret->isAttachedToDiver = isAttachedToDiver;

    return ret;
}

bool MarineLifeLayer::initWithPlist(const char* plist, const char* frameName)
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	//
	//if(frm_marineLife = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName))
	//{
	//	sprt_marineLife = Sprite::createWithSpriteFrame(frm_marineLife);
	//	addChild(sprt_marineLife);

	//	// Dolphin's Animation
	//	Array* animFrames = Array::createWithCapacity(5);

	//	char str[100] = {0};

	//	for(int i = 1; i < 6; i++) 
	//	{
	//		sprintf(str, "dolphin%d.png", i);
	//		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( str );
	//		animFrames->addObject(frame);
	//	}

	//	auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	//	sprt_marineLife->runAction( RepeatForever::create( Animate::create(animation) ) );

	//	// Dolphin's Y
	//	int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

	//	// Set Dolphin to the screen right edge
	//	setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));

	//	// Velocity
	//	int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

	//	// Action
	//	int actionIndex = (rand() % 2);
	//	actionIndex>0 ? MarineLifeLayer::actionSequence(this, actualY, actualDuration) : MarineLifeLayer::actionBezier(this, actualY);

	//	// bye sprite
	//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p_Bye);
	//	sprt_bye = Sprite::createWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye) );
	//	sprt_bye->setPosition( Point(0, frm_marineLife->getOriginalSize().height/2) );
	//	sprt_bye->setVisible(false);
	//	addChild(sprt_bye);

	//	// Collision Check sprite
	//	/*Sprite* sprtTest = Sprite::create();
	//	sprtTest->setTextureRect(getDolphinRect());
	//	sprtTest->setColor(Color3B::WHITE);
	//	addChild(sprtTest);*/
	//}

	//return true;
	return true;
}

void MarineLifeLayer::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

Rect MarineLifeLayer::getRect()
{
	Size s = frm_marineLife->getOriginalSize();
	
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void MarineLifeLayer::onEnter()
{
    Layer::onEnter();
}

void MarineLifeLayer::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool MarineLifeLayer::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool MarineLifeLayer::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) )
	{
		return false;
	}
    
	if(!isBye)
	{
		aliveMarineLifeTouched();
	}

    return true;
}

void MarineLifeLayer::ccTouchMoved(Touch* touch, Event* event)
{   
}

void MarineLifeLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void MarineLifeLayer::aliveMarineLifeTouched()
{
	byePointUp();

	playMarineLifeSound();
	refreshByeSprite();
	actionTint(sprt_marineLife);

	if(st_byePoint <= byePoint)
	{
		comboForFeverUp();
		actionBlinkAndRemove(sprt_marineLife);
	}
}

void MarineLifeLayer::byePointUp()
{
	MainGameScene* parent = (MainGameScene*)getParent();
	int touchPoint = ((FeverLayer*)parent->getChildByTag(kTagFever))->getTouchDamage();

	byePoint += touchPoint;

	if(st_byePoint <= byePoint)
	{
		isBye = true;
	}
}

void MarineLifeLayer::refreshByeSprite()
{
	switch(byePoint) 
	{
		case 1:
			sprt_bye->setVisible(true);
			break;
		case 2:
			if( sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye)) )
				sprt_bye->setDisplayFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName("bye2.png") );
			break;
		case 3:
		default:
			sprt_bye->setVisible(true);
			if( sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye)) ||
				sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName("bye2.png")) )
				sprt_bye->setDisplayFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName("bye3.png") );
			break;
	}
}

void MarineLifeLayer::actionTint(Sprite* sprt)
{
	auto tintAction = TintBy::create(0.1, 0, -255, -255);
	auto tintAction_back = tintAction->reverse();
	sprt->runAction( Sequence::create( tintAction, tintAction_back, NULL) );
}

void MarineLifeLayer::comboForFeverUp()
{
	MainGameLayer* parent = (MainGameLayer*)getParent();
	parent->increaseMarineLifeBye();

	// MainGameLayer dolphin touch for fever ++
	((FeverLayer*)parent->getChildByTag(kTagFever))->increaseTouchCombo();	
}

void MarineLifeLayer::actionBlinkAndRemove(Sprite* sprt)
{
	stopAllActions();
	auto blinkAction = Blink::create(1, 3);
	auto blinkActionDone = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteMoveFinished, this) );
	auto seq = Sequence::create( blinkAction, blinkActionDone, NULL );
	sprt->runAction(seq);
}

void MarineLifeLayer::playMarineLifeSound()
{
	/*switch(byePoint)
	{
		case 1:
		case 2:
			Sound::playDolphinEffectRand();
			break;
		case 3:
		default:
			Sound::playDolphinEffectWithType(3);
			break;
	}*/
}

void MarineLifeLayer::spriteFlipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(-1);
	sprt_bye->setScaleX(-1);
	isHeadToLeft = true;
}

void MarineLifeLayer::spriteUnflipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(1);
	sprt_bye->setScaleX(1);
	sprt_bye->setPositionX(frm_marineLife->getOriginalSize().width/2);
	isHeadToLeft = false;
}

void MarineLifeLayer::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeFromParentAndCleanup(true);
}

void MarineLifeLayer::actionSequence(Layer* lyr, int actualY, int actualDuration)
{
	auto actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteFlipY, this) );
	auto actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - lyr->getContentSize().width/2, actualY) );
	auto actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	auto actionPause = DelayTime::create(0.5);
	auto actionPauseDone = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteUnflipY, this) );
	auto actionBackToRight = MoveTo::create( (float)actualDuration, Point(lyr->getPosition().x, actualY) );
	auto actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteMoveFinished, this) );

    lyr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
}

void MarineLifeLayer::actionBezier(Layer* lyr, int actualY)
{
    ccBezierConfig bezier;
	
    bezier.controlPoint_1 = Point(0, actualY + 200);
    bezier.controlPoint_2 = Point(-250, actualY - 200);
    bezier.endPosition = Point(-500, actualY);
	
	auto towardToLeft = CallFuncN::create(CC_CALLBACK_1(MarineLifeLayer::spriteFlipY, this));
	auto towardToRight = CallFuncN::create(CC_CALLBACK_1(MarineLifeLayer::spriteUnflipY, this));
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
	auto bezierEnd = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteMoveFinished, this) );
    auto rep = RepeatForever::create(Sequence::create( towardToLeft, bezierForward, towardToRight, bezierBack, bezierEnd, NULL));

    lyr->runAction(rep);
}

Rect MarineLifeLayer::getMarineLifeRect()
{
	return Rect( this->getPosition().x - (sprt_marineLife->getContentSize().width/2),
				 this->getPosition().y - (sprt_marineLife->getContentSize().height/2),
				 sprt_marineLife->getContentSize().width,
				 sprt_marineLife->getContentSize().height );
}

void MarineLifeLayer::attachToDiver(int diverPosX, int diverPosY)
{
	isAttachedToDiver = true;

	stopAllActions();

	// set color
	sprt_marineLife->setColor(Color3B::RED);

	// unvisible bye sprt
	sprt_bye->setVisible(false);

	// head to left
	spriteFlipY(this);

	// disable touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);

	// run after diver
	schedule( schedule_selector(MarineLifeLayer::runAfterDiver), 0.5f );

	// set potion to diver
	//this->setPosition(diverPosX, diverPosY);
}

void MarineLifeLayer::runAfterDiver(float dt)
{
	MainGameScene* parent = (MainGameScene*)getParent();
	if( (DiverLayer*)parent->getChildByTag(kTagLayerDiver) )
	{
		Point pntDiver = ((DiverLayer*)parent->getChildByTag(kTagLayerDiver))->getPosition();

		auto actionMoveToDiver = MoveTo::create(3.4, pntDiver);
		auto actionMoveToDiverEaseInOut = EaseInOut::create(actionMoveToDiver, 1.2);
		runAction(actionMoveToDiverEaseInOut);
	}
}

void MarineLifeLayer::runLoveAction()
{
	// move to left screen edge
	auto actionMoveToLeft = MoveTo::create( 4.5, Point(0 - sprt_marineLife->getContentSize().width , getPositionY()) );
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(MarineLifeLayer::spriteMoveFinished, this) );
	runAction( Sequence::create(actionMoveToLeft, actionMoveDone, NULL) );
}
