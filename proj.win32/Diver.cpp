#include "Diver.h"
#include "Resource.h"
#include "UtilFunc.h"

Diver::Diver(void)
{
	healthPoint = st_healthpoint;
}


Diver::~Diver(void)
{
}

Diver* Diver::clone() const
{
	Diver* ret = Diver::createWithPlist();
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());
    return ret;
}

Diver* Diver::createWithPlist()
{
	Diver* pDiver = new Diver();
	pDiver->initWithPlist(p_Diver);
	pDiver->autorelease();

	return pDiver;
}

bool Diver::initWithPlist(const char* plist)
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
		Size visibleSize = Director::getInstance()->getVisibleSize();
		int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, visibleSize.height/1.4 - getContentSize().height);

		// Set to the screen right edge
		//setPosition(Point(visibleSize.width + (getContentSize().width / 2), actualY));
		setPosition(Point(visibleSize.width / 2, 500));

		// Velocity
		int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

		// Action
		//int actionIndex = (rand() % 2);
		//actionIndex>0 ? Diver::actionSequence(this, actualY, actualDuration) : Diver::actionBezier(this, actualY);
		Diver::actionMoveStacked(this, 50, 0);

		// HP sprite
		sprt_hp = Sprite::create();
		sprt_hp->setTextureRect(CCRectMake(0, 0, 50, 5));
		sprt_hp->setColor(ccRED);
		Size diverSize = frm_diver->getOriginalSize();
		sprt_hp->setPosition(Point(0, diverSize.height / 2 + 5));
		this->addChild(sprt_hp);
	}

	return true;
}

void Diver::actionMoveStacked(Layer *lyr, int destX, int destY)
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

Rect Diver::getRect()
{
	Size s = frm_diver->getOriginalSize();
	
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void Diver::onEnter()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    Layer::onEnter();
}

void Diver::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool Diver::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Diver::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) ) return false;
    
	decreaseHealthPoint(touch);

    return true;
}

void Diver::decreaseHealthPoint(Touch* touch) 
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

void Diver::ccTouchMoved(Touch* touch, Event* event)
{   
}

void Diver::ccTouchEnded(Touch* touch, Event* event)
{    
}

void Diver::spriteFlipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(-1);
}

void Diver::spriteUnflipY(Object* pSender)
{
	Layer *layer = (Layer *)pSender;
	layer->setScaleX(1);
}

void Diver::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

void Diver::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeFromParentAndCleanup(true);
}

void Diver::actionSequence(Layer* lyr, int actualY, int actualDuration)
{
	auto actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(Diver::spriteFlipY, this) );
	auto actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - lyr->getContentSize().width/2, actualY) );
	auto actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	auto actionPause = DelayTime::create(0.5);
	auto actionPauseDone = CallFuncN::create( CC_CALLBACK_1(Diver::spriteUnflipY, this) );
	auto actionBackToRight = MoveTo::create( (float)actualDuration, Point(lyr->getPosition().x, actualY) );
	auto actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	auto actionMoveDone = CallFuncN::create( CC_CALLBACK_1(Diver::spriteMoveFinished, this) );

    lyr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
}

void Diver::actionBezier(Layer* lyr, int actualY)
{
    ccBezierConfig bezier;
	
    bezier.controlPoint_1 = Point(0, actualY + 200);
    bezier.controlPoint_2 = Point(-250, actualY - 200);
    bezier.endPosition = Point(-500, actualY);
	
	auto towardToLeft = CallFuncN::create(CC_CALLBACK_1(Diver::spriteFlipY, this));
	auto towardToRight = CallFuncN::create(CC_CALLBACK_1(Diver::spriteUnflipY, this));
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
	auto bezierEnd = CallFuncN::create( CC_CALLBACK_1(Diver::spriteMoveFinished, this) );
    auto rep = RepeatForever::create(Sequence::create( towardToLeft, bezierForward, towardToRight, bezierBack, bezierEnd, NULL));

    lyr->runAction(rep);
}