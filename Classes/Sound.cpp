#include "Sound.h"
#include "Resource.h"
#include "SimpleAudioEngine.h"
#include "GrandBlueConfig.h"

using namespace CocosDenshion;

float Sound::pitchVal = 1;
float Sound::panVal = 0;
float Sound::gainVal = 1;

Sound::Sound(void)
{
#if (BACKGROUND_MUSIC)
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic( MUSIC_FILE );
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic( FEVER_FILE );
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
#endif

#if (EFFECT_SOUND)
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_BUBBLE_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN1_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN2_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_DOLPHIN3_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_TURTLE1_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_TURTLE2_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_TURTLE3_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_SQUID1_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_SQUID2_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_SQUID3_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_STARFISH1_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_STARFISH2_FILE );
	SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_STARFISH3_FILE );
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
#endif
}

Sound::~Sound(void)
{
	SimpleAudioEngine::end();
}

void Sound::playBackgroundMusic(bool loop)
{
#if (BACKGROUND_MUSIC)
	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, loop);
#endif
}

void Sound::stopBackgroundMusic()
{
#if (BACKGROUND_MUSIC)
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
#endif
}

void Sound::playFeverMusic(bool loop)
{
#if (BACKGROUND_MUSIC)
	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic(FEVER_FILE, loop);
#endif
}

void Sound::stopFeverMusic()
{
#if (BACKGROUND_MUSIC)
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
#endif
}

void Sound::playBubbleEffect()
{
#if (EFFECT_SOUND)
	int bPlay = (rand() % 5);
	if(0 == bPlay)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_BUBBLE_FILE, false, pitchVal, panVal, gainVal);
	}
#endif
}

void Sound::playDolphinEffectRand()
{
#if (EFFECT_SOUND)
	int typeVal = rand() % 2 + 1;
	playDolphinEffectWithType(typeVal);
#endif
}

void Sound::playDolphinEffectWithType(int type)
{
#if (EFFECT_SOUND)
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
#endif
}

void Sound::playTurtleEffectRand()
{
#if (EFFECT_SOUND)
	int typeVal = rand() % 2 + 1;
	playTurtleEffectWithType(typeVal);
#endif
}

void Sound::playTurtleEffectWithType(int type)
{
#if (EFFECT_SOUND)
	switch(type)
	{
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_TURTLE1_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 2:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_TURTLE2_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_TURTLE3_FILE, false, pitchVal, panVal, gainVal);
			break;
		default:
			break;
	}
#endif
}

void Sound::playSquidEffectRand()
{
#if (EFFECT_SOUND)
	int typeVal = rand() % 2 + 1;
	playSquidEffectWithType(typeVal);
#endif
}

void Sound::playSquidEffectWithType(int type)
{
#if (EFFECT_SOUND)
	switch(type)
	{
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_SQUID1_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 2:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_SQUID2_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_SQUID3_FILE, false, pitchVal, panVal, gainVal);
			break;
		default:
			break;
	}
#endif
}

void Sound::playStarfishEffectRand()
{
#if (EFFECT_SOUND)
	int typeVal = rand() % 2 + 1;
	playStarfishEffectWithType(typeVal);
#endif
}

void Sound::playStarfishEffectWithType(int type)
{
#if (EFFECT_SOUND)
	switch(type)
	{
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_STARFISH1_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 2:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_STARFISH2_FILE, false, pitchVal, panVal, gainVal);
			break;
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_STARFISH3_FILE, false, pitchVal, panVal, gainVal);
			break;
		default:
			break;
	}
#endif
}