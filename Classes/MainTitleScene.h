#ifndef __MAINTITLE_SCENE_H__
#define __MAINTITLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainTitleScene : public Scene
{
public:
	CREATE_FUNC(MainTitleScene);
	virtual bool init();
};

class MainTitleLayer : public Layer
{
public:
    virtual bool init();  
    
    void menuCloseCallback(Object* pSender);
	void menuDiveCallback(Object* pSender);
	void menuOptionCallback(Object* pSender);

	void backToMainMenuCallback(Object* pSender);

	//sound
	void togglMusicCallback(Object* pSender);
	void togglEffectCallback(Object* pSender);
    
    CREATE_FUNC(MainTitleLayer);
};

#endif // __MAINTITLE_SCENE_H__
