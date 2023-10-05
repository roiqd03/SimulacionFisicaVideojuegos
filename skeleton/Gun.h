#pragma once
#include "Projectile.h"
#include <stack>

class Gun 
{
public:
	Gun();
	~Gun();
	enum TypeOfShot { PISTOLA, CAÑON, TANQUE };
	void shoot(TypeOfShot t);
	void integrate(float t);
	void pushErasedParticles(Particle* p);
	void eraseParticles();
private:
	std::list<Particle*> v;
	std::stack<Particle*> erased;
};