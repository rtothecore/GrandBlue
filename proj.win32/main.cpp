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

	/*eglView->setFrameSize(720, 1080);
	eglView->setFrameZoomFactor(0.8f);*/

	eglView->setFrameSize(320, 480);

    return Application::getInstance()->run();
}
