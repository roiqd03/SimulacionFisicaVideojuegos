#pragma once
#include "Particle.h"
#include <cmath>

class ParticleGenerator;

class ForceGenerator
{
public:
	virtual ~ForceGenerator(){
		for(auto gens : myGenerators){ 
			gens.first->erase(gens.second);
		}
	}
	virtual bool updateForce(Particle* particle, double duration) = 0;
	bool updateTime(double t, bool sum = true);
	void addContext(std::list<ForceGenerator*>* l, std::list<ForceGenerator*>::iterator pG) { myGenerators.insert({ l, pG }); }
	void quitContext(std::list<ForceGenerator*>* l) { myGenerators.erase(l); }
protected:
	ForceGenerator(std::string name, double duration);
	std::unordered_multimap<std::list<ForceGenerator*>*, std::list<ForceGenerator*>::iterator> myGenerators;
	std::string name;
	double t = 0.0;
	double duration = -1e10;

};

