#pragma once
#include "Particles/Entities/RigidSolid.h"

const float PLAYER_SIZE = 2;
const Vector4 PLAYER_COLOR = { 1,0,0,1 };
const float PLAYER_SPEED = 2;
const float PLAYER_MASS = 0.5;
const float MAX_TIME_GROUNDED = 0.3f;
const float MAX_TIME_INPUT_STORED = 0.3f;
const float JUMP_OFFSET = 0.1f;

class Player : public RigidSolid
{
public:
	Player(physx::PxPhysics* physics, physx::PxScene* scene);
	virtual ~Player();
	virtual void integrate(double t);
	bool resetJump();
	bool isGrounded() { return grounded; }
	void setGrounded(bool b) {
		grounded = b; if (!b) { timer = 0; _tryJump = false; }
	}
	inline void resetTimer() { timer = 0; }
	virtual void setInvisible();
	virtual void tryJump() {
		_tryJump = true;
		timerJump = 0;
	};
	void clearForce() { rb->clearForce(); }
	void yellowTouched() { yellow_touched = true; };
	bool getYellowTouched() { return yellow_touched; };
private:
	bool grounded = false;
	bool _tryJump = false;
	float timer = MAX_TIME_GROUNDED;
	float timerJump = 0;
	bool yellow_touched = false;
};

