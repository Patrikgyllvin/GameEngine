#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "Engine/CoreSystems/MovementSystem.h"
#else
#include "MovementSystem.h"
#endif

namespace Engine
{
	/*MovementSystem::MovementSystem( EventManager* evtManager, EntityManager* entManager ) : System( evtManager, entManager, COMPONENT_MOVEMENT_BIT | COMPONENT_TRANSFORM_BIT )
	{}*/

	MovementSystem::~MovementSystem()
	{}

	void MovementSystem::init()
	{}
/*
	void MovementSystem::preUpdate()
	{}
*//*
	void MovementSystem::updateEntities( const std::set< Entity* >& entities )
	{
		for( std::set< Entity* >::const_iterator it = entities.begin(); it != entities.end(); ++it )
		{
			updateEntityPosition( *it );
		}
	}
*//*
	void MovementSystem::updateEntityPosition( Entity* entity )
	{
		MovementComponent* moveComp = static_cast< MovementComponent* >( entityManager->getComponent( entity, COMPONENT_MOVEMENT ) );

		TransformComponent* transComp = static_cast< TransformComponent* >( entityManager->getComponent( entity, COMPONENT_TRANSFORM ) );

		float velX = moveComp->getVelocityX(), velY = moveComp->getVelocityY(), velZ = moveComp->getVelocityZ();
		float posX = transComp->getPosX(), posY = transComp->getPosY(), posZ = transComp->getPosZ();

		transComp->setPosition( posX + velX * 1/* DELTA_TIME *//*, posY + velY * 1*//* DELTA_TIME *//*, posZ + velZ * 1 *//* DELTA_TIME */ /*);*/
	//}
}