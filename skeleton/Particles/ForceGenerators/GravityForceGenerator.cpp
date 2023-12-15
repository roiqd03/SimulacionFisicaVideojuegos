#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : ForceGenerator("Gravity", -1) {
	setGravity(g);
}

bool GravityForceGenerator::updateForce(Entity* particle, double t) {
	if (updateTime(t, false)) {
		if (fabs(particle->getInvMass()) < 1e-10)
			return true;

		particle->addForce(_gravity * (1.0f / particle->getInvMass()));
	}
	return true;
}