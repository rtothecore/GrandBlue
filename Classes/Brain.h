#ifndef __BRAIN_H__
#define __BRAIN_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class BrainLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(BrainLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual BrainLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif