#include "Diver.h"
#include "Resource.h"
#include "UtilFunc.h"

bool DiverLayer::init()
{
	healthPoint = st_healthpoint;
	attachedDolphins = 0;
	initWithPlist(p_Diver);
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

		// HP sprite
		sprt_hp = Sprite::create();
		sprt_hp->setTextureRect(CCRectMake(0, 0, 50, 5));
		sprt_hp->setColor(Color3B::RED);
		Size diverSize = frm_diver->getOriginalSize();
		sprt_hp->setPosition(Point(0, diverSize.height / 2 + 5));
		this->addChild(sprt_hp);
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
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
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
    
	decreaseHealthPoint(touch);

    return true;
}

void DiverLayer::decreaseHealthPoint(Touch* touch) 
{
	healthPoint--;

	int hpBar = (50 / st_healthpoint) * healthPoint;
	sprt_hp->setTextureRect(CCRectMake(0, 0, hpBar, 5));

	if(0 == healthPoint) 
	{
		CCLog("HealthPoint is 0");

		// Particle effect
		auto particle = ParticleGalaxy::create();
		particle->setPosition( touch->getLocation() );
		particle->setAutoRemoveOnFinish(true);
		getParent()->addChild(particle);

		// Remove Diver
		this->removeFromParentAndCleanup(true);	
	}
}

void DiverLayer::ccTouchMoved(Touch* touch, Event* event)
{   
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

Rect DiverLayer::getDiverRect()
{
	return Rect( this->getPosition().x - (sprt_diver->getContentSize().width/2),
				 this->getPosition().y - (sprt_diver->getContentSize().height/2),
				 sprt_diver->getContentSize().width,
				 sprt_diver->getContentSize().height );
}

void DiverLayer::refreshDiverPositionWithDolphin()
{
	attachedDolphins++;
	actionDownMoveBy(-20);
}

void DiverLayer::actionDownMoveBy(int yDelta)
{
	auto actionMoveToDown = MoveBy::create( 1.0f, Point(0, yDelta) );
	runAction(actionMoveToDown);
}