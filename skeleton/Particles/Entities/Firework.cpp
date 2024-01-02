#include "Firework.h"
#include "../ForceGenerators/GravityForceGenerator.h"

const Vector3 Firework::mean_vel = { 0,4,0 };
const Vector3 Firework::std_dev_vel = { 4, 3, 4 };
const float Firework::erased_time = 1.0f;
const float Firework::std_dev_time = 0.2f;


Firework::Firework(float size, Vector4 color, float life_time, int gen, int min_particles_generated, int max_particles_generated) : 
	Particle(size, color, life_time), gen(gen), min_particles_generated(min_particles_generated), 
	max_particles_generated(max_particles_generated) {}

void Firework::onDeath() {
	if (gen > 0) {
		int diff = max_particles_generated - min_particles_generated;
		if (diff == 0)
			diff = 1;
		GaussianParticleGenerator* g = new GaussianParticleGenerator(pose.p, mean_vel, erased_time,
			rand() % (diff) + min_particles_generated, { 0.1,0.1,0.1 }, std_dev_vel, std_dev_time);
		Firework* p = new Firework(size.x * 0.75, color, 0, gen - 1, min_particles_generated * 0.75, max_particles_generated * 0.75);
		//p->setGravity({ 0, -10, 0 });
		p->setDamping(0.99f);
		g->addModelParticle(p, "FIREWORK");
		p->setInvMass(1);
		p->setFirstGenerator(firstGenerator);
		for (auto forces : (*firstGenerator->getForceGenerators())) {
			g->addForceGenerator(forces);
		}
		addGenerator(g);
	}
}

Entity* Firework::clone() const {
	Firework* _particle = new Firework(size.x, color, life_time, gen, min_particles_generated, max_particles_generated);

	_particle->pose.p = pose.p;
	_particle->vel = vel;
	_particle->ac = ac;
	//_particle->gravity = gravity;
	_particle->inv_mass = inv_mass;
	_particle->damping = damping;
	_particle->firstGenerator = firstGenerator;

	return _particle;
}