#include "Particle.h"
#include "UtilFunc.h"
#include "Tags.h"
#include "AppMacros.h"

bool ParticleLayer::init()
{
	return true;
}

ParticleSystem* ParticleLayer::createWithParticlePlist(const char* plist)
{
	ParticleSystem* _emitter = ParticleSystemQuad::create(plist);

	// For multi resolution
	float designRatio = cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / small3Resource.size.width;

	_emitter->setScale(designRatio);

	return _emitter;
}


