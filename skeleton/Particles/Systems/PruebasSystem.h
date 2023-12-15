#pragma once
#include "ParticleSystem.h"

class GaussianParticleGenerator;

class PruebasSystem : public ParticleSystem
{
private:
	GaussianParticleGenerator* g;
public:
	PruebasSystem(BoundingBox* bb = nullptr);
	virtual ~PruebasSystem();
	void explosion();
};

