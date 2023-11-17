#include "FireworkSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "WhirlWindGenerator.h"
#include "ExplosionGenerator.h"
#include "Firework.h"

FireworkSystem::FireworkSystem(BoundingBox* bb) : ParticleSystem(bb) {

	GaussianParticleGenerator* g = new GaussianParticleGenerator({ 0,0,0 }, { 0,30,0 }, 2, 1, { 0.5,0.5,0.5 }, { 5,5,5 }, 0.5);

	Firework* p = new Firework(1, { 0,0,1,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(7);
	g->addModelParticle(p, "FIREWORK_BLUE", true);

	p = new Firework(1, { 1,0,0,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(2);
	g->addModelParticle(p, "FIREWORK_RED", true);

	p = new Firework(2, { 0,1,0,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/10);
	g->addModelParticle(p, "FIREWORK_GREEN", true);

	p = new Firework(1, { 1,1,0,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1);
	g->addModelParticle(p, "FIREWORK_YELLOW", true);

	p = new Firework(1, { 0,1,1,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(40);
	g->addModelParticle(p, "FIREWORK_CYAN", true);

	p = new Firework(0.5, { 1,0,1,1 }, 0, 3, 12, 17);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/3);
	g->addModelParticle(p, "FIREWORK_PURPLE", true);

	p = new Firework(1, { 1,1,1,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	p->setInvMass(1.0f/2);
	g->addModelParticle(p, "FIREWORK_WHITE", true);

	p = new Firework(1, { 0,0,0,1 }, 0, 3, 7, 12);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.5f);
	p->setInvMass(10);
	g->addModelParticle(p, "FIREWORK_BLACK", true);

	addGenerator(g, "Fuente");
	getParticleGenerator("Fuente")->addGenerationLoop(1);
	
	GravityForceGenerator* gFG = new GravityForceGenerator({ 0,-9.8f,0 });
	addForceToPartGenerator(g, gFG);

	
}

FireworkSystem::~FireworkSystem() {

}
