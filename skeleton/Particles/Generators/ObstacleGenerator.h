#pragma once
#include "ParticleGenerator.h"

class ObstacleGenerator : public ParticleGenerator
{
public:
	ObstacleGenerator(Vector3 mean_pos, Vector3 mean_vel, int max_obstacles);
	virtual ~ObstacleGenerator();
	std::list<Entity*> generateParticles() override;
	inline void addGenerationLoop(float loop_time) {
		ParticleGenerator::addGenerationLoop(loop_time);
		time = loop_time;
	}
private:
};

