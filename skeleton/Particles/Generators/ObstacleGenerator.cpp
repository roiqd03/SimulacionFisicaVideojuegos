#include "ObstacleGenerator.h"

#include "../Entities/Entity.h"
#include "../../Obstacle.h"
#include "../../GameManager.h"

ObstacleGenerator::ObstacleGenerator(Vector3 mean_pos, Vector3 mean_vel, int max_obstacles) : ParticleGenerator(mean_pos, mean_vel, -1, 1, max_obstacles) {
}

ObstacleGenerator::~ObstacleGenerator() {}

std::list<Entity*> ObstacleGenerator::generateParticles() {
	std::list<Entity*> particles;
	float time = 100.0f;
	for (int i = 0; i < num_particles; ++i) {
		Obstacle* p = static_cast<Obstacle*>(_particle_models[(rand() % _particle_models.size())]->clone());
		if (time > p->loop_time()) {
			time = p->loop_time();
		}
		p->setPosition(mean_pos);
		p->setVelocity(mean_vel);

		particles.push_back(p);
		particles_generated++;
	}
	loop_time = time;
	if (particles_generated >= max_generation_particles) 
		GameManager::lastObstacleGenerated();
	return particles;
}