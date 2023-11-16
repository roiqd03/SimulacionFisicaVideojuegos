#include "ParticleForceRegistry.h"

std::unordered_set<ForceGenerator*> ParticleForceRegistry::updateForces(double duration) {
	std::unordered_set<ForceGenerator*> s;
	for (auto it = begin(); it != end();) {
		if (!(it->second->updateForce(it->first, duration))) {
			s.insert(it->second);
			it = erase(it);
		}
		else ++it;
	}
	return s;
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	insert({ p, fg });
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	this->erase(p);
}
