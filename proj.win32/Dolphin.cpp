#include "Dolphin.h"

Dolphin::Dolphin(void)
{
	healthPoint = st_healthpoint;
}


Dolphin::~Dolphin(void)
{
}

void Dolphin::spriteFlipY(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	sprite->setFlipX(true);
}

void Dolphin::spriteUnflipY(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	sprite->setFlipX(false);
}

void Dolphin::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

void Dolphin::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeFromParentAndCleanup(true);
}

int Dolphin::getRandomRangeValue(int minVal, int maxVal)
{
	int rangeVal = maxVal - minVal;
	return (rand() % rangeVal) + minVal;
}

void Dolphin::actionSequence(Sprite* spr, int actualY, int actualDuration)
{
	FiniteTimeAction* actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteFlipY, this) );
	ActionInterval* actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - spr->getContentSize().width/2, actualY) );
	FiniteTimeAction* actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	FiniteTimeAction* actionPause = DelayTime::create(0.5);
	FiniteTimeAction* actionPauseDone = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteUnflipY, this) );
	ActionInterval* actionBackToRight = MoveTo::create( (float)actualDuration, Point(spr->getPosition().x, actualY) );
	FiniteTimeAction* actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	FiniteTimeAction* actionMoveDone = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteMoveFinished, this) );

    spr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
}

void Dolphin::actionBezier(Sprite* spr, int actualY)
{
    ccBezierConfig bezier;
	
    bezier.controlPoint_1 = Point(0, actualY + 200);
    bezier.controlPoint_2 = Point(-250, actualY - 200);
    bezier.endPosition = Point(-500, actualY);
	
	auto towardToLeft = CallFuncN::create(CC_CALLBACK_1(Dolphin::spriteFlipY, this));
	auto towardToRight = CallFuncN::create(CC_CALLBACK_1(Dolphin::spriteUnflipY, this));
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
	auto bezierEnd = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteMoveFinished, this) );
    auto rep = RepeatForever::create(Sequence::create( towardToLeft, bezierForward, towardToRight, bezierBack, bezierEnd, NULL));

    spr->runAction(rep);
}

Rect Dolphin::getRect()
{
    Size s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

Dolphin* Dolphin::createWithTexture(Texture2D* aTexture)
{
    Dolphin* pDolphin = new Dolphin();
    pDolphin->initWithTexture( aTexture );
    pDolphin->autorelease();

    return pDolphin;
}

bool Dolphin::initWithTexture(Texture2D* aTexture)
{
    if( Sprite::initWithTexture(aTexture) ) 
    {
        //_state = kDolphinStateUngrabbed;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// 돌고래 생성 Y좌표
		int actualY = getRandomRangeValue(getContentSize().height, visibleSize.height/1.4 - getContentSize().height);

		// 돌고래를 오른쪽 끝에서 생성되도록 위치 설정
		setPosition(Point(visibleSize.width + (getContentSize().width / 2), actualY));

		// 속도
		int actualDuration = getRandomRangeValue(2.0, 4.0);

		// 액션 
		int actionIndex = (rand() % 2);
		actionIndex>0 ? Dolphin::actionSequence(this, actualY, actualDuration) : Dolphin::actionBezier(this, actualY);

		// 체력 게이지
		sprt_hp = Sprite::create();
		sprt_hp->setTextureRect(CCRectMake(0, 0, 50, 5));
		sprt_hp->setColor(ccRED);
		CCSize dolphinSize = this->getContentSize();
		sprt_hp->setPosition(Point(dolphinSize.width / 2, dolphinSize.height + 10));
		this->addChild(sprt_hp);
    }
    
    return true;
}

void Dolphin::onEnter()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    Sprite::onEnter();
}

void Dolphin::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Sprite::onExit();
}    

bool Dolphin::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Dolphin::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) ) return false;
    
	decreaseHealthPoint(touch);

    return true;
}

void Dolphin::decreaseHealthPoint(Touch* touch) 
{
	healthPoint--;

	int hpBar = (50 / st_healthpoint) * healthPoint;
	sprt_hp->setTextureRect(CCRectMake(0, 0, hpBar, 5));

	if(0 == healthPoint) 
	{
		CCLog("HealthPoint is 0");

		//파티클 효과
		auto particle = ParticleExplosion::create();
		particle->setPosition( touch->getLocation() );
		particle->setAutoRemoveOnFinish(true);
		getParent()->addChild(particle);

		//Dolphine 객체 제거
		this->removeFromParentAndCleanup(true);	
	}
}

void Dolphin::ccTouchMoved(Touch* touch, Event* event)
{   
	/*
    Point touchPoint = touch->getLocation();   
    setPosition( Point(touchPoint.x, getPosition().y) );
	*/
}

void Dolphin::ccTouchEnded(Touch* touch, Event* event)
{    
} 

Dolphin* Dolphin::clone() const
{
    Dolphin* ret = Dolphin::createWithTexture(_texture);
    ret->setPosition(getPosition());
    ret->setAnchorPoint(getAnchorPoint());
    return ret;
}