#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(Vector3 pos, Vector3 mean_vel, Vector3 dev_vel, BoundingBox* boundingBox) : 
	generator(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())), pos(pos), box(boundingBox) {
	velNormalX = new std::normal_distribution<float>(mean_vel.x, dev_vel.x);
	velNormalY = new std::normal_distribution<float>(mean_vel.y, dev_vel.y);
	velNormalZ = new std::normal_distribution<float>(mean_vel.z, dev_vel.z);

}

void ParticleSystem::integrate(float t) {
	for (auto particle : _particles) {
		particle->integrate(t);
		if (particle->getTime() > maxParticleLifeTime || !box->contains(particle->getPosition())) 
			pushErasedParticles(particle);
	}

	Vector4 color = { 0, 0, (float)(rand() % 256 / 255.0f),1 };
	_particles.push_front(new Particle(0.5, color));
	auto part = _particles.begin();
	(*part)->setPosition(pos);
	(*part)->setVelocity({ (*velNormalX)(generator), (*velNormalY)(generator), (*velNormalZ)(generator) });
	(*part)->setGravity({ 0,-10.0f,0 });
	(*part)->setDamping(1);
	(*part)->setContext(_particles.begin());


	eraseParticles();
}

ParticleSystem::~ParticleSystem() {
	for (auto particle : _particles) {
		delete particle;
	}
	delete velNormalX;
	delete velNormalY;
	delete velNormalZ;
}


void ParticleSystem::eraseParticles() {
	while (!_erased.empty()) {
		auto e = _erased.top();
		_particles.erase(e->getContext());
		delete e;
		_erased.pop();
	}
}

void ParticleSystem::pushErasedParticles(Particle* p) {
	_erased.push(p);
}
