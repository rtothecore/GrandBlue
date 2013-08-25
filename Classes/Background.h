#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);

	virtual void onEnter();
    virtual void onExit();

	//Node* effectNode;

	void initWithSprite(const char* chrSprt);
	void incrementBlue(short blueOffset);
	//void runEffect();
};

#endif