#import <UIKit/UIKit.h>

#import "GADBannerView.h"
@class GADBannerView, GADRequest;
 
@class RootViewController;

static GADBannerView *bannerView_Bottom;
static GADBannerView *bannerView_Top;

//@interface AppController : NSObject <UIApplicationDelegate> {
@interface AppController : NSObject <UIApplicationDelegate, GADBannerViewDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

