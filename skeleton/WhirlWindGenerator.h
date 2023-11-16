#pragma once
#include "ParticleDragGenerator.h"

class WhirlWindGenerator : public ParticleDragGenerator
{
public:
	WhirlWindGenerator(const float k1, const float k2, Vector3 origin, int whirlMagnitude);
	virtual bool updateForce(Particle* particle, double t);
	~WhirlWindGenerator();
private:
	Vector3 origin;
	int whirlMagnitude;
};

