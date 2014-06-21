#include "Engine/CoreSystems/MovementSystem.h"

namespace Engine
{
	MovementSystem::MovementSystem( EventManager* evtManager, EntityManager* entManager ) : System( evtManager, entManager, COMPONENT_MOVEMENT_BIT | COMPONENT_TRANSFORM_BIT )
	{}

	MovementSystem::~MovementSystem()
	{}

	void MovementSystem::init()
	{}

	void MovementSystem::preUpdate()
	{}

	void MovementSystem::updateEntities( const std::set< Entity* >& entities )
	{
		for( std::set< Entity* >::const_iterator it = entities.begin(); it != entities.end(); ++it )
		{
			updateEntityPosition( *it );
		}
	}

	void MovementSystem::updateEntityPosition( Entity* entity )
	{
		std::vector< Component* > moveCompList = ( entityManager->getComponentList( entity, COMPONENT_MOVEMENT ) );

		// Shouldn't ever happen...
		if( !moveCompList.size() )
		{
			fprintf( stdout, "MovementSystem: Entity doesn't contain required component MovementComponent. Will be removed next frame?\n" );
			return;
		}

		std::vector< Component* > transCompList = entityManager->getComponentList( entity, COMPONENT_TRANSFORM );

		// Shouldn't ever happen...
		if( !transCompList.size() )
		{
			fprintf( stdout, "MovementSystem: Entity doesn't contain required component TransformComponent. Will be removed next frame?\n" );
			return;
		}

		for( std::vector< Component* >::const_iterator moveIter = moveCompList.begin(); moveIter != moveCompList.end(); ++moveIter )
		{
			for( std::vector< Component* >::const_iterator transIter = transCompList.begin(); transIter != transCompList.end(); ++transIter )
			{
				MovementComponent* moveComp = static_cast< MovementComponent* >( *moveIter );
				TransformComponent* transComp = static_cast< TransformComponent* >( *transIter );

				float velX = moveComp->getVelocityX(), velY = moveComp->getVelocityY(), velZ = moveComp->getVelocityZ();
				float posX = transComp->getPosX(), posY = transComp->getPosY(), posZ = transComp->getPosZ();

				transComp->setPosition( posX + velX * 1/* DELTA_TIME */, posY + velY * 1/* DELTA_TIME */, posZ + velZ * 1 /* DELTA_TIME */ );
			}
		}
	}

	void MovementSystem::postUpdate()
	{}
}
