#ifndef __DOLPHIN_H__
#define __DOLPHIN_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class DolphinLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(DolphinLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual DolphinLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif