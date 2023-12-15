#include "UniformParticleGenerator.h"

#include "../Entities/Entity.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 mean_pos, Vector3 mean_vel,
	float erase_time, int num_particles, Vector3 pos_width, Vector3 vel_width, float time_width) :
	ParticleGenerator(mean_pos, mean_vel, erase_time, num_particles), pos_width(pos_width), vel_width(vel_width)
{
	Vector3 vW = vel_width / 2;
	Vector3 pW = pos_width / 2;
	float tW = time_width / 2;
	posX = new std::uniform_real_distribution<float>(-pW.x, pW.x);
	posY = new std::uniform_real_distribution<float>(-pW.y, pW.y);
	posZ = new std::uniform_real_distribution<float>(-pW.z, pW.z);

	velX = new std::uniform_real_distribution<float>(mean_vel.x - vW.x, mean_vel.x + vW.x);
	velY = new std::uniform_real_distribution<float>(mean_vel.y - vW.y, mean_vel.y + vW.y);
	velZ = new std::uniform_real_distribution<float>(mean_vel.z - vW.z, mean_vel.z + vW.z);

	time = new std::uniform_real_distribution<float>(erase_time - tW, erase_time + tW);
}

UniformParticleGenerator::~UniformParticleGenerator() {
	delete posX;
	delete posY;
	delete posZ;
	delete velX;
	delete velY;
	delete velZ;
	delete time;
}

std::list<Entity*> UniformParticleGenerator::generateParticles() {
	std::list<Entity*> particles;
	for (int i = 0; i < num_particles; ++i) {
		Entity* p = _particle_models[(rand() % _particle_models.size())]->clone();
		p->setPosition(mean_pos + Vector3((*posX)(generator), (*posY)(generator), (*posZ)(generator)));
		p->setVelocity({ (*velX)(generator), (*velY)(generator), (*velZ)(generator) });
		p->setLifeTime((*time)(generator));
		
		particles.push_back(p);
	}
	return particles;
}
