#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/EntityCore/EntityManager.h"
#else
#include "EntityManager.h"
#include "Entity.h"
#endif

namespace Engine
{
	EntityManager::EntityManager( EventManager* eManager )
	:
	eventManager( eManager ),
	nextID( 0 ),
	usedIDs(),
	entities()
	{}

	EntityManager::~EntityManager()
	{
		for( std::vector< Entity* >::iterator it = entities.begin(); it != entities.end(); ++it )
			destroyEntity( *it );

		entities.clear();

		usedIDs.clear();
	}

	Entity& EntityManager::genEntity()
	{
		EntityID id;

		if( usedIDs.size() )
		{
			id = usedIDs.back();
			usedIDs.pop_back();
		}
		else
		{
			id = nextID++;
		}
		
		if( id >= entities.size() )
			entities.resize( id + 10, nullptr );
		
		Entity* entity = new Entity( id, *this );

		entities[ id ] = entity;

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_CREATED, entity ) );

		return *entity;
	}

	void EntityManager::destroyEntity( Entity* entity )
	{
		usedIDs.push_back( entity->getID() );

		entity->destroyAllComponents();
		
		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_DESTROYED, entity ) );

		delete entity;
	}
}
