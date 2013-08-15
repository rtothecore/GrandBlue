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

void UtilFunc::setSizeToScreenSize(Sprite* sprt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float widthRatio = visibleSize.width / sprt->getContentSize().width;
	float heightRatio = visibleSize.height / sprt->getContentSize().height;

	if(widthRatio > heightRatio)
	{
		sprt->setScale(heightRatio);
	} else {
		sprt->setScale(widthRatio);
	}
}