#include "Dolphin.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Sound.h"
#include "MainGameScene.h"
#include "Fever.h"

enum {
	kTagFever = 3,
};

bool DolphinLayer::init()
{
	isBye = false;
	byePoint = 0;
	isHeadToLeft = true;
	isAttachedToDiver = false;

	initWithPlist(p_Dolphin);
	
	return true;
}

DolphinLayer::~DolphinLayer()
{
}

DolphinLayer* DolphinLayer::clone() const
{
	DolphinLayer* ret = DolphinLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());
    return ret;
}

bool DolphinLayer::initWithPlist(const char* plist)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(frm_dolphin = SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Dolphin))
	{
		sprt_dolphin = Sprite::createWithSpriteFrame(frm_dolphin);
		addChild(sprt_dolphin);

		// Dolphin's Animation
		Array* animFrames = Array::createWithCapacity(5);

		char str[100] = {0};

		for(int i = 1; i < 6; i++) 
		{
			sprintf(str, "dolphin%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( str );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_dolphin->runAction( RepeatForever::create( Animate::create(animation) ) );

		// Dolphin's Y
		int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

		// Set Dolphin to the screen right edge
		setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));

		// Velocity
		int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

		// Action
		int actionIndex = (rand() % 2);
		actionIndex>0 ? DolphinLayer::actionSequence(this, actualY, actualDuration) : DolphinLayer::actionBezier(this, actualY);

		// bye sprite
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p_Bye);
		sprt_bye = Sprite::createWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye) );
		sprt_bye->setPosition( Point(0, frm_dolphin->getOriginalSize().height/2) );
		sprt_bye->setVisible(false);
		addChild(sprt_bye);
	}

	return true;
}

Rect DolphinLayer::getRect()
{
	Size s = frm_dolphin->getOriginalSize();
	
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void DolphinLayer::onEnter()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    Layer::onEnter();
}

void DolphinLayer::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool DolphinLayer::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool DolphinLayer::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) )
	{
		return false;
	}
    
	if(!isBye)
	{
		aliveDolphinTouched();
	}

    return true;
}

void DolphinLayer::aliveDolphinTouched()
{
	byePointUp();

	playDolphinSound();
	refreshByeSprite();
	actionTint(sprt_dolphin);

	if(st_byePoint <= byePoint)
	{
		comboForFeverUp();
		actionBlinkAndRemove(sprt_dolphin);
	}
}

void DolphinLayer::byePointUp()
{
	MainGameLayer* parent = (MainGameLayer*)getParent();
	int touchPoint = ((FeverLayer*)parent->getChildByTag(kTagFever))->getTouchDamage();

	byePoint += touchPoint;

	if(st_byePoint <= byePoint)
		isBye = true;
}

void DolphinLayer::refreshByeSprite()
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

void DolphinLayer::actionTint(Sprite* sprt)
{
	auto tintAction = TintBy::create(0.1, 0, -255, -255);
	auto tintAction_back = tintAction->reverse();
	sprt->runAction( Sequence::create( tintAction, tintAction_back, NULL) );
}

void DolphinLayer::comboForFeverUp()
{
	MainGameLayer* parent = (MainGameLayer*)getParent();
	parent->increaseDolphinBye();

	// MainGameLayer dolphin touch for fever ++
	((FeverLayer*)parent->getChildByTag(kTagFever))->increaseTouchCombo();	
}

void DolphinLayer::actionBlinkAndRemove(Sprite* sprt)
{
	stopAllActions();
	auto blinkAction = Blink::create(1, 3);
	auto blinkActionDone = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteMoveFinished, this) );
	auto seq = Sequence::create( blinkAction, blinkActionDone, NULL );
	sprt->runAction(seq);
}

void DolphinLayer::playDolphinSound()
{
	switch(byePoint)
	{
		case 1:
		case 2:
			Sound::playDolphinEffectRand();
			break;
		case 3:
		default:
			Sound::playDolphinEffectWithType(3);
			break;
	}
}

void DolphinLayer::ccTouchMoved(Touch* touch, Event* event)
{   
}

void DolphinLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void DolphinLayer::spriteFlipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(-1);
	sprt_bye->setScaleX(-1);
	isHeadToLeft = true;
}

void DolphinLayer::spriteUnflipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(1);
	sprt_bye->setScaleX(1);
	sprt_bye->setPositionX(frm_dolphin->getOriginalSize().width/2);
	isHeadToLeft = false;
}

void DolphinLayer::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

void DolphinLayer::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeFromParentAndCleanup(true);
}

void DolphinLayer::actionSequence(Layer* lyr, int actualY, int actualDuration)
{
	auto actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteFlipY, this) );
	auto actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - lyr->getContentSize().width/2, actualY) );
	auto actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	auto actionPause = DelayTime::create(0.5);
	auto actionPauseDone = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteUnflipY, this) );
	auto actionBackToRight = MoveTo::create( (float)actualDuration, Point(lyr->getPosition().x, actualY) );
	auto actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteMoveFinished, this) );

    lyr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
}

void DolphinLayer::actionBezier(Layer* lyr, int actualY)
{
    ccBezierConfig bezier;
	
    bezier.controlPoint_1 = Point(0, actualY + 200);
    bezier.controlPoint_2 = Point(-250, actualY - 200);
    bezier.endPosition = Point(-500, actualY);
	
	auto towardToLeft = CallFuncN::create(CC_CALLBACK_1(DolphinLayer::spriteFlipY, this));
	auto towardToRight = CallFuncN::create(CC_CALLBACK_1(DolphinLayer::spriteUnflipY, this));
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
	auto bezierEnd = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteMoveFinished, this) );
    auto rep = RepeatForever::create(Sequence::create( towardToLeft, bezierForward, towardToRight, bezierBack, bezierEnd, NULL));

    lyr->runAction(rep);
}

Rect DolphinLayer::getDolphinRect()
{
	return Rect( this->getPosition().x - (sprt_dolphin->getContentSize().width/2),
				 this->getPosition().y - (sprt_dolphin->getContentSize().height/2),
				 sprt_dolphin->getContentSize().width,
				 sprt_dolphin->getContentSize().height );
}

void DolphinLayer::attachToDiver(int diverPosX, int diverPosY)
{
	isAttachedToDiver = true;

	stopAllActions();

	// unvisible bye sprt
	sprt_bye->setVisible(false);

	// head to left
	spriteFlipY(this);

	// disable touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);

	this->setPosition(diverPosX, diverPosY);
}

void DolphinLayer::runLoveAction()
{
	// move to left screen edge
	auto actionMoveToLeft = MoveTo::create( 4.5, Point(0 - sprt_dolphin->getContentSize().width , getPositionY()) );
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteMoveFinished, this) );
	runAction( Sequence::create(actionMoveToLeft, actionMoveDone, NULL) );
}