#pragma once
#include "ForceGenerator.h"
#include "../Utils/BoundingBox.h"

class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator(const Vector3 windVelocity, const float k1, const float k2);
	virtual ~ParticleDragGenerator();
	virtual bool updateForce(Entity* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return _k1; }
	inline float getK2() { return _k2; }
	inline void setBoundingBox(BoundingBox* _bb) { if (this->_bb != nullptr) delete this->_bb; this->_bb = _bb; }

protected:
	float _k1;
	float _k2;
	Vector3 windVelocity;
	BoundingBox* _bb = nullptr;
};

