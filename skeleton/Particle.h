#pragma once
#include "RenderUtils.hpp"
#include "ParticleGenerator.h"

class Particle
{
public:
	Particle(float r, Vector4 color);
	virtual ~Particle();
	virtual void integrate(double t);
	void setVelocity(Vector3 v);
	void setPosition(Vector3 p);
	void setMass(float f);
	void setAcceleration(Vector3 ac);
	void setDamping(float d);
protected:
	Vector3 ac;
	float mass;
	float damping;
	float radius;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

