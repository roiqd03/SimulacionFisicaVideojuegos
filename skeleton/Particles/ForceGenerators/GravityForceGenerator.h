#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g);
	virtual bool updateForce(Entity* 
		, double t);
	inline void setGravity(Vector3 g) { _gravity = g; }
protected:
	Vector3 _gravity;
};

