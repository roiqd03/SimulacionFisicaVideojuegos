#include "Particle.h"
#include <iostream>

Particle::Particle(float r, Vector4 color) : vel({0,0,0}), radius(r), ac({ 0,0,0 }), damping(0), mass(0) {
	pose = physx::PxTransform({0,0,0});
	Vector4 c = color;
	physx::PxSphereGeometry sphere(r);
	physx::PxShape* shape = CreateShape(sphere);
	renderItem = new RenderItem(shape, &pose, c);
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	pose.p += vel * t;
	vel = (vel + ac * t) * pow(damping, t);
}

void Particle::setVelocity(Vector3 v) { vel = v; }
void Particle::setPosition(Vector3 p) { pose.p = p; }

void Particle::setMass(float f) { mass = f; }
void Particle::setAcceleration(Vector3 ac) { this->ac = ac; }
void Particle::setDamping(float d) { damping = d; }