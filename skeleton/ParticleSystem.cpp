#include "ParticleSystem.h"
#include <iostream>

#include "GaussianParticleGenerator.h"

ParticleSystem::ParticleSystem(BoundingBox* boundingBox) :
	box(boundingBox) {
	GaussianParticleGenerator* g = new GaussianParticleGenerator({ 1,0,0 }, { 0,50,0 }, 5, 1, { 0.2,0.2,0.2 }, { 5,10,5 }, 1);
	_particles_generators.push_back(g);
	Particle* p = new Particle(1, { 0,0,1,1 }, 0);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA1");
	Particle* p1 = new Particle(1, { 0,0,0.5,1 }, 0);
	p1->setGravity({ 0, -10, 0 });
	p1->setDamping(0.99f);
	g->addModelParticle(p1, "AGUA2");
	g->addGenerationLoop(0.1);
}

void ParticleSystem::addParticle(Particle* p) {
	_particles.push_front(p);
	p->setContext(_particles.begin());
}


void ParticleSystem::integrate(float t) {
	for (auto particle : _particles) {
		particle->integrate(t);
		if (particle->getTime() > particle->getLifeTime() || !box->contains(particle->getPosition()))
			pushErasedParticles(particle);
	}

	
	for (auto gens : _particles_generators) {
		if (gens->hasLoop() && gens->isLoopCompleted(t)) {
			auto particles = gens->generateParticles();
			for (auto p : particles) {
				addParticle(p);
			}
		}
	}

	eraseParticles();
}

ParticleSystem::~ParticleSystem() {
	for (auto particle : _particles) {
		delete particle;
	}

	for (auto gens : _particles_generators) {
		delete gens;
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
