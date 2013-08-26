#include "Particle.h"

bool ParticleLayer::init()
{
	return true;
}

void ParticleLayer::runFirework()
{
	ParticleSystem* _emitter = ParticleSystemQuad::create("particles/LavaFlow.plist");
	
	Node *node = Node::create();
	addChild(node);

	node->addChild(_emitter);
}