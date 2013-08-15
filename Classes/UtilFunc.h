#ifndef __UTILFUNC_H__
#define __UTILFUNC_H__

#include "cocos2d.h"

USING_NS_CC;

class UtilFunc
{
public:
	UtilFunc(void);
	~UtilFunc(void);

	static int getRandomRangeValue(int minVal, int maxVal);
	static void setSizeToScreenSize(Sprite* sprt);
};

#endif