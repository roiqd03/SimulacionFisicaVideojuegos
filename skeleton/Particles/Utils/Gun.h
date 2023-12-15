#pragma once
#include "../Entities/Projectile.h"
#include <stack>

class Gun 
{
public:
	Gun();
	~Gun();
	enum TypeOfShot { PISTOLA, CAÑON, TANQUE };
	void shoot(TypeOfShot t);
	void integrate(float t);
	void pushErasedParticles(Entity* p);
	void eraseParticles();
private:
	std::list<Entity*> v;
	std::stack<Entity*> erased;
	const int maxParticleLifeTime = 10;
};