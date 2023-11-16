#include "FireworkSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "WhirlWindGenerator.h"
#include "ExplosionGenerator.h"
#include "Firework.h"

FireworkSystem::FireworkSystem(BoundingBox* bb) : ParticleSystem(bb) {
	g = new GaussianParticleGenerator({ 0,0,0 }, { 0,0,0 }, 30, 10, { 5,5,5 }, { 0.01,0.01,0.01 }, 1);
	//WhirlWindGenerator* wWG = new WhirlWindGenerator(2, 0, {30, 0, 0}, 1);
	//UniformParticleGenerator* g = new UniformParticleGenerator({ 1,0,0 }, { 0,50,0 }, 5, 1, { 0.4,0.4,0.4 }, { 10,20,10 }, 2);
	//ParticleDragGenerator* pDG = new ParticleDragGenerator({ 0, 12, 12 }, 1, 0);
	BoundingBox* _bb = new BoundingBox({ 1000,400,1000 });
	_bb->translate({ 0,230,0 });
	//pDG->setBoundingBox(_bb);

	Particle* p = new Particle(1, { 0,0,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(7);
	g->addModelParticle(p, "FIREWORK_BLUE", true);

	p = new Particle(1, { 1,0,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(2);
	g->addModelParticle(p, "FIREWORK_RED", true);

	p = new Particle(2, { 0,1,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/10);
	g->addModelParticle(p, "FIREWORK_GREEN", true);

	p = new Particle(1, { 1,1,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1);
	g->addModelParticle(p, "FIREWORK_YELLOW", true);

	p = new Particle(1, { 0,1,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(40);
	g->addModelParticle(p, "FIREWORK_CYAN", true);

	p = new Particle(0.5, { 1,0,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/3);
	g->addModelParticle(p, "FIREWORK_PURPLE", true);

	p = new Particle(1, { 1,1,1,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/2);
	g->addModelParticle(p, "FIREWORK_WHITE", true);

	p = new Particle(1, { 0,0,0,1 }, 0);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.5f);
	p->setInvMass(10);
	g->addModelParticle(p, "FIREWORK_BLACK", true);

	addGenerator(g, "Fuente");
	//g->addGenerationLoop(0.1);
	getParticleGenerator("Fuente")->addGenerationLoop(0.01);
	//GravityForceGenerator* gFG = new GravityForceGenerator({ 0,-9.8f,0 });
	//addForceToPartGenerator(g, gFG);
	//addForceToPartGenerator(g, pDG);
	
}

FireworkSystem::~FireworkSystem() {

}
void FireworkSystem::explosion() {
	ExplosionGenerator* eG = new ExplosionGenerator({ 10,20,0 }, 10000, 500, 1000, 1);
	addForceToPartGenerator(g, eG);
	for (auto particles : _particles) {
		addRegistry(eG, particles);
	}
}
