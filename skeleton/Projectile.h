#pragma once

#include "Particle.h"
#include <list>

class Gun;

class Projectile : public Particle
{
public:
	Projectile(float radius, Vector4 color, Gun* gun = nullptr);
	virtual ~Projectile() = default;
	virtual void integrate(double t);
	void setContext(std::list<Particle*>::iterator);
	std::list<Particle*>::iterator getContext();
	void erase();
private:
	std::list<Particle*>::iterator it;
	Gun* gun = nullptr;

	const int maxTime = 10;
	double time = 0;
};

