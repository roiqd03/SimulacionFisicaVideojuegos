#pragma once
#include "SpringForceGenerator.h"

class ElasticBandForceGenerator : public SpringForceGenerator
{
public:
	ElasticBandForceGenerator(double k, double resting_length, Particle* other);
	virtual	bool updateForce(Particle* particle, double t);
	virtual ~ElasticBandForceGenerator(){}
};

