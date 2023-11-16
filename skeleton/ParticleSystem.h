#pragma once
#include "Particle.h"
#include <list>
#include <stack>
#include <exception>
#include "BoundingBox.h"
#include "ParticleForceRegistry.h"

class ParticleSystem
{
public:
	ParticleSystem(BoundingBox* boundingBox = nullptr);
	virtual ~ParticleSystem();
	void integrate(float t);
	void addParticle(Particle* p, ParticleGenerator* pG = nullptr);
	void addGenerator(ParticleGenerator* g, std::string name);
	void addRegistry(ForceGenerator* g, Particle* p);
	void addForceToPartGenerator(ParticleGenerator* p, ForceGenerator* f);
	ParticleGenerator* getParticleGenerator(std::string name);
	void pushErasedParticles(Particle* p);
	void eraseParticles();
protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	std::unordered_set<ForceGenerator*> _force_generators;
	std::stack<Particle*> _erased;
	std::unordered_map<std::string, ParticleGenerator*> id_generators;
	int _num_particles;
	ParticleForceRegistry* pFR;

	BoundingBox* box;
};

