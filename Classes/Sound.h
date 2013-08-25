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

	static bool bMusic;
	static bool bEffect;

public:
	Sound(void);
	~Sound(void);

	static bool isMusicOn();
	static bool isEffectOn();
	
	static void toggleMusic();
	static void toggleEffect();

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

	// squid
	static void playSquidEffectRand();
	static void playSquidEffectWithType(int type);

	// starfish
	static void playStarfishEffectRand();
	static void playStarfishEffectWithType(int type);

	// seahorse
	static void playSeahorseEffectWithType(int type);

	// mermaid
	static void playMermaidEffectRand();
	static void playMermaidEffectWithType(int type);

	// ray
	static void playRayEffectRand();
	static void playRayEffectWithType(int type);

	// jellyfish
	static void playJellyfishEffectRand();
	static void playJellyfishEffectWithType(int type);

	// orca
	static void playOrcaEffectRand();
	static void playOrcaEffectWithType(int type);

	// diver
	static void playDiverEffectWithType(int type);

	// score
	static void playScoreEffect();
	
};

#endif