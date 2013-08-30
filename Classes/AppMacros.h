#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

// ------------- FOR IOS TEST ------------------
//#define CC_TARGET_PLATFORM CC_PLATFORM_IOS
// ------------- FOR IOS TEST ------------------

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

#define ORIENTATION_LANDSCAPE		0
#define ORIENTATION_PORTRAIT		1
#define ORIENTATION		ORIENTATION_PORTRAIT

#if (ORIENTATION == ORIENTATION_LANDSCAPE)	// ORIENTATION_LANDSCAPE
static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource small5Resource = { cocos2d::Size(1136, 640),   "iphone5" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
static Resource androidResource  =  { cocos2d::Size(1280, 720), "android" };
#else	// ORIENTATION_PORTRAIT
static Resource small3Resource  =  { cocos2d::Size(320, 480),   "iphone3" };
static Resource smallResource  =  { cocos2d::Size(640, 960),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(768, 1024),  "ipad"   };
static Resource small5Resource = { cocos2d::Size(640, 1136),   "iphone5" };
static Resource largeResource  =  { cocos2d::Size(1536, 2048), "ipadhd" };
static Resource androidResource  =  { cocos2d::Size(720, 1280), "android" };
#endif

static cocos2d::Size designResolutionSize;

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 40)
#define STATUS_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 16)
#define MENU_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 18)
#define DIVEFEET_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 18)
#define RESULT_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 18)
#define SCORE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 24)
#define LAP_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 36)
#define FEVER_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 24)
#define HIGHSCORE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width * 12)

#endif /* __APPMACROS_H__ */
