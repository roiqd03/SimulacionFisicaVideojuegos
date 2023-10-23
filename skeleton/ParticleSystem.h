#pragma once
#include "Particle.h"
#include <list>
#include <stack>
#include "BoundingBox.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector3 pos, Vector3 mean_vel, Vector3 dev_vel, BoundingBox* boundingBox);
	~ParticleSystem();
	void integrate(float t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void pushErasedParticles(Particle* p);
	void eraseParticles();
private:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	std::stack<Particle*> _erased;
	int _num_particles;

	BoundingBox* box;
};

