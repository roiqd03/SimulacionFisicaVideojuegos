#pragma once
#include "ParticleSystem.h"

class GaussianParticleGenerator;

class FireworkSystem : public ParticleSystem
{
private:
	GaussianParticleGenerator* g;
public:
	FireworkSystem(BoundingBox* bb = nullptr);
	virtual ~FireworkSystem();
	void explosion();
};

