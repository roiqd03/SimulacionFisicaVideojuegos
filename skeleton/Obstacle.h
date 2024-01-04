#pragma once
#include "Particles/Entities/Particle.h"
#include "Particles/Entities/RigidSolid.h"
const float OBSTACLE_SIZE = 2.8f;

class Obstacle : public Particle
{
public:
	Obstacle(physx::PxPhysics* physics, physx::PxScene* scene, std::vector<std::vector<char>> const& info, float loop_time_after);
	virtual ~Obstacle();
	virtual Entity* clone() const;
	virtual void integrate(double t);
	virtual void setPosition(Vector3 p);
	virtual void setInvisible();
	float loop_time() { return loop_time_after; }
	
private:
	std::list<RigidSolid*> obstacles;
	physx::PxPhysics* physics;
	physx::PxScene* scene;
	std::vector<std::vector<char>> info;
	float loop_time_after;
};

