#pragma once
#include "RenderUtils.hpp"
#include "ParticleGenerator.h"
#include <list>

class Particle
{
public:
	Particle(float r, Vector4 color);
	virtual ~Particle();
	virtual void integrate(double t);
	void setVelocity(Vector3 v);
	void setPosition(Vector3 p);
	inline Vector3 getPosition() { return pose.p; }
	inline Vector3 getVelocity() { return vel; }
	inline float getTime() { return time; }
	void setMass(float f);
	void setAcceleration(Vector3 ac);
	void setDamping(float d);
	void setContext(std::list<Particle*>::iterator);
	std::list<Particle*>::iterator getContext();
protected:
	std::list<Particle*>::iterator it;
	Vector3 ac;
	float mass;
	float damping;
	float radius;
	float time;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

