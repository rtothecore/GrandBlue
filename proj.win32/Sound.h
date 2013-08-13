#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

USING_NS_CC;

class Sound
{
private:
	static float pitchVal;
    static float panVal;
    static float gainVal;

public:
	Sound(void);
	~Sound(void);

	static void playBackgroundMusic(bool loop);
	static void stopBackgroundMusic();

	static void playBubbleEffect();
	static void playDolphinEffectRand();
	static void playDolphinEffectWithType(int type);
	
	
};

#endif