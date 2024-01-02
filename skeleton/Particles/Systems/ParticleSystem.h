#pragma once
#include "../Entities/Particle.h"
#include <list>
#include <stack>
#include <exception>
#include "../Utils/BoundingBox.h"
#include "../ForceGenerators/ParticleForceRegistry.h"

class ParticleSystem
{
public:
	ParticleSystem(BoundingBox* boundingBox = nullptr);
	virtual ~ParticleSystem();
	void integrate(float t);
	void addParticle(Entity* p, ParticleGenerator* pG = nullptr);
	void addGenerator(ParticleGenerator* g, std::string name);
	void addRegistry(ForceGenerator* g, Entity* p);
	void addForceToPartGenerator(ParticleGenerator* p, ForceGenerator* f);
	ParticleGenerator* getParticleGenerator(std::string name);
	void pushErasedParticles(Entity* p);
	void eraseParticles();
	void setEmpty();
	inline int num_particles() { return _particles.size(); }
protected:
	std::list<Entity*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	std::unordered_set<ForceGenerator*> _force_generators;
	std::stack<Entity*> _erased;
	std::unordered_map<std::string, ParticleGenerator*> id_generators;
	int _num_particles;
	ParticleForceRegistry* pFR;

	BoundingBox* box;
};

