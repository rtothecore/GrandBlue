#include "ProgressBar.h"
#include "Tags.h"


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
	sprt_back->setTextureRect(Rect(0, 0, maxBarWidth, barHeight));
	sprt_back->setColor(Color3B::BLUE);
	sprt_back->setAnchorPoint( Point(0, 0) );
	addChild(sprt_back, 0, kTagSprtBackgroundProgress);

	//foreground sprite
	sprt_fore = Sprite::create();
	sprt_fore->setTextureRect(Rect(0, 0, maxBarWidth, barHeight));
	sprt_fore->setColor(Color3B::YELLOW);
	sprt_fore->setAnchorPoint( Point(1, 0) );
	addChild(sprt_fore, 1, kTagSprtForegroundProgress);
}

void ProgressBarLayer::setProgressWithTagetVal(int targetVal)
{
	int dstWidth = segmentVal * targetVal;

	if(0 > dstWidth)
		dstWidth = 0;
	if(maxBarWidth < dstWidth)
		dstWidth = maxBarWidth;

	auto actionScaleToX = MoveTo::create( 0.5f, Point(dstWidth, 0) );
	sprt_fore->runAction(actionScaleToX);
}