#ifndef __TURTLE_H__
#define __TURTLE_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class SquidLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(SquidLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual SquidLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif