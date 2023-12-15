#pragma once
#include "Particle.h"
#include "../Generators/GaussianParticleGenerator.h"

class Firework : public Particle
{
protected:
	int gen;
	static const Vector3 mean_vel;
	static const Vector3 std_dev_vel;
	static const float erased_time;
	static const float std_dev_time;
	int min_particles_generated;
	int max_particles_generated;
public:
	Firework(float size, Vector4 color, float life_time, int gen, int min_particles_generated, int max_particles_generated);
	virtual ~Firework(){};
	void onDeath() override;
	Entity* clone() const override;
};

