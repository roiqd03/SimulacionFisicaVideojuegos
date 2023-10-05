#pragma once
#include "RenderUtils.hpp"


class Particle
{
public:
	Particle(float r, Vector4 color);
	virtual ~Particle();
	virtual void integrate(double t);
	void setVelocity(Vector3 v);
	void setPosition(Vector3 p);
protected:
	float radius;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

