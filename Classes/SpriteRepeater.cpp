#include "SpriteRepeater.h"
#include "Resource.h"
#include "UtilFunc.h"

//------------------------------------------------------------------
//
// SpriteRepeater
//
//------------------------------------------------------------------
bool SpriteRepeater::init()
{
    return true;
}

bool SpriteRepeater::initWithTexture(Texture2D* aTexture, int zValue, int durValue)
{
    if( Sprite::initWithTexture(aTexture) ) 
    {
		// coordinates
		int orgX = UtilFunc::getWinSize().width / 2;
		int orgY = UtilFunc::getWinSize().height / 2;

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
	int orgX = UtilFunc::getWinSize().width / 2;
	int orgY = UtilFunc::getWinSize().height / 2;

	setPosition(Point(orgX, orgY));
}

void SpriteRepeater::stopMoveActions()
{
	stopAllActions();
}


//------------------------------------------------------------------
//
// Rope
//
//------------------------------------------------------------------
bool Rope::init()
{
    return true;
}


//------------------------------------------------------------------
//
// Rocks
//
//------------------------------------------------------------------
bool Rocks::init()
{
    return true;
}