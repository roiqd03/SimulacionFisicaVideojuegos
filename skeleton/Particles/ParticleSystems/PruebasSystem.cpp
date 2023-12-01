#include "PruebasSystem.h"
#include "../ParticleGenerators/GaussianParticleGenerator.h"
#include "../ForceGenerators/GravityForceGenerator.h"
#include "../ForceGenerators/ParticleDragGenerator.h"
#include "../ForceGenerators/WhirlWindGenerator.h"
#include "../ForceGenerators/ExplosionGenerator.h"

PruebasSystem::PruebasSystem(BoundingBox* bb) : ParticleSystem(bb) {
	g = new GaussianParticleGenerator({ 300,0,0 }, { 0,0,0 }, 30, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	GaussianParticleGenerator* g1 = new GaussianParticleGenerator({ -150,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	GaussianParticleGenerator* g2 = new GaussianParticleGenerator({ 0,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	GaussianParticleGenerator* g3 = new GaussianParticleGenerator({ 150,0,0 }, { 0,40,0 }, 10, 1, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	
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

	Particle* p = new Particle(1, { 0,0,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(7);
	g->addModelParticle(p, "BLUE", true);

	p = new Particle(1, { 1,0,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(2);
	g->addModelParticle(p, "RED", true);

	p = new Particle(2, { 0,1,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f / 10);
	g1->addModelParticle(p, "GREEN", true);

	p = new Particle(1, { 1,1,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1);
	g1->addModelParticle(p, "YELLOW", true);

	p = new Particle(1, { 0,1,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(40);
	g2->addModelParticle(p, "CYAN", true);

	p = new Particle(0.5, { 1,0,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f / 3);
	g2->addModelParticle(p, "PURPLE", true);

	p = new Particle(1, { 1,1,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f / 2);
	g3->addModelParticle(p, "WHITE", true);

	p = new Particle(1, { 0,0,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.5f);
	p->setInvMass(10);
	g3->addModelParticle(p, "BLACK", true);

	addGenerator(g, "Explosiones");
	addGenerator(g1, "Gravedad");
	addGenerator(g2, "Viento");
	addGenerator(g3, "Torbellino");
	
	g->addGenerationLoop(0.7);
	g1->addGenerationLoop(0.1);
	g2->addGenerationLoop(0.1);
	g3->addGenerationLoop(0.1);

}

PruebasSystem::~PruebasSystem() {

}
void PruebasSystem::explosion() {
	ExplosionGenerator* eG = new ExplosionGenerator({ 300,0,0 }, 10000, 20, 1000, 1);
	addForceToPartGenerator(g, eG);
	for (auto particles : _particles) {
		addRegistry(eG, particles);
	}
}
