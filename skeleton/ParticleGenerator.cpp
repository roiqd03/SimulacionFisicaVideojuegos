#include "ParticleGenerator.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time, int num_particles) : 
	mean_pos(mean_pos), mean_vel(mean_vel), num_models(0), erase_time(erase_time), num_particles(num_particles),
	generator(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())) {}


void ParticleGenerator::setParticle(Particle* _model, std::string _type) {
	_model = _particle_models[Particle_Type[_type]]->clone();
}

void ParticleGenerator::addModelParticle(Particle* _model, std::string _type) {
	_particle_models.push_back(_model);
	_model->setInvisible();
	Particle_Type[_type] = num_models;
	num_models++;
}
