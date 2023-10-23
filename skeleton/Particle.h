#pragma once
#include "RenderUtils.hpp"
#include "ParticleGenerator.h"
#include <list>

class Particle
{
public:
	Particle(float r, Vector4 color, float life_time);
	virtual ~Particle();
	virtual void integrate(double t);
	void setVelocity(Vector3 v);
	void setPosition(Vector3 p);
	void setMass(float f);
	void setAcceleration(Vector3 ac);
	void setGravity(Vector3 g);
	void setDamping(float d);
	inline Vector3 getVelocity() { return vel; }
	inline Vector3 getPosition() { return pose.p; }
	inline float setMass() { return mass; }
	inline Vector3 setAcceleration() { return ac; }
	inline Vector3 setGravity() { return gravity; }
	inline float setDamping() { return damping; }
	inline float getTime() { return time; }
	inline float getLifeTime() { return life_time; }
	inline Vector4 getColor() { return color; }
	inline void setLifeTime(float life_time) { this->life_time = life_time; }
	void setInvisible();
	void setContext(std::list<Particle*>::iterator);
	std::list<Particle*>::iterator getContext();
	virtual Particle* clone() const;
protected:
	std::list<Particle*>::iterator it;
	Vector3 ac;
	float mass;
	float damping;
	float radius;
	Vector4 color;
	float time;
	float life_time;
	Vector3 gravity;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

