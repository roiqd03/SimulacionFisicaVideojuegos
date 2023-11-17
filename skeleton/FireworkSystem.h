#pragma once
#include "ParticleSystem.h"

class FireworkSystem : public ParticleSystem
{
public:
	FireworkSystem(BoundingBox* bb = nullptr);
	virtual ~FireworkSystem();
};

