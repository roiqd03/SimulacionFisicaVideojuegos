#include "BuoyancyForceGenerator.h"
#include "../Entities/Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(Vector3 pos, Vector3 dim, float d, float g) : ForceGenerator("Flotación", -1) {
	_bb = new BoundingBox(- dim / 2, dim / 2);
	_bb->translate(pos);
	_volume = dim.x*dim.y*dim.z;
	_liquid_density = d;
	_gravity = g;
	visual_liquid = new Particle(dim, { 0,0,1,0 }, -1);
	visual_liquid->setPosition(pos);
	_height_limit = pos.y + dim.y / 2;
}

bool BuoyancyForceGenerator::updateForce(Entity* particle, double t) {
	Vector3 pos_particle = particle->getPosition();
	float size = particle->getSize().y;
	if (_bb->contains(pos_particle - Vector3(0, size / 2, 0))) {
		float immersed;
		float highest_point = pos_particle.y + size / 2;
		if (highest_point <= _height_limit) {
			immersed = 1.0f;
		}
		else immersed = (size - (highest_point - _height_limit)) / size;

		Vector3 force(0, 0, 0);
		force.y = _liquid_density * particle->getVolume() * immersed * _gravity;
		particle->addForce(force);
	}
	return true;
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete visual_liquid;
	delete _bb;
}