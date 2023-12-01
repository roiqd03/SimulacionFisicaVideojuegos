#pragma once
#include "ParticleSystem.h"
class AnchoredSpringFG;

class SpringsSystem : public ParticleSystem
{
private:
	Particle* particle;
	Particle* particleForBuoyancy;
	AnchoredSpringFG* aSFG;

public:
	SpringsSystem();
	virtual ~SpringsSystem();
	void applyDirectionalForce();
	void changeK(float k);
	void changeMass(float k);
	void changeVolume(float k);
};

