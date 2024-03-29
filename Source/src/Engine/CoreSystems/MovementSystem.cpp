#include "../../../include/Engine/CoreSystems/MovementSystem.h"

namespace Engine
{
	MovementSystem::MovementSystem()
	{}

	MovementSystem::~MovementSystem()
	{}

    bool MovementSystem::shouldProcessEntity( const Entity& entity )
    {
        return entity.hasComponent( COMPONENT_MOVEMENT_BIT | COMPONENT_TRANSFORM_BIT );
    }

	void MovementSystem::init( EntityManager& entityManager )
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
