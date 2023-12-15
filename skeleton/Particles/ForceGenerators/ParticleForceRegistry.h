#pragma once
#include "ForceGenerator.h"
#include <unordered_set>
#include <map>

class ParticleForceRegistry : public std::unordered_multimap<Entity*, ForceGenerator*>
{
public:
	std::unordered_set<ForceGenerator*> updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Entity* p);
	void deleteParticleRegistry(Entity* p);
};

