#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
	_other = new Particle({ 3,3,3 }, { 0,0,0,1 }, -1);
	_other->setPosition(anchor_pos);
}

AnchoredSpringFG::~AnchoredSpringFG() {
	delete _other;
}