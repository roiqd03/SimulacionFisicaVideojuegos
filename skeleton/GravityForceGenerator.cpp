#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : ForceGenerator("Gravity", -1) {
	setGravity(g);
}

void GravityForceGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	particle->addForce(_gravity * (1.0f / particle->getInvMass()));
}