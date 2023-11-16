#include "ParticleDragGenerator.h"


ParticleDragGenerator::ParticleDragGenerator(const Vector3 windVelocity, const float k1, const float k2) : ForceGenerator("Drag", -1), 
	windVelocity(windVelocity), _k1(k1), _k2(k2) {}


bool ParticleDragGenerator::updateForce(Particle* particle, double t) {
	if (updateTime(t)) {
		if (fabs(particle->getInvMass()) < 1e-10) return true;

		if (_bb == nullptr || (_bb != nullptr && _bb->contains(particle->getPosition()))) {
			Vector3 v = particle->getVelocity();
			Vector3 diff = windVelocity - v;
			Vector3 force = diff * _k1 + _k2 * diff * diff.magnitude();

			particle->addForce(force);
		}
	}
	return true;
}

ParticleDragGenerator::~ParticleDragGenerator() {
	if (_bb != nullptr) delete _bb;
}
