#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Entity* other) : ForceGenerator("Muelle", -1) {
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

bool SpringForceGenerator::updateForce(Entity* particle, double t) {
	if (active) {
		Vector3 relative_pos_vector = _other->getPosition() - particle->getPosition();
		Vector3 force;

		const float length = relative_pos_vector.normalize();
		const float delta_x = length - _resting_length;

		force = relative_pos_vector * delta_x * _k;

		particle->addForce(force);
	}
	return true;
}