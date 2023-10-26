#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(BoundingBox* boundingBox) :
	box(boundingBox) {
	
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
