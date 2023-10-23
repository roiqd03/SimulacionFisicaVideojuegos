#pragma once

#include "Particle.h"

class Gun;

class Projectile : public Particle
{
public:
	Projectile(float radius, Vector4 color, float life_time, Gun* gun = nullptr);
	virtual ~Projectile() = default;
	virtual void integrate(double t);
	void setContext(std::list<Particle*>::iterator);
	std::list<Particle*>::iterator getContext();
	void erase();
private:
	std::list<Particle*>::iterator it;
	Gun* gun = nullptr;
};

