#include "ParticleSystem.h"
#include <iostream>

#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "Firework.h"

ParticleSystem::ParticleSystem(BoundingBox* boundingBox) :
	box(boundingBox) {
	GaussianParticleGenerator* g = new GaussianParticleGenerator({ -10,0,0 }, { 0,40,0 }, 2, 1, { 0.2,0.2,0.2 }, { 5,5,5 }, 0.2);
	//UniformParticleGenerator* g = new UniformParticleGenerator({ 1,0,0 }, { 0,50,0 }, 5, 1, { 0.4,0.4,0.4 }, { 10,20,10 }, 2);
	Firework* p = new Firework(1, { 0,0,1,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA1");
	p = new Firework(1, { 1,0,0,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA2");
	p = new Firework(1, { 0,1,0,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA3");
	p = new Firework(1, { 1,1,0,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA4");
	p = new Firework(1, { 0,1,1,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA5");
	p = new Firework(1, { 1,0,1,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA6");
	p = new Firework(1, { 1,1,1,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA7");
	p = new Firework(1, { 0,0,0,1 }, 0, 3, 7, 10);
	p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "AGUA8");
	addGenerator(g, "Fuente");
	//g->addGenerationLoop(0.1);
	getParticleGenerator("Fuente")->addGenerationLoop(2);
}

void ParticleSystem::addParticle(Particle* p) {
	_particles.push_front(p);
	p->setContext(_particles.begin());
}

void ParticleSystem::addGenerator(ParticleGenerator* g, std::string name) {
	_particles_generators.push_front(g);
	id_generators[name] = g;
}

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name) {
	auto it = id_generators.find(name);
	if (it == id_generators.end()) throw std::invalid_argument("generator does not exist");
	else return (*it).second;
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
		e->onDeath();
		if (e->generatesOnDeath()) {
			auto l = e->generateParticles();
			for (auto p : l) {
				addParticle(p);
			}
		}
		_particles.erase(e->getContext());
		delete e;
		_erased.pop();
	}
}

void ParticleSystem::pushErasedParticles(Particle* p) {
	_erased.push(p);
}
