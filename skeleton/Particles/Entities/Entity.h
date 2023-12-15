#pragma once
#include "../../RenderUtils.hpp"
#include "../Generators/ParticleGenerator.h"
#include <list>

class Entity
{
public:
	Entity(Vector3 size, Vector4 color, float life_time);
	virtual ~Entity();
	virtual void integrate(double t);
	virtual void setVelocity(Vector3 v) = 0;
	virtual void setPosition(Vector3 p) = 0;
	virtual inline void setInvMass(float _inv_mass) {
		if (_inv_mass != 0)
			density = 1.0f / _inv_mass / volume;
		else density = 0;
	}
	virtual void setAcceleration(Vector3 ac) = 0;
	virtual inline Vector3 getVelocity() = 0;
	inline float getVolume() { return volume; }
	virtual inline Vector3 getPosition() = 0;
	virtual inline Vector3 getAcceleration() = 0;
	inline float getDensity() { return density; }
	inline float getTime() { return time; }
	virtual inline float getInvMass() = 0;
	inline float getLifeTime() { return life_time; }
	inline Vector4 getColor() { return color; }
	inline void setLifeTime(float life_time) { this->life_time = life_time; }
	void setInvisible();
	void setFirstGenerator(ParticleGenerator* myG) { firstGenerator = myG; };
	void setContext(std::list<Entity*>::iterator);
	std::list<Entity*>::iterator getContext();
	virtual Entity* clone() const = 0;
	inline bool generatesOnDeath() { return generator != nullptr; }
	inline std::pair<std::list<Entity*>, ParticleGenerator*> generateParticles() { generator->changePosition(getPosition());  return { generator->generateParticles(), generator }; }
	void addGenerator(ParticleGenerator* g);
	virtual void onDeath() {};
	virtual inline Vector3 getSize() { return size; }

	Vector3 force;
	virtual void addForce(const Vector3& f) = 0;
	void clearAccum() { force = Vector3(0, 0, 0); }
protected:
	std::list<Entity*>::iterator it;
	Vector4 color;
	float time;
	float life_time;
	float volume;
	float density;
	Vector3 size;
	RenderItem* renderItem;
	ParticleGenerator* generator = nullptr;
	ParticleGenerator* firstGenerator = nullptr;
};

