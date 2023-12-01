#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual	bool updateForce(Particle* particle, double t);
	inline void setK(double k) { _k = k; }
	inline double getK() { return _k; }
	virtual ~SpringForceGenerator(){};
protected:
	double _k;
	double _resting_length;
	Particle* _other;
};

