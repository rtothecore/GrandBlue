#ifndef __MAINTITLE_SCENE_H__
#define __MAINTITLE_SCENE_H__

#include "cocos2d.h"

class MainTitle : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
	void menuDiveCallback(Object* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainTitle);
};

#endif // __MAINTITLE_SCENE_H__
