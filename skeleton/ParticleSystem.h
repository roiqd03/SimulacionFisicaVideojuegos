#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include <list>
#include <stack>
#include <random>

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void integrate(float t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
	void pushErasedParticles(Particle* p);
	void eraseParticles();
private:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	std::stack<Particle*> _erased;
	const float mean = 1;
	const float stddev = 0.5;
	std::normal_distribution<float>* n;
};

