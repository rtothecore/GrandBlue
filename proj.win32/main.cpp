#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    EGLView* eglView = EGLView::getInstance();
    eglView->setViewName("Grandblue");
    //eglView->setFrameSize(480, 320);

	eglView->setFrameSize(720, 1280);	// Galaxy S3
	eglView->setFrameZoomFactor(0.7f);

	//eglView->setFrameSize(320, 480);	// iphone
	//eglView->setFrameZoomFactor(1.8f);

	//eglView->setFrameSize(640, 1136);	// iphone5
	//eglView->setFrameZoomFactor(0.8f);

	//eglView->setFrameSize(768, 1024);	// ipad
	//eglView->setFrameZoomFactor(0.7f);

	//eglView->setFrameSize(1536, 2048);	// ipadHd
	//eglView->setFrameZoomFactor(0.3f);

    return Application::getInstance()->run();
}
