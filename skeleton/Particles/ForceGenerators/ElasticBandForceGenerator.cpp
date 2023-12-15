#include "ElasticBandForceGenerator.h"
ElasticBandForceGenerator::ElasticBandForceGenerator(double k, double resting_length, Entity* other) : SpringForceGenerator(k, resting_length, other) {}

bool ElasticBandForceGenerator::updateForce(Entity* particle, double t) {
	Vector3 relative_pos_vector = _other->getPosition() - particle->getPosition();
	const float length = relative_pos_vector.normalize();
	if (length > _resting_length) return SpringForceGenerator::updateForce(particle, t);
}