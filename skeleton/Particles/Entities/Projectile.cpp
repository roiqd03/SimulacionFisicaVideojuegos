#include "Projectile.h"


#include "Particle.h"
#include "../Utils/Gun.h"
#include <iostream>

Projectile::Projectile(float radius, Vector4 color, float life_time, Gun* gun) : Particle(radius, color, life_time), gun(gun) {}

void Projectile::integrate(double t) {
	Particle::integrate(t);
}

void Projectile::setContext(std::list<Entity*>::iterator it2) { it = it2; }
std::list<Entity*>::iterator  Projectile::getContext() { return it; }
void Projectile::erase() {
	if (gun != nullptr) gun->pushErasedParticles(this);
}
