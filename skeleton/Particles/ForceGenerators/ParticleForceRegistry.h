#pragma once
#include "ForceGenerator.h"
#include <unordered_set>
#include <map>

class ParticleForceRegistry : public std::unordered_multimap<Particle*, ForceGenerator*>
{
public:
	std::unordered_set<ForceGenerator*> updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p);
	void deleteParticleRegistry(Particle* p);
};

