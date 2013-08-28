#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cocos2d.h"

USING_NS_CC;

class ParticleLayer : public Layer
{
public:
	CREATE_FUNC(ParticleLayer);
	virtual bool init();
	
	static ParticleSystem* createWithParticlePlist(const char* plist);
	
};

#endif