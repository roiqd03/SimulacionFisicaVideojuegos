#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(Vector3 pos, Vector3 mean_vel, Vector3 dev_vel, BoundingBox* boundingBox) : 
	box(boundingBox) {


}

void ParticleSystem::integrate(float t) {
	for (auto particle : _particles) {
		particle->integrate(t);
		if (particle->getTime() > particle->getLifeTime() || !box->contains(particle->getPosition()))
			pushErasedParticles(particle);
	}

	eraseParticles();
}

ParticleSystem::~ParticleSystem() {
	for (auto particle : _particles) {
		delete particle;
	}
}


void ParticleSystem::eraseParticles() {
	while (!_erased.empty()) {
		auto e = _erased.top();
		_particles.erase(e->getContext());
		delete e;
		_erased.pop();
	}
}

void ParticleSystem::pushErasedParticles(Particle* p) {
	_erased.push(p);
}
