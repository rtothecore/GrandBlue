#include "Particle.h"
#include "UtilFunc.h"
#include "Tags.h"

bool ParticleLayer::init()
{
	return true;
}

void ParticleLayer::runFireWork()
{
	ParticleSystem* _emitter = ParticleSystemQuad::create("particles/LavaFlow.plist");
	
	Node *node = Node::create();
	addChild(node);

	node->addChild(_emitter);
}

ParticleSystem* ParticleLayer::createWithParticlePlist(const char* plist)
{
	ParticleSystem* _emitter = ParticleSystemQuad::create(plist);
	return _emitter;
}


