#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pose = physx::PxTransform(Pos);
	Vector4 color = {255, 0, 0, 1};
	physx::PxSphereGeometry sphere(10);
	physx::PxShape* shape = CreateShape(sphere);
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	pose.p = pose.p + vel * speed * t;
}