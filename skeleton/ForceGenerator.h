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
	void addContext(std::list<ForceGenerator*>* l, std::list<ForceGenerator*>::iterator pG) { myGenerators.push_back({ l, pG }); }
protected:
	ForceGenerator(std::string name, double duration);
	std::list<std::pair<std::list<ForceGenerator*>*, std::list<ForceGenerator*>::iterator>> myGenerators;
	std::string name;
	double t = 0.0;
	double duration = -1e10;

};

