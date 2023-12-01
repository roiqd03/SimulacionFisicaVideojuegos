#include "ExplosionGenerator.h"
#include <cmath>

ExplosionGenerator::ExplosionGenerator(Vector3 origin, int k, float radius, int tau, int explosionTime) : ForceGenerator("Explosion", explosionTime), 
	origin(origin), k(k), radius(radius), tau(tau) {}

bool ExplosionGenerator::updateForce(Particle* particle, double t) {
	if (updateTime(t, false)) {
		if (fabs(particle->getInvMass()) < 1e-10)
			return true;

		Vector3 distV = particle->getPosition() - origin;
		float dist = distV.magnitude();
		if (dist <= radius) {
			Vector3 force = k * (particle->getPosition() - origin) / pow(dist, 2) * exp(-this->t / tau);
			particle->addForce(force);
		}
		return true;
	}
	else return false;
}