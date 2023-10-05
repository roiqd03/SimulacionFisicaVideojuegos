#include "Projectile.h"


#include "Particle.h"
#include "Gun.h"
#include <iostream>

Projectile::Projectile(float radius, Vector4 color, Gun* gun) : Particle(radius, color), ac({ 0,0,0 }), damping(0), mass(0), speed(0), gun(gun) {}

void Projectile::integrate(double t) {
	vel = (vel + ac * t) * pow(damping, t);
	Particle::integrate(t);
	
	time += t;
	if (time > maxTime) erase();
}

void Projectile::setMass(float f) { mass = f; }
void Projectile::setAcceleration(Vector3 ac) { this->ac = ac; }
void Projectile::setDamping(float d) { damping = d; }
void Projectile::setContext(std::list<Particle*>::iterator it2) { it = it2; }
std::list<Particle*>::iterator  Projectile::getContext() { return it; }
void Projectile::erase() {
	if (gun != nullptr) gun->pushErasedParticles(this);
}
