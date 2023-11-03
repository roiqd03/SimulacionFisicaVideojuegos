#include "ParticleForceRegistry.h"


void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = begin(); it != end(); it++) {
		it->second->updateForce(it->first, duration);
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	insert({ p, fg });
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	auto it = find(p);
	while (it != end()) {
		erase(it);
		it = find(p);
	}
}
