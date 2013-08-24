#include "SpriteRepeater.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Tags.h"

//------------------------------------------------------------------
//
// SpriteRepeater
//
//------------------------------------------------------------------
bool SpriteRepeater::init()
{
    return true;
}

bool SpriteRepeater::initWithTexture(Texture2D* aTexture, int zValue)
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
		this->addChild(repeatImage, zValue, kTagSpriteRepeatImg);

		// set action manager
		createActionManager();

		// action
		SpriteRepeater::actionSequence(this, orgX, destY);
    }
    
    return true;
}

void SpriteRepeater::createActionManager()
{
	// Create a new scheduler, and link it to the main scheduler
	schedRepeatMove = new Scheduler();	

	//Scheduler* defaultScheduler = Director::sharedDirector()->getScheduler();
    Scheduler* defaultScheduler = Director::getInstance()->getScheduler();
	defaultScheduler->scheduleUpdateForTarget(schedRepeatMove, 0, false);

	// Create anew AcitonManager, and link it to the new scheduler
	ActionManager* actionManager = new ActionManager();
	schedRepeatMove->scheduleUpdateForTarget(actionManager, 0, false);
	setActionManager(actionManager);
}

void SpriteRepeater::setTimeScale(float scale)
{
	schedRepeatMove->setTimeScale(scale);
}

void SpriteRepeater::actionSequence(Sprite* spr, int destX, int destY)
{
	auto actionUp = MoveTo::create( actionDurVal, Point(destX, destY) );
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

Rect SpriteRepeater::getSpriteRepeaterRect()
{
	return Rect( this->getPosition().x - (getContentSize().width/2),
				 //this->getPosition().y - (getContentSize().height/2),
				 0,
				 getContentSize().width,
				 getContentSize().height );
}

void SpriteRepeater::setColorToAllSprite(Color3B colorValue)
{
	setColor(colorValue);
	((Sprite*)(getChildByTag(kTagSpriteRepeatImg)))->setColor(colorValue);
}


//------------------------------------------------------------------
//
// Rope
//
//------------------------------------------------------------------
bool Rope::init()
{
	actionDurVal = 15;
    return true;
}


//------------------------------------------------------------------
//
// Rocks
//
//------------------------------------------------------------------
bool Rocks::init()
{
	actionDurVal = 3;
    return true;
}