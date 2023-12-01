#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
	std::normal_distribution<float>* velX;
	std::normal_distribution<float>* velY;
	std::normal_distribution<float>* velZ;
	std::normal_distribution<float>* posX;
	std::normal_distribution<float>* posY;
	std::normal_distribution<float>* posZ;
	std::normal_distribution<float>* time;
	Vector3 std_dev_pos, std_dev_vel;
	float std_dev_time;
public:
	GaussianParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time, int num_particles,
		Vector3 std_dev_pos, Vector3 std_dev_vel, float std_dev_time);
	virtual ~GaussianParticleGenerator();
	std::list<Particle*> generateParticles() override;
};

