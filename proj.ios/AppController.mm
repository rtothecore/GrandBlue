#import "AppController.h"
#import "EAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#import "GADBannerView.h"
#import "GADRequest.h"
#define GADUnitID @"40b2102b943344b2";

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the CCEAGLView
    CCEAGLView *__glView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // Initialize Admob
    [self initAdmob];
    
    cocos2d::Application::getInstance()->run();

    return YES;
}

// Admob START
- (void)initAdmob{
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    //CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    // bottom
    bannerView_Bottom = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:CGPointMake(0, screenHeight-kGADAdSizeBanner.size.height)];
    [bannerView_Bottom setDelegate:self];
    bannerView_Bottom.rootViewController = viewController;
    bannerView_Bottom.adUnitID = GADUnitID;
    [viewController.view addSubview:bannerView_Bottom];
    
    [bannerView_Bottom loadRequest:[GADRequest request]];   // REAL
    //[bannerView_Bottom loadRequest:[self createrRequest]];    // TEST
    [bannerView_Bottom setHidden:true];
    
    // top
    bannerView_Top = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:CGPointMake(0, 0)];
    [bannerView_Top setDelegate:self];
    bannerView_Top.rootViewController = viewController;
    bannerView_Top.adUnitID = GADUnitID;
    [viewController.view addSubview:bannerView_Top];
    
    [bannerView_Top loadRequest:[GADRequest request]]; // REAL
    //[bannerView_Top loadRequest:[self createrRequest]]; // TEST
    [bannerView_Top setHidden:true];
}

+ (void)setAdmobVisible:(BOOL)visible isTopVisible:(BOOL)isTop {
    if(visible) {
        if(isTop) {
            [bannerView_Top setHidden:false];
        } else {
            [bannerView_Bottom setHidden:false];
        }
    } else {
        if(isTop) {
            [bannerView_Top setHidden:true];
        } else {
            [bannerView_Bottom setHidden:true];
        }
    }
}

- (GADRequest*)createrRequest{
    GADRequest *request = [GADRequest request];
    
    // Make the request for a test ad. Put in an identifier for
    // the simulator as well as any devices you want to receive test ads.
    [request setTesting:TRUE];
    request.testDevices = [NSArray arrayWithObjects:GAD_SIMULATOR_ID, nil];
    
    //NSString *udid = [[UIDevice currentDevice] uniqueIdentifier];
    //NSLog(@"Device udid is %@", udid);
    
    return request;
}

- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received ad successfully");
}

- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive ad with error: %@", [error localizedFailureReason]);
}
// Admob END

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::Director::getInstance()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::Director::getInstance()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [bannerView_Bottom release];
    [bannerView_Top release];
    [window release];
    [super dealloc];
}


@end
