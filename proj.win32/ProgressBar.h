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
	ProgressBarLayer(int width, int height, int divVal);
	~ProgressBarLayer(void);

	Sprite* sprt_back;
	Sprite* sprt_fore;

	void increaseProgress(int stepVal);
	void decreaseProgress(int stepVal);

	void emptyProgress();
	void fullProgress();
};

#endif