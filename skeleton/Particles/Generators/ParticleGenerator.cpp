#include "ParticleGenerator.h"
#include "../Entities/Entity.h"
#include "../ForceGenerators/ForceGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time, int num_particles) : 
	mean_pos(mean_pos), mean_vel(mean_vel), num_models(0), erase_time(erase_time), num_particles(num_particles),
	generator(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())), generateLoop(false),
	time(0) {}


void ParticleGenerator::setParticle(Entity* _model, std::string _type) {
	_model = _particle_models[Particle_Type[_type]]->clone();
}

void ParticleGenerator::addModelParticle(Entity* _model, std::string _type, bool isFirstGenerator) {
	_particle_models.push_back(_model);
	_model->setInvisible();
	Particle_Type[_type] = num_models;
	num_models++;
	if (isFirstGenerator) _model->setFirstGenerator(this);
}

void ParticleGenerator::addGenerationLoop(float loop_time) {
	this->loop_time = loop_time;
	generateLoop = true;
}

bool ParticleGenerator::isLoopCompleted(float t) {
	time += t;
	if (time > loop_time) {
		time = 0;
		return true;
	}
	else return false;
}


void ParticleGenerator::addForceGenerator(ForceGenerator* fG) {
	_force_generators.push_front(fG);
	fG->addContext(&_force_generators, _force_generators.begin());
}

ParticleGenerator::~ParticleGenerator() {
	for (auto part : _particle_models) delete part;
	for (auto forces : _force_generators) forces->quitContext(&_force_generators);
}