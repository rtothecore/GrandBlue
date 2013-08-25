#include "Diver.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "Tags.h"
#include "Sound.h"

bool DiverLayer::init()
{
	isLove = false;
	lovePoint = 0;

	initWithPlist(p_Diver);

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

DiverLayer::~DiverLayer(void)
{
}

DiverLayer* DiverLayer::clone() const
{
	DiverLayer* ret = DiverLayer::create();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());

	//Added
	ret->lovePoint = lovePoint;
	ret->isLove = isLove;

    return ret;
}

bool DiverLayer::initWithPlist(const char* plist)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(frm_diver = SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Diver))
	{
		sprt_diver = Sprite::createWithSpriteFrame(frm_diver);
		addChild(sprt_diver);

		//Animation --------------> FIX ME : batchNode? make it that don't need to set Array's number
		Array* animFrames = Array::createWithCapacity(4);

		char str[100] = {0};

		for(int i = 1; i < 5; i++) 
		{
			sprintf(str, "diver%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( str );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_diver->runAction( RepeatForever::create( Animate::create(animation) ) );	

		//Y
		//int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, visibleSize.height/1.4 - getContentSize().height);

		// Set to the screen right edge
		setPosition( Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height-(UtilFunc::getWinSize().height/5)) );

		// Velocity
		//int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

		// Action
		actionMoveStacked(this, 0, 10);

		// Love sprite
		Size diverSize = frm_diver->getOriginalSize();

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p_Love);
		sprt_love = Sprite::createWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Love) );
		sprt_love->setPosition( Point(0, diverSize.height/2) );
		sprt_love->setVisible(false);
		addChild(sprt_love);

		// Collision Check sprite
		/*Sprite* sprtTest = Sprite::create();
		sprtTest->setTextureRect(getDiverRect());
		sprtTest->setColor(Color3B::WHITE);
		addChild(sprtTest);*/
	}

	return true;
}

void DiverLayer::actionMoveStacked(Layer *lyr, int destX, int destY)
{
    lyr->runAction(
        RepeatForever::create(
                Sequence::create(
                MoveBy::create(5, Point(10,10)),
                MoveBy::create(5, Point(-10,-10)),
       NULL)));
    
    MoveBy* action = MoveBy::create(2.0f, Point(destX, destY));
    MoveBy* action_back = action->reverse();
    
    lyr->runAction(
      RepeatForever::create(
        Sequence::create(action, action_back, NULL)
      ));
}

Rect DiverLayer::getRect()
{
	Size s = frm_diver->getOriginalSize();
	
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void DiverLayer::onEnter()
{
    Layer::onEnter();
}

void DiverLayer::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool DiverLayer::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool DiverLayer::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) ) return false;

    return true;
}

void DiverLayer::ccTouchMoved(Touch* touch, Event* event)
{   
	Rect moveLimitRect = Rect( 0 + getContentSize().width, 
							   0 + getContentSize().height , 
							   UtilFunc::getWinSize().width - getContentSize().width,
							   UtilFunc::getWinSize().height - getContentSize().height
						     );

	if( moveLimitRect.containsPoint(touch->getLocation()) )
		setPosition( Point(touch->getLocation().x, touch->getLocation().y) );
}

void DiverLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void DiverLayer::spriteMoveFinished(Object* pSender)
{
	this->removeFromParentAndCleanup(true);
}

// WARNING : Rect's anchor point is not (0.5, 0.5) but (0, 0) !!!!
Rect DiverLayer::getDiverRect()
{
	//ORIGINAL
	/*return Rect( this->getPosition().x - (sprt_diver->getContentSize().width/2),
				 this->getPosition().y - (sprt_diver->getContentSize().height/2),
				 sprt_diver->getContentSize().width,
				 sprt_diver->getContentSize().height );*/

	float rectWidth = 20;
	float rectHeight = 20;
	
	return Rect( this->getPosition().x - rectWidth / 2, 
		         this->getPosition().y - rectHeight / 2,
				 rectWidth, 
				 rectHeight );
}

