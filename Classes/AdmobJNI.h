#ifndef __ADMOBJNI_H__
#define __ADMOBJNI_H__

#include "cocos2d.h"

USING_NS_CC;

class AdmobJNI
{
public:
	AdmobJNI(void);
	~AdmobJNI(void);

	/*
	static float getRandomRangeValue(float minVal, float maxVal);
	static Size getVisibleSize();
	static Size getWinSize();
	*/
	static void setAdmobVisible(bool visible, bool isTop);
};

#endif