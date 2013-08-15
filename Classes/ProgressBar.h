#ifndef __PROGRESS_BAR_H__
#define __PROGRESS_BAR_H__

#include "cocos2d.h"

USING_NS_CC;

class ProgressBarLayer : public Layer
{
private:
	int segmentVal;
	int maxBarWidth;
	int barHeight;

public:
	virtual bool init();
	CREATE_FUNC(ProgressBarLayer);
	
	void initWithSize(int width, int height, int divVal);

	Sprite* sprt_back;
	Sprite* sprt_fore;

	void increaseProgress(int stepVal);
	void decreaseProgress(int stepVal);
	void setProgressWithTagetVal(int targetVal);

	void emptyProgress();
	void fullProgress();
};

#endif