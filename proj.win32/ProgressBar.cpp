#include "ProgressBar.h"

enum {
	kTagBackgroundProgress = 0,
	kTagForegroundProgress = 1,
};

ProgressBarLayer::ProgressBarLayer(int width, int height, int divVal)
{
	segmentVal = width / divVal;
	maxBarWidth = width;
	barHeight = height;
	/*
	sprite = new Sprite();
    sprite->init();
    sprite->setTextureRect( Rect(0, 0, 300,300) );
    sprite->setColor(Color3B::RED);
    sprite->setOpacity(128);
    sprite->setPosition(Point(3*s.width/4, s.height/2));
    addChild(sprite, 100);
    sprite->release();
	*/

	//background sprite
	sprt_back = Sprite::create();
	sprt_back->setTextureRect(CCRectMake(0, 0, maxBarWidth, barHeight));
	sprt_back->setColor(Color3B::RED);
	sprt_back->setAnchorPoint( Point(0, 0) );
	/*Size dolphinSize = frm_dolphin->getOriginalSize();
	sprt_hp->setPosition(Point(0, dolphinSize.height / 2 + 5));*/
	addChild(sprt_back, 0, kTagBackgroundProgress);

	//foreground sprite
	sprt_fore = Sprite::create();
	sprt_fore->setTextureRect(CCRectMake(0, 0, 0, barHeight));
	sprt_fore->setColor(Color3B::YELLOW);
	sprt_fore->setAnchorPoint( Point(0, 0) );
	addChild(sprt_fore, 1, kTagForegroundProgress);
}

ProgressBarLayer::~ProgressBarLayer(void)
{
	
}

void ProgressBarLayer::increaseProgress(int stepVal)
{
	int orgWidth = sprt_fore->getTextureRect().size.width;
	int dstWidth = orgWidth + (segmentVal * stepVal);
	if(maxBarWidth < dstWidth)
	{
		dstWidth = maxBarWidth;
	}

	sprt_fore->setTextureRect(CCRectMake(0, 0, dstWidth, barHeight));
}

void ProgressBarLayer::decreaseProgress(int stepVal)
{
	int orgWidth = sprt_fore->getTextureRect().size.width;
	int dstWidth = orgWidth - (segmentVal * stepVal);
	if(0 > dstWidth)
	{
		dstWidth = 0;
	}

	sprt_fore->setTextureRect(CCRectMake(0, 0, dstWidth, barHeight));
}

void ProgressBarLayer::emptyProgress()
{
	sprt_fore->setTextureRect(CCRectMake(0, 0, 0, barHeight));
}

void ProgressBarLayer::fullProgress()
{
	sprt_fore->setTextureRect(CCRectMake(0, 0, maxBarWidth, barHeight));
}