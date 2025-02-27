#pragma once
class Entity;
#include "../../RenderUtils.hpp"
#include <list>
#include <vector>
#include <random>
#include <chrono>
#include <unordered_map>
class ForceGenerator;

class ParticleGenerator
{
protected:
	Vector3 mean_pos, mean_vel;
	float erase_time;
	std::vector<Entity*> _particle_models;
	std::list<ForceGenerator*> _force_generators;
	std::unordered_map<std::string, int> Particle_Type;
	int num_models;
	std::default_random_engine generator;
	int num_particles;
	bool generateLoop;
	float time, loop_time;
	int max_generation_particles; // if -1, there is no limit
	int particles_generated = 0;
	bool active = true;
public:
	ParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, float erase_time, int num_particles, int max_generation_particles = -1);
	virtual ~ParticleGenerator();
	void setParticle(Entity* _model, std::string _type);
	void addModelParticle(Entity* _model, std::string _type, bool isFirstGenerator = false);
	virtual void addGenerationLoop(float loop_time);
	void addForceGenerator(ForceGenerator* fG);
	std::list<ForceGenerator*>* const getForceGenerators(){ return &_force_generators; }
	inline bool hasLoop() { return generateLoop; }
	bool isLoopCompleted(double t);
	virtual std::list<Entity*> generateParticles() = 0;
	inline void changePosition(Vector3 pos) { mean_pos = pos; }
	bool canGenerateParticles(double t);
	inline bool isActive() { return active; }
	inline void setActive(bool b) { active = b; }
};

