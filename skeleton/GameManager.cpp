#include "GameManager.h"
#include "Particles/ForceGenerators/GravityForceGenerator.h"
#include "Particles/ForceGenerators/JumpForce.h"
#include "Particles/Generators/ObstacleGenerator.h"
#include "Particles/Generators/GaussianParticleGenerator.h"
#include "Obstacle.h"
#include "Particles/Entities/Firework.h"

BoundingBox* GameManager::bb = nullptr;
ParticleSystem* GameManager::system = nullptr;
Player* GameManager::player = nullptr;
ParticleSystem* GameManager::playerParticles = nullptr;
bool GameManager::end = false;

GameManager::GameManager(physx::PxPhysics* physics, physx::PxScene* scene) : gPhysics(physics), gScene(scene) {
	state = START;
}

void GameManager::onStart() {
	BoundingBox* bb = new BoundingBox({ 80,200,50 });

	system = new ParticleSystem(bb);
	player = new Player(gPhysics, gScene);
	GravityForceGenerator* gFG = new GravityForceGenerator({ 0,-GRAVITY_FORCE,0 });

	system->addParticle(player);
	system->addRegistry(gFG, player); // Generador se añade si no está

	RigidSolid* ground = new RigidSolid({ 70, 3, 50 }, { 0,0,0,1 }, -1, true, gPhysics, gScene);
	system->addParticle(ground);

	player->setPosition({ 0, 0, 0 });
	ground->setPosition({ 0, -10, 0 });
	ground->changeName("SUELO");

	half_player_size = PLAYER_SIZE / 2;
	playerParticles = new ParticleSystem(nullptr);
	GaussianParticleGenerator* gPG = new GaussianParticleGenerator(player->getPosition() - Vector3(half_player_size, half_player_size, half_player_size), { -5,0,0 }, 3, 1, { 0.1,0.1,0.1 }, { 1, 2, 2 }, 1, -1);
	playerParticles->addGenerator(gPG, "IZQ_PLAYER");
	gPG->addGenerationLoop(0.05);
	gPG->setActive(false);
	Particle* p = new Particle(0.2, { 1,0.5,0,1 }, 0);
	p->setInvMass(1.0f / 5.0f);
	gPG->addModelParticle(p, "NARANJA", true);
	p = new Particle(0.1, { 1,0,0,1 }, 0);
	p->setInvMass(1.0f);
	gPG->addModelParticle(p, "ROJO", true);

	gPG = new GaussianParticleGenerator(player->getPosition() - Vector3(half_player_size, half_player_size, -half_player_size), { -5,0,0 }, 3, 1, { 0.1,0.1,0.1 }, { 1, 2, 2 }, 1, -1);
	playerParticles->addGenerator(gPG, "DER_PLAYER");
	gPG->addGenerationLoop(0.05);
	gPG->setActive(false);
	p = new Particle(0.2, { 1,0.5,0,1 }, 0);
	gPG->addModelParticle(p, "NARANJA", true);
	p->setInvMass(1.0f / 5.0f);
	p = new Particle(0.1, { 1,0,0,1 }, 0);
	p->setInvMass(1.0f);
	gPG->addModelParticle(p, "ROJO", true);

	ObstacleGenerator* obsGen = new ObstacleGenerator({ 40, -10 + 1.5f + OBSTACLE_SIZE / 2, 0 }, { -OBSTACLE_VEL,0,0 }, NUM_OF_OBSTACLES);
	Obstacle* obs = new Obstacle(gPhysics, gScene, {
	{'0','0','0', '0', '2', '0', '0', '0'},
	{'0','0','1', '1', '1', '1', '1', '0'},
	{'1','0','1', '1', '1', '1', '1', '0'}
		}, 2.7f);
	obsGen->addModelParticle(obs, "CONSECUTIVOS", true);
	obs = new Obstacle(gPhysics, gScene, {
	{'0','0','0','0'},
	{'0','0','0','1'},
	{'2','0','3','1'}
		}, 2.0f);
	obsGen->addModelParticle(obs, "CONSECUTIVOS", true);
	obs = new Obstacle(gPhysics, gScene, {
	{'0','0','0'},
	{'0','0','0'},
	{'0','2','0'}
		}, 1.7f);
	obsGen->addModelParticle(obs, "CONSECUTIVOS", true);
	obs = new Obstacle(gPhysics, gScene, {
	{'0','0','0','0'},
	{'0','2','4','4'},
	{'3','1','0','0'}
	}, 2.5f);
	obsGen->addModelParticle(obs, "CONSECUTIVOS", true);
	system->addGenerator(obsGen, "OBSTACULOS");
	obsGen->addGenerationLoop(2);
}


GameManager::~GameManager() {
	delete system;
}

void GameManager::update(double t) {
	if (state != START) {
		system->integrate(t);
		playerParticles->integrate(t);
		if (state == PLAYING) {
			gScene->simulate(t);
			gScene->fetchResults(true);
			if (end && system->num_particles() == 2) { // PLAYER Y SUELO
				state = WIN;
				playerParticles->getParticleGenerator("IZQ_PLAYER")->setActive(false);
				playerParticles->getParticleGenerator("DER_PLAYER")->setActive(false);
				GravityForceGenerator* gFG = new GravityForceGenerator({ 0,-9.8f,0 });
				GaussianParticleGenerator* gPG = new GaussianParticleGenerator(player->getPosition() - Vector3(PLAYER_SIZE * 2, -half_player_size, 0), { 0,25,0 }, 0.7f, 1, { 0.1,0.1,0.1 }, { 4,1,4 }, 0.2f, -1);
				Firework* p = new Firework(0.3, { 1,0,1,1 }, 0,3,7,12);
				p->setInvMass(1.0f / 2.0f);
				gPG->addModelParticle(p, "MORADO", true);
				p = new Firework(0.4, { 1,1,0,1 }, 0,2,10,14);
				p->setInvMass(1.0f);
				gPG->addModelParticle(p, "AMARILLO", true);
				gPG->addGenerationLoop(1.7f);
				gPG->addForceGenerator(gFG);
				playerParticles->addGenerator(gPG, "LEFT_FIREWORKS");

				gFG = new GravityForceGenerator({ 0,-9.8f,0 });
				gPG = new GaussianParticleGenerator(player->getPosition() - Vector3(-PLAYER_SIZE * 2, -half_player_size, 0), { 0,25,0 }, 0.7f, 1, { 0.1,0.1,0.1 }, { 4,2,4 }, 0.2f, -1);
				p = new Firework(0.5, { 0,0,1,1 }, 0,4,8,10);
				p->setInvMass(1.0f / 2.0f);
				gPG->addModelParticle(p, "AZUL", true);
				p = new Firework(0.3, { 1,1,1,1 }, 0, 3, 7, 12);
				p->setInvMass(1.0f);
				gPG->addModelParticle(p, "BLANCO", true);
				gPG->addGenerationLoop(2.3f);
				gPG->addForceGenerator(gFG);
				playerParticles->addGenerator(gPG, "RIGHT_FIREWORKS");
			}
		}
		else if (state == DEAD) {
			time += t;
			if (time > DEAD_TIME) {
				state = PLAYING;
				delete system;
				delete playerParticles;
				onStart();
			}
		}
	}
}

void GameManager::processInput(unsigned char key) {
	if (key == ' ') {
		if (state == PLAYING) {
			player->tryJump();
		}
		else if (state == WIN) {
			state = PLAYING;
			delete system;
			delete playerParticles;
			onStart();
		}
		else if (state == START) {
			state = PLAYING;
			onStart();
		}
	}
}

void GameManager::jump(float force) {
	JumpForce* jF;
	if (YELLOW_JUMP_FORCE == force) {
		jF = new JumpForce({ 0,force,0 }, 0.1);
	}
	else jF = new JumpForce({ 0,force,0 }, 0.3);
	system->addRegistry(jF, player);
	player->setGrounded(false);
	playerParticles->getParticleGenerator("IZQ_PLAYER")->setActive(false);
	playerParticles->getParticleGenerator("DER_PLAYER")->setActive(false);
}

void GameManager::lastObstacleGenerated() {
	end = true;
}


void GameManager::onGameOver() {
	state = DEAD;
	time = 0;
	player->setLifeTime(0);
	playerParticles->setEmpty();
	GaussianParticleGenerator* gPG = new GaussianParticleGenerator(player->getPosition(), { 0,0,0 }, 3, 5, { 0.1,0.1,0.1 }, { 6,6,6 }, 1, 30);
	playerParticles->addGenerator(gPG, "DEAD");
	Particle* p = new Particle(0.4, { 0,0.4,1,1 }, 0);
	p->setInvMass(1.0f / 5.0f);
	gPG->addModelParticle(p, "AZUL", true);
	p = new Particle(0.6, { 1,0.7,1,1 }, 0);
	p->setInvMass(1.0f);
	gPG->addModelParticle(p, "AZUL/VERDE", true);
	gPG->addGenerationLoop(0.2);
}

void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	if (actor1->getName() == "PLAYER") {
		Player* p = static_cast<Player*>(actor1->userData);
		RigidSolid* rs = static_cast<RigidSolid*>(actor2->userData);
		std::string name = rs->getName();
		float a = p->getPosition().y - PLAYER_SIZE / 2.0f;

		float b = rs->getPosition().y + OBSTACLE_SIZE / 2.0f + COLLISION_MARGIN;
		if (name == "TRIANGULO" || (name == "CUADRADO" && p->getPosition().y - PLAYER_SIZE / 2.0f <= rs->getPosition().y + OBSTACLE_SIZE / 2.0f - COLLISION_MARGIN )) {
			onGameOver();
		}
		else if (name == "CIRCULO" && !player->getYellowTouched()) {
			player->setVelocity({ 0, 0, 0 });
			player->clearForce();
			player->yellowTouched();
			GameManager::jump(YELLOW_JUMP_FORCE);
		}
		else {
			if (p->resetJump() && name == "SUELO") {
				ParticleGenerator* gPG = playerParticles->getParticleGenerator("IZQ_PLAYER");
				gPG->setActive(true);
				gPG->changePosition(player->getPosition() - Vector3(half_player_size, half_player_size, half_player_size));
				gPG = playerParticles->getParticleGenerator("DER_PLAYER");
				gPG->setActive(true);
				gPG->changePosition(player->getPosition() - Vector3(half_player_size, half_player_size, -half_player_size));
			}
		}
	}
	
}
