#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(BoundingBox* boundingBox) :
	box(boundingBox) {
	pFR = new ParticleForceRegistry();
}

void ParticleSystem::addParticle(Particle* p, ParticleGenerator* pG) {
	_particles.push_front(p);
	p->setContext(_particles.begin());
	if (pG != nullptr) {
		for (auto forces : (*pG->getForceGenerators())) {
			addRegistry(forces, p);
		}
	}
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

void ParticleSystem::addRegistry(ForceGenerator* g, Particle* p) {
	pFR->addRegistry(g, p);
	_force_generators.insert(g);
}

void ParticleSystem::addForceToPartGenerator(ParticleGenerator* p, ForceGenerator* f) {
	p->addForceGenerator(f);
}

void ParticleSystem::integrate(float t) {
	for (auto forceGenerator : _force_generators) {
		forceGenerator->updateTime(t);
	}
	auto s = pFR->updateForces(t);
	for (auto forceGenerator : s) {
		_force_generators.erase(forceGenerator);
		delete forceGenerator;
	}

	for (auto particle : _particles) {
		particle->integrate(t);
		if (particle->getTime() > particle->getLifeTime() || (box != nullptr && !box->contains(particle->getPosition())))
			pushErasedParticles(particle);
	}

	
	for (auto gens : _particles_generators) {
		if (gens->hasLoop() && gens->isLoopCompleted(t)) {
			auto particles = gens->generateParticles();
			for (auto p : particles) {
				addParticle(p, gens);
			}
		}
	}

	eraseParticles();
}

ParticleSystem::~ParticleSystem() {
	for (auto particle : _particles) {
		delete particle;
	}

	for (auto gens : _force_generators) {
		delete gens;
	}

	for (auto gens : _particles_generators) {
		delete gens;
	}

	delete pFR;
}


void ParticleSystem::eraseParticles() {
	while (!_erased.empty()) {
		auto e = _erased.top();
		e->onDeath();
		if (e->generatesOnDeath()) {
			auto l = e->generateParticles();
			for (auto p : l.first) {
				addParticle(p, l.second);
			}
		}
		_particles.erase(e->getContext());
		pFR->deleteParticleRegistry(e);
		delete e;
		_erased.pop();
	}
}

void ParticleSystem::pushErasedParticles(Particle* p) {
	_erased.push(p);
}
