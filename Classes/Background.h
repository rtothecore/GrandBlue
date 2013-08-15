#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);

	virtual void onEnter();
    virtual void onExit();

	Node* effectNode;

	static BackgroundLayer* create();
	void initWithSprite(const char* chrSprt);
	void runEffect();
};

#endif