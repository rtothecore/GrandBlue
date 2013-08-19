#ifndef __UTILFUNC_H__
#define __UTILFUNC_H__

#include "cocos2d.h"

USING_NS_CC;

class UtilFunc
{
public:
	UtilFunc(void);
	~UtilFunc(void);

	static float getRandomRangeValue(float minVal, float maxVal);
	static Size getVisibleSize();
	static Size getWinSize();
};

#endif