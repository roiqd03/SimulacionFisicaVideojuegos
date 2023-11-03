#pragma once
#include "ForceGenerator.h"
#include <map>

class ParticleForceRegistry : public std::unordered_multimap<Particle*, ForceGenerator*>
{
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p);
	void deleteParticleRegistry(Particle* p);
};

