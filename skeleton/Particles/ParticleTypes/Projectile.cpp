#include "Projectile.h"


#include "Particle.h"
#include "../Utils/Gun.h"
#include <iostream>

Projectile::Projectile(float radius, Vector4 color, float life_time, Gun* gun) : Particle(radius, color, life_time), gun(gun) {}

void Projectile::integrate(double t) {
	Particle::integrate(t);
	
	time += t;
}

void Projectile::setContext(std::list<Particle*>::iterator it2) { it = it2; }
std::list<Particle*>::iterator  Projectile::getContext() { return it; }
void Projectile::erase() {
	if (gun != nullptr) gun->pushErasedParticles(this);
}
