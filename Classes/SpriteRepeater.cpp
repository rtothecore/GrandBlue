#include "SpriteRepeater.h"

//------------------------------------------------------------------
//
// SpriteRepeater
//
//------------------------------------------------------------------
SpriteRepeater* SpriteRepeater::createWithTexture(Texture2D* aTexture, int zValue, int durValue)
{
    SpriteRepeater* pSR = new SpriteRepeater();
    pSR->initWithTexture( aTexture, zValue, durValue );
    pSR->autorelease();

    return pSR;
}

bool SpriteRepeater::initWithTexture(Texture2D* aTexture, int zValue, int durValue)
{
    if( Sprite::initWithTexture(aTexture) ) 
    {
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// coordinates
		int orgX = visibleSize.width / 2;
		int orgY = visibleSize.height / 2;
		int destY = getContentSize().height + (getContentSize().height/2);

		// set position
		setPosition(Point(orgX, orgY));
		setZOrder(zValue);

		// add repeat image
		Sprite *repeatImage = Sprite::createWithTexture(aTexture);
		repeatImage->setPosition(Point(getContentSize().width / 2, -getContentSize().height/2));
		repeatImage->setZOrder(zValue);
		this->addChild(repeatImage);

		// velocity
		//int actualDuration = 3;

		// action
		SpriteRepeater::actionSequence(this, orgX, destY, durValue);
    }
    
    return true;
}

void SpriteRepeater::actionSequence(Sprite* spr, int destX, int destY, int actualDuration)
{
	auto actionUp = MoveTo::create( (float)actualDuration, Point(destX, destY) );
	auto actionUpDone = CallFuncN::create( CC_CALLBACK_1(SpriteRepeater::moveFinished, this) );
	auto rep = RepeatForever::create(Sequence::create( actionUp, actionUpDone, NULL));
	spr->runAction(rep);
}

void SpriteRepeater::moveFinished(Object* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int orgX = visibleSize.width / 2;
	int orgY = visibleSize.height / 2;

	setPosition(Point(orgX, orgY));
}

//------------------------------------------------------------------
//
// Rope
//
//------------------------------------------------------------------
Rope::Rope(void)
{
}

Rope::~Rope(void)
{
}

//------------------------------------------------------------------
//
// Rocks
//
//------------------------------------------------------------------
Rocks::Rocks(void)
{
}

Rocks::~Rocks(void)
{
}