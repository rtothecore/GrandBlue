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

	static void playFeverMusic(bool loop);
	static void stopFeverMusic();

	static void playBubbleEffect();

	// dolphin
	static void playDolphinEffectRand();
	static void playDolphinEffectWithType(int type);

	// turtle
	static void playTurtleEffectRand();
	static void playTurtleEffectWithType(int type);
};

#endif