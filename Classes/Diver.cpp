#include "Diver.h"
#include "Resource.h"
#include "UtilFunc.h"

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
		int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

		// Action
		//int actionIndex = (rand() % 2);
		//actionIndex>0 ? Diver::actionSequence(this, actualY, actualDuration) : Diver::actionBezier(this, actualY);
		actionMoveStacked(this, 50, 0);

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

void DiverLayer::spriteFlipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(-1);
}

void DiverLayer::spriteUnflipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(1);
}

void DiverLayer::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

void DiverLayer::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeFromParentAndCleanup(true);
}

void DiverLayer::actionSequence(Layer* lyr, int actualY, int actualDuration)
{
	auto actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteFlipY, this) );
	auto actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - lyr->getContentSize().width/2, actualY) );
	auto actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	auto actionPause = DelayTime::create(0.5);
	auto actionPauseDone = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteUnflipY, this) );
	auto actionBackToRight = MoveTo::create( (float)actualDuration, Point(lyr->getPosition().x, actualY) );
	auto actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteMoveFinished, this) );

    lyr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
}

void DiverLayer::actionBezier(Layer* lyr, int actualY)
{
    ccBezierConfig bezier;
	
    bezier.controlPoint_1 = Point(0, actualY + 200);
    bezier.controlPoint_2 = Point(-250, actualY - 200);
    bezier.endPosition = Point(-500, actualY);
	
	auto towardToLeft = CallFuncN::create(CC_CALLBACK_1(DiverLayer::spriteFlipY, this));
	auto towardToRight = CallFuncN::create(CC_CALLBACK_1(DiverLayer::spriteUnflipY, this));
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
	auto bezierEnd = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteMoveFinished, this) );
    auto rep = RepeatForever::create(Sequence::create( towardToLeft, bezierForward, towardToRight, bezierBack, bezierEnd, NULL));

    lyr->runAction(rep);
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
			CCLog("Diver is falling in love with dolphin");
		}
	}
}

void DiverLayer::runLoveAction()
{
	// rotate 90
	sprt_diver->setRotation(90);

	// move to left screen edge
	auto actionMoveToLeft = MoveTo::create( 5, Point(0 - sprt_diver->getContentSize().width , getPositionY()) );
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(DiverLayer::spriteMoveFinished, this) );
	runAction( Sequence::create(actionMoveToLeft, actionMoveDone, NULL) );
}

void DiverLayer::refreshDiver()
{
	refreshLoveSprite();
}