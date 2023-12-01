#include "SpringsSystem.h"
#include "../ForceGenerators/AnchoredSpringFG.h"
#include "../ForceGenerators/SpringForceGenerator.h"
#include "../ForceGenerators/ElasticBandForceGenerator.h"
#include "../ForceGenerators/GravityForceGenerator.h"
#include "../ForceGenerators/DirectionalForce.h"
#include "../ForceGenerators/BuoyancyForceGenerator.h"

SpringsSystem::SpringsSystem() : ParticleSystem(nullptr) {
	aSFG = new AnchoredSpringFG(1, 20, {200,20,0});
	GravityForceGenerator* gFG = new GravityForceGenerator({ 0, -9.8, 0 });
	particle = new Particle(3, { 0,0,1,1 }, -1);
	particle->setPosition({ 200, 15, 0 });
	addParticle(particle);
	particle->setInvMass(1);
	addRegistry(aSFG, particle);
	addRegistry(gFG, particle);
	particle = new Particle(3, { 1,0,0,1 }, -1);
	particle->setPosition({ 200,40, -30 });
	addParticle(particle);
	particle->setInvMass(1);
	addRegistry(aSFG, particle);
	addRegistry(gFG, particle);


	Particle* part = new Particle(2, { 1,1,0,1 }, -1);
	part->setPosition({ -30, 60, -30 });
	addParticle(part);
	part->setInvMass(0.5);

	Particle* part2 = new Particle(2, { 1,0,1,1 }, -1);
	part2->setPosition({ -10, 60, -30 });
	addParticle(part2);
	part2->setInvMass(5);
	ElasticBandForceGenerator* sFG = new ElasticBandForceGenerator(3, 10, part2);
	ElasticBandForceGenerator* sFG2 = new ElasticBandForceGenerator(3, 10, part);
	addRegistry(sFG, part);
	addRegistry(sFG2, part2);

	Particle* part3 = new Particle(2, { 1,1,0,1 }, -1);
	part3->setPosition({ -30, 80, -30 });
	addParticle(part3);
	part3->setInvMass(2);

	Particle* part4 = new Particle(2, { 1,0,1,1 }, -1);
	part4->setPosition({ -10, 80, -30 });
	addParticle(part4);
	part4->setInvMass(2);
	ElasticBandForceGenerator* sFG3 = new ElasticBandForceGenerator(3, 10, part4);
	ElasticBandForceGenerator* sFG4 = new ElasticBandForceGenerator(3, 10, part3);
	addRegistry(sFG3, part3);
	addRegistry(sFG4, part4);

	Particle* part5 = new Particle(2, { 0,0,0,1 }, -1);
	part5->setPosition({ -30, 100, -30 });
	addParticle(part5);
	part5->setInvMass(2);

	Particle* part6 = new Particle(2, { 1,1,1,1 }, -1);
	part6->setPosition({ -10, 100, -30 });
	addParticle(part6);
	part6->setInvMass(2);
	SpringForceGenerator* sFG5 = new SpringForceGenerator(3, 10, part6);
	SpringForceGenerator* sFG6 = new SpringForceGenerator(3, 10, part5);
	addRegistry(sFG5, part5);
	addRegistry(sFG6, part6);

	BuoyancyForceGenerator* bFG = new BuoyancyForceGenerator({ 0,-20,0 }, { 100, 10, 20 }, 1000, 9.8);
	Particle* part7 = new Particle({ 2, 3, 2 }, { 1,0,0,1 }, -1);
	part7->setPosition({ -40, 5, 0 });
	part7->setDamping(0.95);
	addParticle(part7);
	part7->setInvMass(1/200.0f);
	addRegistry(bFG, part7);
	addRegistry(gFG, part7);

	particleForBuoyancy = new Particle({ 2, 3, 2 }, { 1,1,0,1 }, -1);
	particleForBuoyancy->setPosition({ -20, 5, 0 });
	particleForBuoyancy->setDamping(0.90);
	addParticle(particleForBuoyancy);
	particleForBuoyancy->setInvMass(1 / 2000.0f);
	addRegistry(bFG, particleForBuoyancy);
	addRegistry(gFG, particleForBuoyancy);

	part7 = new Particle({ 4, 6, 4 }, { 1,0,0,1 }, -1);
	part7->setPosition({ 0, 5, 0 });
	part7->setDamping(0.90);
	addParticle(part7);
	part7->setInvMass(1 / 200.0f);
	addRegistry(bFG, part7);
	addRegistry(gFG, part7);

	part7 = new Particle({ 8, 12, 8 }, { 1,1,0,1 }, -1);
	part7->setPosition({ 20, 5, 0 });
	part7->setDamping(0.90);
	addParticle(part7);
	part7->setInvMass(1 / 200.0f);
	addRegistry(bFG, part7);
	addRegistry(gFG, part7);
}

SpringsSystem::~SpringsSystem() {}

void SpringsSystem::applyDirectionalForce() {
	DirectionalForce* dF = new DirectionalForce({ -70,0,0 }, 3);
	addRegistry(dF, particle);
}

void SpringsSystem::changeK(float k) {
	aSFG->setK(aSFG->getK() + k);
}

void SpringsSystem::changeMass(float k) {
	float aux = particleForBuoyancy->getInvMass() + k;
	if (aux >= 1/50.0f) aux = 1/50.0f;
	particleForBuoyancy->setInvMass(aux);
}

void SpringsSystem::changeVolume(float k) {
	float aux = particleForBuoyancy->getVolume() + k;
	if (aux <= 0) aux = 0;
	particleForBuoyancy->setVolume(aux);
}