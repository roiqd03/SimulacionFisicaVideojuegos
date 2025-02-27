#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Entity* other);
	virtual	bool updateForce(Entity* particle, double t);
	inline void setK(double k) { _k = k; }
	inline double getK() { return _k; }
	virtual ~SpringForceGenerator(){};
	inline void setActive(bool b) { active = b; }
	inline bool isActive() { return active; }
protected:
	double _k;
	double _resting_length;
	Entity* _other;
	bool active = true;
};

