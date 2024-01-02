#pragma once
#include "Particles/Systems/ParticleSystem.h"
#include "Player.h"

const float JUMP_FORCE = 110.0f;
const float YELLOW_JUMP_FORCE = 300.0f;
const float GRAVITY_FORCE = 150.0f;
const float OBSTACLE_VEL = 12.0f;
const float DEAD_TIME = 2.0f;
const float COLLISION_MARGIN = 0.1f;
const int NUM_OF_OBSTACLES= 10;
enum GameStates { START, PLAYING, DEAD, WIN };

class GameManager
{
private:
	static BoundingBox* bb;
	static ParticleSystem* system;
	static Player* player;
	static ParticleSystem* playerParticles;
	static bool end;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
	GameStates state = START;
	float time = 0;
	float half_player_size;
public:
	GameManager(physx::PxPhysics* physics, physx::PxScene* scene);
	~GameManager();
	void update(double t);
	void processInput(unsigned char key);
	void onStart();
	void onGameOver();
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	static void jump(float force);
	static void lastObstacleGenerated();
};

