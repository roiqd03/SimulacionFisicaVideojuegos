#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
protected:
	std::uniform_real_distribution<float>* velX;
	std::uniform_real_distribution<float>* velY;
	std::uniform_real_distribution<float>* velZ;
	std::uniform_real_distribution<float>* posX;
	std::uniform_real_distribution<float>* posY;
	std::uniform_real_distribution<float>* posZ;
	std::uniform_real_distribution<float>* time;
	Vector3 vel_width;
	Vector3 pos_width;
public:
	UniformParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time,
		int num_particles, Vector3 pos_width, Vector3 vel_width, float time_width);
	virtual ~UniformParticleGenerator();
	std::list<Particle*> generateParticles() override;
};



