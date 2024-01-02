#include "JumpForce.h"

bool JumpForce::updateForce(Entity* particle, double t) {
	if (updateTime(t, false)) {
		if (fabs(particle->getInvMass()) < 1e-10)
			return true;

		particle->addForce(force);
		return true;
	}
	else return false;
}