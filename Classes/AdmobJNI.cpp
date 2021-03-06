#include "AdmobJNI.h"

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "platform\android\jni\JniHelper.h"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#include "../proj.ios/AppController.h"
#endif

AdmobJNI::AdmobJNI(void)
{
}

AdmobJNI::~AdmobJNI(void)
{
}

void AdmobJNI::setAdmobVisible(bool visible, bool isTop)
{
	// ADMOB JNI
#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/Arette/Grandblue/Grandblue", "SetAdModVisible", "(ZZ)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, visible, isTop);
		t.env->DeleteLocalRef(t.classID);
	}
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [AppController setAdmobVisible:visible isTopVisible:isTop];
#endif
    
}