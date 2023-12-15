#include "RigidSolidSystem.h"
#include "../Generators/GaussianParticleGenerator.h"
#include "../ForceGenerators/GravityForceGenerator.h"
#include "../ForceGenerators/ParticleDragGenerator.h"
#include "../ForceGenerators/WhirlWindGenerator.h"
#include "../ForceGenerators/ExplosionGenerator.h"
#include "../Entities/RigidSolid.h"

RigidSolidSystem::RigidSolidSystem(BoundingBox* bb, physx::PxPhysics* physics, physx::PxScene* scene) : ParticleSystem(bb) {
	g = new GaussianParticleGenerator({ 300,0,0 }, { 0,0,0 }, 30, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	GaussianParticleGenerator* g1 = new GaussianParticleGenerator({ -150,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1, 300);
	GaussianParticleGenerator* g2 = new GaussianParticleGenerator({ 0,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1, 300);
	GaussianParticleGenerator* g3 = new GaussianParticleGenerator({ 150,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1, 300);
	
	GravityForceGenerator* gFG = new GravityForceGenerator({ 0,-9.8f,0 });
	addForceToPartGenerator(g1, gFG);
	addForceToPartGenerator(g2, gFG);
	addForceToPartGenerator(g3, gFG);
	

	ParticleDragGenerator* pDG = new ParticleDragGenerator({ 0, 12, 12 }, 1, 0);
	BoundingBox* _bb = new BoundingBox({200,100,200});
	_bb->translate({ 0,100,0 });
	pDG->setBoundingBox(_bb);
	addForceToPartGenerator(g2, pDG);

	WhirlWindGenerator* wWG = new WhirlWindGenerator(2, 0, {170, 0, 0}, 1);
	_bb = new BoundingBox({ 1000,400,1000 });
	_bb->translate({ 170,0,0 });
	wWG->setBoundingBox(_bb);
	addForceToPartGenerator(g3, wWG);

	RigidSolid* p = new RigidSolid(2.5, { 0,0,1,1 }, 0, false, physics, scene);
	p->setInvMass(7);
	g->addModelParticle(p, "BLUE", true);

	Particle* p2 = new Particle({5, 5, 5}, {1,0,0,1}, 0);
	p2->setInvMass(1.0f/15);
	g->addModelParticle(p2, "RED", true);

	p2 = new Particle(2, { 0,1,0,1 }, 0);
	p2->setInvMass(1.0f / 10);
	g1->addModelParticle(p2, "GREEN", true);

	p = new RigidSolid({ 2, 2, 2 }, { 1,1,0,1 }, 0, false, physics, scene);
	p->setInvMass(1);
	g1->addModelParticle(p, "YELLOW", true);

	p2 = new Particle({ 3, 3, 3 }, { 0,1,1,1 }, 0);
	p2->setInvMass(40);
	g2->addModelParticle(p2, "CYAN", true);

	p = new RigidSolid({ 0.5, 0.5, 0.5 }, { 1,0,1,1 }, 0, false, physics, scene);
	p->setInvMass(1.0f / 3);
	g2->addModelParticle(p, "PURPLE", true);

	p = new RigidSolid(1, { 1,1,1,1 }, 0, false, physics, scene);
	p->setInvMass(1.0f / 2);
	g3->addModelParticle(p, "WHITE", true);

	p = new RigidSolid({ 4, 4, 4 }, { 0,0,0,1 }, 0, false, physics, scene);
	p->setInvMass(10);
	g3->addModelParticle(p, "BLACK", true);

	addGenerator(g, "Explosiones");
	addGenerator(g1, "Gravedad");
	addGenerator(g2, "Viento");
	addGenerator(g3, "Torbellino");
	
	g->addGenerationLoop(0.3);
	g1->addGenerationLoop(0.1);
	g2->addGenerationLoop(0.1);
	g3->addGenerationLoop(0.1);

	p = new RigidSolid({ 500,2,500 }, { 1, 1, 1, 1 }, -1, true, physics, scene);
	p->setPosition({0,-30,0});
	addParticle(p);

}

RigidSolidSystem::~RigidSolidSystem() {

}
void RigidSolidSystem::explosion() {
	ExplosionGenerator* eG = new ExplosionGenerator({ 300,0,0 }, 10000, 1000, 1000, 2);
	addForceToPartGenerator(g, eG);
	for (auto particles : _particles) {
		addRegistry(eG, particles);
	}
}
