#pragma once
#include "Particle.h"
#include <list>
#include <stack>
#include <exception>
#include "BoundingBox.h"

class ParticleSystem
{
public:
	ParticleSystem(BoundingBox* boundingBox);
	virtual ~ParticleSystem();
	void integrate(float t);
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* g, std::string name);
	ParticleGenerator* getParticleGenerator(std::string name);
	void pushErasedParticles(Particle* p);
	void eraseParticles();
private:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	std::stack<Particle*> _erased;
	std::unordered_map<std::string, ParticleGenerator*> id_generators;
	int _num_particles;

	BoundingBox* box;
};

