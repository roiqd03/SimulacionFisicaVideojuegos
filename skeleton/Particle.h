#pragma once
#include "RenderUtils.hpp"


class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();
	void integrate(double t);

private:
	Vector3 vel;
	const float speed = 15;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

