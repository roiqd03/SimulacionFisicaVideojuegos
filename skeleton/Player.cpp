#include "Player.h"
#include "GameManager.h"

Player::Player(physx::PxPhysics* physics, physx::PxScene* scene) : RigidSolid({PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE }, PLAYER_COLOR, -1, false, physics, scene) {
	resetJump();
	actor->setName("PLAYER");
	rb->setMass(PLAYER_MASS);

	//Entity::setInvMass(1.0f/PLAYER_MASS);
	//physx::PxRigidBodyExt::updateMassAndInertia(*rb, );
}

Player::~Player() {

}

void Player::integrate(double t) {
	RigidSolid::integrate(t);
	if (_tryJump) {
		if (grounded) {
			GameManager::jump(JUMP_FORCE);
			_tryJump = false;
		}
		else {
			timerJump += t;
			if (timerJump > MAX_TIME_INPUT_STORED) {
				_tryJump = false;
			}
		}
	}
	auto tr = rb->getGlobalPose();
	tr.p = { 0, tr.p.y, 0 };
	tr.q = physx::PxQuat(0, 0, 0, 1);
	rb->setGlobalPose(tr);
	timer += t;
}

#include <iostream>
bool Player::resetJump() {
	if (timer > MAX_TIME_GROUNDED) {
		std::cout << "GROUNDEADO XD\n";
		rb->setLinearVelocity({ 0,0,0 });
		rb->clearForce();
		grounded = true;
		yellow_touched = false;
		timer = 0;
		return true;
	}
	return false;
}


void Player::setInvisible() {
	Entity::setInvisible();
}
