#include "UtilFunc.h"


UtilFunc::UtilFunc(void)
{
}


UtilFunc::~UtilFunc(void)
{
}


float UtilFunc::getRandomRangeValue(float minVal, float maxVal)
{
	int rangeVal = maxVal - minVal;
	return (rand() % rangeVal) + minVal;
}

Size UtilFunc::getWinSize()
{
	Size winSize = Director::getInstance()->getWinSize();
	return winSize;
}

Size UtilFunc::getVisibleSize()
{
	Size winSize = Director::getInstance()->getVisibleSize();
	return winSize;
}