#include "Turtle.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Sound.h"

bool TurtleLayer::init()
{
	isBye = false;
	byePoint = 0;
	isHeadToLeft = true;
	isAttachedToDiver = false;

	initWithPlist(p_Turtle, s_Turtle);

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
	return true;
}

bool TurtleLayer::initWithPlist(const char* plist, const char* frameName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(frm_marineLife = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName))
	{
		sprt_marineLife = Sprite::createWithSpriteFrame(frm_marineLife);
		addChild(sprt_marineLife);

		// Animation
		Array* animFrames = Array::createWithCapacity(4);

		char str[100] = {0};

		for(int i = 1; i < 5; i++) 
		{
			sprintf(str, "turtle%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( str );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_marineLife->runAction( RepeatForever::create( Animate::create(animation) ) );

		// Y
		int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

		// Set to the screen right edge
		setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));

		// Velocity
		int actualDuration = UtilFunc::getRandomRangeValue(2.0, 3.0);

		// Action
		int actionIndex = (rand() % 2);
		actionIndex>0 ? MarineLifeLayer::actionSequence(this, actualY, actualDuration) : MarineLifeLayer::actionBezier(this, actualY);

		// bye sprite
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p_Bye);
		sprt_bye = Sprite::createWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye) );
		sprt_bye->setPosition( Point(0, frm_marineLife->getOriginalSize().height/2) );
		sprt_bye->setVisible(false);
		addChild(sprt_bye);

		// Collision Check sprite
		/*Sprite* sprtTest = Sprite::create();
		sprtTest->setTextureRect(getDolphinRect());
		sprtTest->setColor(Color3B::WHITE);
		addChild(sprtTest);*/
	}

	return true;
}

TurtleLayer* TurtleLayer::clone() const
{
	TurtleLayer* ret = TurtleLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());

	//Added
	ret->isBye = isBye;
	ret->byePoint = byePoint;
	ret->isHeadToLeft = isHeadToLeft;
	ret->isAttachedToDiver = isAttachedToDiver;

    return ret;
}

void TurtleLayer::playMarineLifeSound()
{
	switch(byePoint)
	{
		case 1:
		case 2:
			Sound::playTurtleEffectRand();
			break;
		case 3:
		default:
			Sound::playTurtleEffectWithType(3);
			break;
	}
}