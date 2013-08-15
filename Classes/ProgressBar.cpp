#include "ProgressBar.h"

enum {
	kTagBackgroundProgress = 0,
	kTagForegroundProgress = 1,
};

bool ProgressBarLayer::init()
{
	return true;
}

void ProgressBarLayer::initWithSize(int width, int height, int divVal)
{
	segmentVal = width / divVal;
	maxBarWidth = width;
	barHeight = height;

	//background sprite
	sprt_back = Sprite::create();
	sprt_back->setTextureRect(CCRectMake(0, 0, maxBarWidth, barHeight));
	sprt_back->setColor(Color3B::RED);
	sprt_back->setAnchorPoint( Point(0, 0) );
	addChild(sprt_back, 0, kTagBackgroundProgress);

	//foreground sprite
	sprt_fore = Sprite::create();
	sprt_fore->setTextureRect(CCRectMake(0, 0, 0, barHeight));
	sprt_fore->setColor(Color3B::YELLOW);
	sprt_fore->setAnchorPoint( Point(0, 0) );
	addChild(sprt_fore, 1, kTagForegroundProgress);
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

void ProgressBarLayer::setProgressWithTagetVal(int targetVal)
{
	int dstWidth = segmentVal * targetVal;

	if(0 > dstWidth)
		dstWidth = 0;
	if(maxBarWidth < dstWidth)
		dstWidth = maxBarWidth;

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