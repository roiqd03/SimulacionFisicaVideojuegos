#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	n = new std::normal_distribution<float>(mean, stddev);
}

ParticleSystem::~ParticleSystem() {
	delete n;
}

void ParticleSystem::integrate(float t) {
	for (auto particle : _particles) {
		particle->integrate(t);
	}
}


void ParticleSystem::eraseParticles() {
}

void ParticleSystem::pushErasedParticles(Particle* p) {
	_erased.push(p);
}
