#pragma once
#include "Particle.h"
#include <list>
#include <stack>
#include <random>
#include <chrono>
#include "BoundingBox.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector3 pos, Vector3 mean_vel, Vector3 dev_vel, BoundingBox* boundingBox);
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
	int _num_particles;

	std::normal_distribution<float>* velNormalX;
	std::normal_distribution<float>* velNormalY;
	std::normal_distribution<float>* velNormalZ;
	std::default_random_engine generator;
	Vector3 pos;
	const int maxParticleLifeTime = 10;
	BoundingBox* box;
};

