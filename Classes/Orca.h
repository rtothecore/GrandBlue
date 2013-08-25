#ifndef __ORCA_H__
#define __ORCA_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class OrcaLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(OrcaLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual OrcaLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif