#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(Vector3 origin, int k, float radius, int tau, int explosionTime);
	~ExplosionGenerator() {}
	virtual bool updateForce(Entity* particle, double t);

private:
	const Vector3 origin;
	const int k, tau;
	const float radius;
	int explosionTime;
};
