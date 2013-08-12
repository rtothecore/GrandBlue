#include "Rocks.h"
#include "Resource.h"


Rocks::Rocks(void)
{
}


Rocks::~Rocks(void)
{
}

Rocks* Rocks::createWithTexture(Texture2D* aTexture)
{
    Rocks* pRocks = new Rocks();
    pRocks->initWithTexture( aTexture );
    pRocks->autorelease();

    return pRocks;
}

bool Rocks::initWithTexture(Texture2D* aTexture)
{
    if( Sprite::initWithTexture(aTexture) ) 
    {
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// 좌표
		int orgX = visibleSize.width / 2;
		int orgY = visibleSize.height / 2;
		int destY = getContentSize().height + (getContentSize().height/2);

		// 위치 설정
		setPosition(Point(orgX, orgY));
		setZOrder(1);

		// 하단 이미지 추가
		Sprite *rocks2 = Sprite::createWithTexture(aTexture);
		rocks2->setPosition(Point(getContentSize().width / 2, -getContentSize().height/2));
		rocks2->setZOrder(1);
		this->addChild(rocks2);

		// 속도
		int actualDuration = 3;

		// 액션
		Rocks::actionSequence(this, orgX, destY, actualDuration);
    }
    
    return true;
}

void Rocks::actionSequence(Sprite* spr, int destX, int destY, int actualDuration)
{
	auto actionUp = MoveTo::create( (float)actualDuration, Point(destX, destY) );
	auto actionUpDone = CallFuncN::create( CC_CALLBACK_1(Rocks::rockUpFinished, this) );
	auto rep = RepeatForever::create(Sequence::create( actionUp, actionUpDone, NULL));
	spr->runAction(rep);

	/*
	FiniteTimeAction* actionMoveToLeftBefore = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteFlipY, this) );
	ActionInterval* actionMoveToLeft = MoveTo::create( (float)actualDuration, Point(0 - spr->getContentSize().width/2, actualY) );
	FiniteTimeAction* actionMoveToLeftEaseInOut = EaseInOut::create(actionMoveToLeft, 1.2);
	FiniteTimeAction* actionPause = DelayTime::create(0.5);
	FiniteTimeAction* actionPauseDone = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteUnflipY, this) );
	ActionInterval* actionBackToRight = MoveTo::create( (float)actualDuration, Point(spr->getPosition().x, actualY) );
	FiniteTimeAction* actionBackToRightEaseIn = EaseIn::create(actionBackToRight, 1.2);
	FiniteTimeAction* actionMoveDone = CallFuncN::create( CC_CALLBACK_1(Dolphin::spriteMoveFinished, this) );

    spr->runAction( CCSequence::create(actionMoveToLeftBefore, actionMoveToLeftEaseInOut, actionPause, actionPauseDone, actionBackToRightEaseIn, actionMoveDone, NULL) );
	*/
}

void Rocks::rockUpFinished(Object* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int orgX = visibleSize.width / 2;
	int orgY = visibleSize.height / 2;

	setPosition(Point(orgX, orgY));
}