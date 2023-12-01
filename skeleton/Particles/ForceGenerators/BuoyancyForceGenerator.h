#pragma once
#include "ForceGenerator.h"
#include "../Utils/BoundingBox.h"
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(Vector3 pos, Vector3 dim, float d, float g);
	virtual bool updateForce(Particle* particle, double t);
	virtual ~BuoyancyForceGenerator();
private:
	BoundingBox* _bb;
	float _height_limit;
	Particle* visual_liquid;
	float _volume;
	float _liquid_density;
	float _gravity;
};

