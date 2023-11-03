#include "FireworkSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "Firework.h"

FireworkSystem::FireworkSystem(BoundingBox* bb) : ParticleSystem(bb) {
	GaussianParticleGenerator* g = new GaussianParticleGenerator({ -10,0,0 }, { 0,40,0 }, 2, 1, { 0.2,0.2,0.2 }, { 5,5,5 }, 0.2);
	//UniformParticleGenerator* g = new UniformParticleGenerator({ 1,0,0 }, { 0,50,0 }, 5, 1, { 0.4,0.4,0.4 }, { 10,20,10 }, 2);

	Firework* p = new Firework(1, { 0,0,1,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_BLUE");

	p = new Firework(1, { 1,0,0,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_RED");

	p = new Firework(2, { 0,1,0,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_GREEN");

	p = new Firework(1, { 1,1,0,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_YELLOW");

	p = new Firework(1, { 0,1,1,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_CYAN");

	p = new Firework(0.5, { 1,0,1,1 }, 0, 3, 15, 20);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_PURPLE");

	p = new Firework(1, { 1,1,1,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.99f);
	g->addModelParticle(p, "FIREWORK_WHITE");

	p = new Firework(1, { 0,0,0,1 }, 0, 3, 7, 10);
	//p->setGravity({ 0, -10, 0 });
	p->setDamping(0.5f);
	g->addModelParticle(p, "FIREWORK_BLACK");

	addGenerator(g, "Fuente");
	//g->addGenerationLoop(0.1);
	getParticleGenerator("Fuente")->addGenerationLoop(0.5);
}

FireworkSystem::~FireworkSystem() {

}