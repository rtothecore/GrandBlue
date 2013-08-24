#ifndef __RAY_H__
#define __RAY_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class RayLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(RayLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual RayLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif