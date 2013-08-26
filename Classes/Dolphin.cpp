#include "Dolphin.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Sound.h"

bool DolphinLayer::init()
{
	isBye = false;
	byePoint = 0;
	isHeadToLeft = true;
	isAttachedToDiver = false;

	initWithPlist(p_Dolphin, s_Dolphin);

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
	return true;
}

bool DolphinLayer::initWithPlist(const char* plist, const char* frameName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(frm_marineLife = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName))
	{
		sprt_marineLife = Sprite::createWithSpriteFrame(frm_marineLife);
		addChild(sprt_marineLife);

		// Dolphin's Animation
		Array* animFrames = Array::createWithCapacity(5);

		for(int i = 1; i < 6; i++) 
		{
			String* strDolphin = String::createWithFormat("dolphin%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( strDolphin->getCString() );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_marineLife->runAction( RepeatForever::create( Animate::create(animation) ) );

		// Dolphin's Y
		int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

		// Set Dolphin to the screen right edge
		setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));

		// Velocity
		int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

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

DolphinLayer* DolphinLayer::clone() const
{
	DolphinLayer* ret = DolphinLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());

	//Added
	ret->isBye = isBye;
	ret->byePoint = byePoint;
	ret->isHeadToLeft = isHeadToLeft;
	ret->isAttachedToDiver = isAttachedToDiver;

    return ret;
}

void DolphinLayer::playMarineLifeSound()
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

