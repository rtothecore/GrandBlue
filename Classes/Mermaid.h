#ifndef __MERMAID_H__
#define __MERMAID_H__

#include "cocos2d.h"
#include "MarineLife.h"

USING_NS_CC;

class MermaidLayer : public MarineLifeLayer
{
public:
	CREATE_FUNC(MermaidLayer);

	virtual bool init();
	virtual bool initWithPlist(const char* plist, const char* frameName);
	virtual MermaidLayer* clone() const;
	//virtual bool containsTouchLocation(Touch* touch);
	virtual void playMarineLifeSound();
};

#endif