#include "Brain.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Sound.h"

bool BrainLayer::init()
{
	isBye = false;
	byePoint = 0;
	isHeadToLeft = true;
	isAttachedToDiver = false;

	initWithPlist(p_Brain, s_Brain);

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
	return true;
}

bool BrainLayer::initWithPlist(const char* plist, const char* frameName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(frm_marineLife = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName))
	{
		sprt_marineLife = Sprite::createWithSpriteFrame(frm_marineLife);
		addChild(sprt_marineLife);

		// Animation
		Array* animFrames = Array::createWithCapacity(5);

		for(int i = 1; i < 6; i++) 
		{
			String* strBrain = String::createWithFormat("brain%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( strBrain->getCString() );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_marineLife->runAction( RepeatForever::create( Animate::create(animation) ) );

		// Y
		//int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

		// X
		int actualX = UtilFunc::getRandomRangeValue(getContentSize().width/2, UtilFunc::getWinSize().width - getContentSize().width/2);

		// Set to the screen top edge
		//setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));
		setPosition(Point(actualX, UtilFunc::getWinSize().height - getContentSize().height/2));

		// Velocity
		int actualDuration = UtilFunc::getRandomRangeValue(1.0, 2.0);

		// Action
		int actionIndex = (rand() % 2);
		//actionIndex>0 ? MarineLifeLayer::actionSequence(this, actualY, actualDuration) : MarineLifeLayer::actionBezier(this, actualY);
		actionIndex>0 ? MarineLifeLayer::actionSequenceTopToBottom(this, actualX, actualDuration) : MarineLifeLayer::actionBezierTopToBottom(this, actualX);

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

BrainLayer* BrainLayer::clone() const
{
	BrainLayer* ret = BrainLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());

	//Added
	ret->isBye = isBye;
	ret->byePoint = byePoint;
	ret->isHeadToLeft = isHeadToLeft;
	ret->isAttachedToDiver = isAttachedToDiver;

    return ret;
}

void BrainLayer::playMarineLifeSound()
{
	switch(byePoint)
	{
		case 1:
		case 2:
			Sound::playBrainEffectRand();
			break;
		case 3:
		default:
			Sound::playBrainEffectWithType(2);
			break;
	}
}