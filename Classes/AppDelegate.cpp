#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainTitleScene.h"
#include "AppMacros.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* director = Director::getInstance();
    EGLView* glView = EGLView::getInstance();

    director->setOpenGLView(glView);
    
    Size size = director->getWinSize();

    // Set the design resolution
	glView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

	Size frameSize = glView->getFrameSize();
    
    vector<string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
		log("ipadhd resource selected");

        searchPath.push_back(largeResource.directory);

        director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
		log("ipad resource selected");

        searchPath.push_back(mediumResource.directory);
        
        director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
		log("iphone resource selected");

        searchPath.push_back(smallResource.directory);

        director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
#else
	log("android resource selected");
	searchPath.push_back(androidResource.directory);
	director->setContentScaleFactor(MIN(androidResource.size.height/designResolutionSize.height, androidResource.size.width/designResolutionSize.width));
#endif
    
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    Scene *scene = HelloWorld::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// ORIGINAL
//bool AppDelegate::applicationDidFinishLaunching() {
//    // initialize director
//    Director* director = Director::getInstance();
//    EGLView* eglView = EGLView::getInstance();
//
//    director->setOpenGLView(eglView);
//	
//    // turn on display FPS
//    director->setDisplayStats(true);
//
//    // set FPS. the default value is 1.0/60 if you don't call this
//    director->setAnimationInterval(1.0 / 60);
//
//    // create a scene. it's an autorelease object
//    Scene *scene = HelloWorld::scene();
//	//Scene *scene = MainTitle::scene();
//
//    // run
//    director->runWithScene(scene);
//
//    return true;
//}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
