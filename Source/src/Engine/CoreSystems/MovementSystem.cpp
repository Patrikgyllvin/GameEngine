#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/CoreSystems/MovementSystem.h"
#else
#include "MovementSystem.h"
#endif

namespace Engine
{
	MovementSystem::MovementSystem()
	{}

	MovementSystem::~MovementSystem()
	{}

	void MovementSystem::init()
	{}
	
	void MovementSystem::preProcess()
	{}

	void MovementSystem::processEntity( Entity& entity )
	{
		// Entity can only have one transform, move component.
		MovementComponent* moveComp = static_cast< MovementComponent* >( entity.getComponents( COMPONENT_MOVEMENT )[ 0 ] );
		TransformComponent* transComp = static_cast< TransformComponent* >( entity.getComponents( COMPONENT_TRANSFORM )[ 0 ] );

		float velX = moveComp->getVelocityX(), velY = moveComp->getVelocityY(), velZ = moveComp->getVelocityZ();
		float posX = transComp->getPosX(), posY = transComp->getPosY(), posZ = transComp->getPosZ();

		// TODO: Deltatime, fixed timestep.
		transComp->setPosition(posX + velX * 1/* DELTA_TIME */, posY + velY * 1 /* DELTA_TIME */, posZ + velZ * 1 /* DELTA_TIME */);
	}

	void MovementSystem::postProcess()
	{}
}