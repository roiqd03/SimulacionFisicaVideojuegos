//#include "FireworkGenerator.h"
//
//#include "Particle.h"
//
//FireworkGenerator::FireworkGenerator(Vector3 mean_pos, Vector3 mean_vel,
//	float erase_time, int num_particles, Vector3 std_dev_pos, Vector3 std_dev_vel, float std_dev_time) :
//	GaussianParticleGenerator(mean_pos, mean_vel, erase_time, num_particles, std_dev_pos, std_dev_vel, std_dev_time)
//{}
//
//std::list<Particle*> FireworkGenerator::generateParticles() {
//	std::list<Particle*> particles;
//	for (int i = 0; i < num_particles; ++i) {
//		Particle* p = _particle_models[0]->clone();
//		p->setPosition(mean_pos);
//		p->setVelocity({ (*velX)(generator), (*velY)(generator), (*velZ)(generator) });
//		p->setLifeTime((*time)(generator));
//
//		particles.push_back(p);
//	}
//	return particles;
//}
