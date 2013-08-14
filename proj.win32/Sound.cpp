#include "Sound.h"
#include "Resource.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

float Sound::pitchVal = 1;
float Sound::panVal = 0;
float Sound::gainVal = 1;

Sound::Sound(void)
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic( MUSIC_FILE );
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic( FEVER_FILE );
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_BUBBLE_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN1_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN2_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN3_FILE );
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
}


Sound::~Sound(void)
{
	SimpleAudioEngine::end();
}


void Sound::playBackgroundMusic(bool loop)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, loop);
}

void Sound::stopBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Sound::playFeverMusic(bool loop)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(FEVER_FILE, loop);
}

void Sound::stopFeverMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Sound::playBubbleEffect()
{
	int bPlay = (rand() % 5);
	if(0 == bPlay)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_BUBBLE_FILE, false, pitchVal, panVal, gainVal);
	}
}

void Sound::playDolphinEffectRand()
{
	int typeVal = rand() % 2 + 1;
	playDolphinEffectWithType(typeVal);
}

void Sound::playDolphinEffectWithType(int type)
{
	switch(type)
	{
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_DOLPHIN1_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 2:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_DOLPHIN2_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_DOLPHIN3_FILE, false, pitchVal, panVal, gainVal);
			break;
		default:
			break;
	}
}