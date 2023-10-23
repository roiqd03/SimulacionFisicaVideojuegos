#pragma once
class Particle;
#include "RenderUtils.hpp"
#include <list>
#include <vector>
#include <random>
#include <chrono>
#include <unordered_map>

class ParticleGenerator
{
protected:
	Vector3 mean_pos, mean_vel;
	float erase_time;
	std::vector<Particle*> _particle_models;
	std::unordered_map<std::string, int> Particle_Type;
	int num_models;
	std::default_random_engine generator;
	int num_particles;
public:
	ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time, int num_particles);
	virtual ~ParticleGenerator() { for (auto part : _particle_models) delete part; }
	void setParticle(Particle* _model, std::string _type);
	void addModelParticle(Particle* _model, std::string _type);
	virtual std::list<Particle*> generateParticles() = 0;
};

