#pragma once
#include "../../RenderUtils.hpp"
#include "../Generators/ParticleGenerator.h"
#include "Entity.h"
#include <list>

class Particle : public Entity
{
public:
	Particle(float radius, Vector4 color, float life_time);
	Particle(Vector3 size, Vector4 color, float life_time);
	virtual ~Particle();
	virtual void integrate(double t);
	virtual void setVelocity(Vector3 v);
	virtual void setPosition(Vector3 p);
	virtual inline void setInvMass(float _inv_mass) { 
		inv_mass = _inv_mass; 
		Entity::setInvMass(_inv_mass);
	}
	virtual void setAcceleration(Vector3 ac);
	void setDamping(float d);
	virtual inline Vector3 getVelocity() { return vel; }
	virtual inline Vector3 getPosition() { return pose.p; }
	virtual inline Vector3 getAcceleration() { return ac; }
	inline float getDamping() { return damping; }
	virtual inline float getInvMass() { return inv_mass; }
	virtual Entity* clone() const;
	virtual void onDeath(){};

	virtual void addForce(const Vector3& f) { force += f; }
protected:
	Vector3 ac;
	float inv_mass;
	float damping;
	bool sphereShape;
	Vector3 vel;
	physx::PxTransform pose;
};

