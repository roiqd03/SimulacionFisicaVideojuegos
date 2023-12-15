#pragma once
#include "SpringForceGenerator.h"

class ElasticBandForceGenerator : public SpringForceGenerator
{
public:
	ElasticBandForceGenerator(double k, double resting_length, Entity* other);
	virtual	bool updateForce(Entity* particle, double t);
	virtual ~ElasticBandForceGenerator(){}
};

