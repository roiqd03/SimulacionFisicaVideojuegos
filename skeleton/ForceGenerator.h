#pragma once
#include "Particle.h"
#include <cmath>

class ForceGenerator
{
public:
	virtual ~ForceGenerator(){}
	virtual void updateForce(Particle* particle, double duration) = 0;
	bool updateTime(double t);
protected:
	ForceGenerator(std::string name, double duration);
	std::string name;
	double t = 0.0;
	double duration = -1e10;

};

