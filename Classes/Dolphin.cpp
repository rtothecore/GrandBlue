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
	healthPoint = st_healthpoint;
	touched = 0;

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

		// HP sprite
		/*sprt_hp = Sprite::create();
		sprt_hp->setTextureRect(CCRectMake(0, 0, 50, 5));
		sprt_hp->setColor(Color3B::BLUE);
		Size dolphinSize = frm_dolphin->getOriginalSize();
		sprt_hp->setPosition(Point(0, dolphinSize.height / 2 + 5));
		addChild(sprt_hp);*/

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
    
	decreaseHealthPoint(touch);

    return true;
}

void DolphinLayer::decreaseHealthPoint(Touch* touch) 
{
	MainGameLayer* parent = (MainGameLayer*)getParent();

	int touchDamage = ((FeverLayer*)parent->getChildByTag(kTagFever))->getTouchDamage();
	healthPoint -= touchDamage;

	//int hpBar = (50 / st_healthpoint) * healthPoint;
	//sprt_hp->setTextureRect(CCRectMake(0, 0, hpBar, 5));

	// Bye sprite frame++
	if(2 == healthPoint)
	{
		sprt_bye->setVisible(true);
	} else if (1 == healthPoint) {
		if( sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye)) )
			sprt_bye->setDisplayFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName("bye2.png") );
	}

	// Tint action
	auto tintAction = TintBy::create(0.1, 0, -255, -255);
	auto tintAction_back = tintAction->reverse();
	sprt_dolphin->runAction( Sequence::create( tintAction, tintAction_back, NULL) );

	if(0 == healthPoint)
	{
		// Bye sprite
		if( sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye)) 
			|| sprt_bye->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName("bye2.png")) )
		{
			sprt_bye->setVisible(true);
			sprt_bye->setDisplayFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName("bye3.png") );
		}

		// Particle effect
		/*auto particle = ParticleExplosion::create();
		particle->setPosition( touch->getLocation() );
		particle->setAutoRemoveOnFinish(true);
		getParent()->addChild(particle);*/

		// Sound
		Sound::playDolphinEffectWithType(3);

		// MainGameLayer dolphin count++
		parent->increaseDolphinBye();

		// MainGameLayer dolphin touch for fever ++
		((FeverLayer*)parent->getChildByTag(kTagFever))->increaseTouchCombo();

		// Blink action
		stopAllActions();
		auto blinkAction = Blink::create(1, 3);
		auto blinkActionDone = CallFuncN::create( CC_CALLBACK_1(DolphinLayer::spriteMoveFinished, this) );
		auto seq = Sequence::create( blinkAction, blinkActionDone, NULL );
		sprt_dolphin->runAction(seq);

		// Remove Dolphin
		//this->removeFromParentAndCleanup(true);
	} else {
		Sound::playDolphinEffectRand();
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
}

void DolphinLayer::spriteUnflipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(1);
	sprt_bye->setScaleX(1);
	sprt_bye->setPositionX(frm_dolphin->getOriginalSize().width/2);
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