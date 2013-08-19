#ifndef __STARFISH_H__
#define __STARFISH_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class StarfishLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(StarfishLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual StarfishLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif