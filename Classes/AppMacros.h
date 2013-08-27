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


#define ORIENTATION_LANDSCAPE		0
#define ORIENTATION_PORTRAIT		1
#define ORIENTATION		ORIENTATION_PORTRAIT

#if (ORIENTATION == ORIENTATION_LANDSCAPE)
#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
#else
#error unknown target design resolution!
#endif

#else	// ORIENTATION_PORTRAIT

#define DESIGN_RESOLUTION_320X480    0
#define DESIGN_RESOLUTION_768X1024   1
#define DESIGN_RESOLUTION_1536X2048  2
#define DESIGN_RESOLUTION_720X1280   3

// ------------- FOR IOS TEST ------------------
//#define CC_TARGET_PLATFORM CC_PLATFORM_IOS
// ------------- FOR IOS TEST ------------------

/* If you want to switch design resolution, change next line */
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_320X480
#else
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_720X1280
#endif

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::Size(320, 480),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(768, 1024),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(1536, 2048), "ipadhd" };
static Resource androidResource  =  { cocos2d::Size(720, 1280), "android" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_320X480)
static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_768X1024)
static cocos2d::Size designResolutionSize = cocos2d::Size(768, 1024);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1536X2048)
static cocos2d::Size designResolutionSize = cocos2d::Size(1536, 2048);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_720X1280)
static cocos2d::Size designResolutionSize = cocos2d::Size(720, 1280);
#else
#error unknown target design resolution!
#endif

#endif	// ORIENTATION

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 40)
#define STATUS_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 16)
#define MENU_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 18)
#define DIVEFEET_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 18)
#define SCORE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 18)
#define LAP_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 36)
#define FEVER_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 24)
#define HIGHSCORE_FONT_SIZE  (cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width * 12)

#endif /* __APPMACROS_H__ */
