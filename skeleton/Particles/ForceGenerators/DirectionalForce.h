#pragma once
#include "ForceGenerator.h"

class DirectionalForce : public ForceGenerator
{
public:
	DirectionalForce(Vector3 force, float duration) : ForceGenerator("Direccional", duration), force(force) {}
	virtual	bool updateForce(Entity* particle, double t) {
		if (updateTime(t, false)) {
			particle->addForce(force);
			return true;
		}
		else return false;
	}
	virtual ~DirectionalForce() {};
protected:
	Vector3 force;
};


