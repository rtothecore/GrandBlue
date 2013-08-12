#include "UtilFunc.h"


UtilFunc::UtilFunc(void)
{
}


UtilFunc::~UtilFunc(void)
{
}


int UtilFunc::getRandomRangeValue(int minVal, int maxVal)
{
	int rangeVal = maxVal - minVal;
	return (rand() % rangeVal) + minVal;
}