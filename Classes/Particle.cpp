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
	float designRatio = cocos2d::EGLView::getInstance()->getDesignResolutionSize().width / smallResource.size.width;

	//_emitter->setStartSize(designRatio * _emitter->getStartSize());
	//_emitter->setStartSizeVar(designRatio * _emitter->getStartSizeVar());
	//
	//_emitter->setEndSize(designRatio * _emitter->getEndSize());
	//_emitter->setEndSizeVar(designRatio * _emitter->getEndSizeVar());

	_emitter->setScale(designRatio);

	return _emitter;
}


