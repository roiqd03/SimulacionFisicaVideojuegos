#pragma once
#include "ForceGenerator.h"

class JumpForce : public ForceGenerator
{
public:
	JumpForce(Vector3 force, float time) : ForceGenerator("JUMP", time), force(force) {};
	~JumpForce() {}
	virtual bool updateForce(Entity* particle, double t);

private:
	const Vector3 force;
};

