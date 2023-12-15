#include "WhirlWindGenerator.h"


WhirlWindGenerator::WhirlWindGenerator(const float k1, const float k2, Vector3 origin, int whirlMagnitude) : ParticleDragGenerator({0,0,0}, k1, k2), 
	origin(origin), whirlMagnitude(whirlMagnitude) {}

bool WhirlWindGenerator::updateForce(Entity* particle, double t) {
	Vector3 p = particle->getPosition();
	windVelocity = whirlMagnitude * Vector3(-(p.z - origin.z), (p.y - origin.y) / 3, p.x - origin.x);
	return ParticleDragGenerator::updateForce(particle, t);
}

WhirlWindGenerator::~WhirlWindGenerator() {}