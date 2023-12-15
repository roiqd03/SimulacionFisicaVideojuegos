#pragma once
#include "ParticleSystem.h"

class GaussianParticleGenerator;

class RigidSolidSystem : public ParticleSystem
{
private:
	GaussianParticleGenerator* g;
public:
	RigidSolidSystem(BoundingBox* bb = nullptr, physx::PxPhysics* physics = nullptr, physx::PxScene* scene = nullptr);
	virtual ~RigidSolidSystem();
	void explosion();
};

