#include "ParticleGenerator.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel) : 
	mean_pos(mean_pos), mean_vel(mean_vel), num_models(0) {}


void ParticleGenerator::setParticle(Particle* _model, std::string _type) {
	_model = _particle_models[Particle_Type[_type]]->clone();
}

void ParticleGenerator::addModelParticle(Particle* _model, std::string _type) {
	_particle_models.push_back(_model);
	Particle_Type[_type] = num_models;
	num_models++;
}