void DiverLayer::refreshDiverPositionWithDolphin()
{
	if(0 + getContentSize().height < getPositionY() - 20)
		actionDownMoveBy(-20);

	increaseLovePoint();
	refreshLoveSprite();
}

void DiverLayer::actionDownMoveBy(int yDelta)
{
	auto actionMoveToDown = MoveBy::create( 1.0f, Point(0, yDelta) );
	runAction(actionMoveToDown);
}

void DiverLayer::refreshLoveSprite()
{
	if(1 == lovePoint)
	{
		sprt_love->setVisible(true);
	}
	else if( 1 < lovePoint && st_maxLovePoint >= lovePoint)
	{
		sprt_love->setVisible(true);

		char chrCurrentLoveFrame[10] = {0};
		sprintf(chrCurrentLoveFrame, "love%d.png", lovePoint-1);

		char chrNextLoveFrame[10] = {0};
		sprintf(chrNextLoveFrame, "love%d.png", lovePoint);

		if( sprt_love->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Love)) ||
			sprt_love->isFrameDisplayed(SpriteFrameCache::getInstance()->getSpriteFrameByName(chrCurrentLoveFrame)) )
			sprt_love->setDisplayFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(chrNextLoveFrame) );	
	}
}

void DiverLayer::increaseLovePoint()
{
	if(st_maxLovePoint > lovePoint)
	{
		lovePoint++;

		if(st_maxLovePoint == lovePoint)
		{
			isLove = true;
			log("Diver is falling in love with dolphin");
		}

		// sprite action
		runMeetMarinelifeAction();

		// sound
		Sound::playDiverEffectWithType(1);
	}
}

void DiverLayer::runLoveAction()
{
	// rotate 90
	sprt_diver->setRotation(90);

	// show love sprite
	refreshLoveSprite();

	// move to left screen edge
	auto actionMoveToLeft = MoveTo::create( 5, Point(0 - sprt_diver->getContentSize().width , getPositionY()) );
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteMoveFinished, this) );
	runAction( Sequence::create(actionMoveToLeft, actionMoveDone, NULL) );
}

void DiverLayer::runFevermodeAction()
{
	auto tintred = TintBy::create(0.1f, 0, -255, -255);
    auto tintred_back = tintred->reverse();

	auto tintgreen = TintBy::create(0.1f, -255, 0, -255);
    auto tintgreen_back = tintgreen->reverse();
    
    auto tintblue = TintBy::create(0.1f, -255, -255, 0);
    auto tintblue_back = tintblue->reverse();

    auto diverFeverAction = RepeatForever::create( Sequence::create( tintred, tintred_back, 
																tintgreen, tintgreen_back, 
																tintblue, tintblue_back, NULL) );
	diverFeverAction->setTag(kTagActionDiverFever);
	sprt_diver->runAction(diverFeverAction);
}

void DiverLayer::runMeetMarinelifeAction()
{
	auto tintred = TintBy::create(0.2f, 0, -255, -255);
    auto tintred_back = tintred->reverse();

	sprt_diver->runAction( Sequence::create( tintred, tintred_back, NULL) );
}

void DiverLayer::exitFevermodeAction()
{
	sprt_diver->stopActionByTag(kTagActionDiverFever);
}

void DiverLayer::refreshDiver()
{
	refreshLoveSprite();
}

void DiverLayer::moveByDisplacement(Point displace)
{
	Point pExpectedDest = getPosition() + displace;

	Rect moveLimitRect = Rect( getContentSize().width, 
							   getContentSize().height, 
							   UtilFunc::getWinSize().width - getContentSize().width,
							   UtilFunc::getWinSize().height - getContentSize().height );

	if( moveLimitRect.containsPoint(pExpectedDest) )
		setPosition(pExpectedDest);
}