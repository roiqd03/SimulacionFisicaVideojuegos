#pragma once
class Particle;
#include "RenderUtils.hpp"
#include <list>
#include <vector>
#include <unordered_map>

class ParticleGenerator
{
protected:
	Vector3 mean_pos, mean_vel;
	std::vector<Particle*> _particle_models;
	std::unordered_map<std::string, int> Particle_Type;
	int num_models;
public:
	ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel);
	virtual ~ParticleGenerator() { for (auto part : _particle_models) delete part; }
	void setParticle(Particle* _model, std::string _type);
	void addModelParticle(Particle* _model, std::string _type);
	virtual std::list<Particle*> generateParticles() = 0;
};

