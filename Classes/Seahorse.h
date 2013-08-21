#ifndef __SEAHORSE_H__
#define __SEAHORSE_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class SeahorseLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(SeahorseLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual SeahorseLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif