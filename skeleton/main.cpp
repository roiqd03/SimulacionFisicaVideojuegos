#include <ctype.h>

#include <PxPhysicsAPI.h>
#include <PxRigidDynamic.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particles/Utils/Gun.h"
#include "Particles/Systems/FireworkSystem.h"
#include "Particles/Systems/PruebasSystem.h"
#include "Particles/Systems/SpringsSystem.h"
#include "Particles/Systems/RigidSolidSystem.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Gun* g = nullptr;
Entity* part = nullptr;
ParticleSystem* partSystem = nullptr;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*g = new Gun();
	part = new Particle(10, { 255,0,0,1 });
	part->setVelocity({ 0,10,0 });
	part->setPosition({ 0,0,0});*/
	//part->setAcceleration({ 0,10,0 });
	//part->setDamping(0.99f);
	
	
	//partSystem = new FireworkSystem();
	//partSystem = new PruebasSystem();
	partSystem = new RigidSolidSystem(nullptr, gPhysics, gScene);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	/*g->integrate(t);
	part->integrate(t);*/
	partSystem->integrate(t);
	

	//g->eraseParticles();
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	//delete g;
	//delete part;
	 
	delete partSystem;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'G':
	{
		static_cast<SpringsSystem*>(partSystem)->applyDirectionalForce();
		break;
	}
	case 'Y':
	{
		static_cast<SpringsSystem*>(partSystem)->changeK(1);
		break;
	}
	case 'H':
	{
		static_cast<SpringsSystem*>(partSystem)->changeK(-1);
		break;
	}
	/*case 'G':
	{
		g->shoot(g->PISTOLA);
		break;
	}
	case 'H':
	{
		g->shoot(g->CAÑON);
		break;
	}
	case 'J':
	{
		g->shoot(g->TANQUE);
		break;
	}*/
	case 'U':
		static_cast<PruebasSystem*>(partSystem)->explosion();
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}