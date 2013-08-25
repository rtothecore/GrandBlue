#ifndef __JELLYFISH_H__
#define __JELLYFISH_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class JellyfishLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(JellyfishLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual JellyfishLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif