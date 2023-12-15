#include "GaussianParticleGenerator.h"

#include "../Entities/Entity.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 mean_pos, Vector3 mean_vel,
	float erase_time, int num_particles, Vector3 std_dev_pos, Vector3 std_dev_vel, float std_dev_time, int max_generation_particles) :
	ParticleGenerator(mean_pos, mean_vel, erase_time, num_particles, max_generation_particles), std_dev_pos(std_dev_pos), std_dev_vel(std_dev_vel),
	std_dev_time(std_dev_time)
{
	posX = new std::normal_distribution<float>(0, std_dev_pos.x);
	posY = new std::normal_distribution<float>(0, std_dev_pos.y);
	posZ = new std::normal_distribution<float>(0, std_dev_pos.z);

	velX = new std::normal_distribution<float>(mean_vel.x, std_dev_vel.x);
	velY = new std::normal_distribution<float>(mean_vel.y, std_dev_vel.y);
	velZ = new std::normal_distribution<float>(mean_vel.z, std_dev_vel.z);

	time = new std::normal_distribution<float>(erase_time, std_dev_time);
}

GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete posX;
	delete posY;
	delete posZ;
	delete velX;
	delete velY;
	delete velZ;
	delete time;
}

std::list<Entity*> GaussianParticleGenerator::generateParticles() {
	std::list<Entity*> particles;
	for (int i = 0; i < num_particles; ++i) {
		Entity* p = _particle_models[(rand() % _particle_models.size())]->clone();
		p->setPosition(mean_pos + Vector3((*posX)(generator), (*posY)(generator), (*posZ)(generator)));
		p->setVelocity({ (*velX)(generator), (*velY)(generator), (*velZ)(generator) });
		p->setLifeTime((*time)(generator));

		particles.push_back(p);
		particles_generated++;
	}
	return particles;
}
