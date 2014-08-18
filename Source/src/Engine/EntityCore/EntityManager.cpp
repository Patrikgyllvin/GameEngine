#include "Engine/EntityCore/EntityManager.h"

namespace Engine
{
	EntityManager::EntityManager( EventManager* eManager )
	:
	eventManager( eManager ),
	nextID( 0 ),
	usedIDs(),
	entities()
	{
		components.resize( COMPONENT_LAST );
	}

	EntityManager::~EntityManager()
	{
		for( std::vector< Entity* >::iterator it = entities.begin(); it != entities.end(); ++it )
			destroyEntity( *it );

		entities.clear();

		usedIDs.clear();

		for( unsigned int i = 0; i < COMPONENT_LAST; i++ )
			components[ i ].clear();

		components.clear();
	}

	Entity* EntityManager::genEntity()
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
			entities.resize( id + 1, nullptr );

		Entity* entity = new Entity( id );

		entities[ id ] = entity;

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_CREATED, entity ) );

		return entity;
	}

	void EntityManager::destroyEntity( Entity* entity )
	{
		usedIDs.push_back( entity->getID() );

		destroyAllComponents( entity );

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_DESTROYED, entity ) );

		delete entity;
	}
	
	Component* EntityManager::addComponent( Entity* entity, Component* comp )
	{
		std::vector< Component* >& entList = components[ comp->getType() ];

		if( entity->getID() >= entList.size() )
			entList.resize( entity->getID() + 1 );

		if( entList[ entity->getID() ] != nullptr )
		{
			std::cout << "Component already added!\n";
			return nullptr;
		}

		entList[ entity->getID() ] = comp;

		entity->typeBits |= comp->getTypeBits();

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_ADDED, entity ) );

		return comp;
	}

	void EntityManager::destroyComponent( Entity* entity, ComponentType compType )
	{
		std::vector< Component* >& entList = components[ compType ];

		if( entity->getID() >= entList.size() )
			return;

		Component* entComp = entList[ entity->getID() ];

		if( entComp != nullptr )
		{
			delete entComp;
			entComp = nullptr;
		}

		// No more components of type
		if( entComp == nullptr )
			entity->typeBits &= ( ~compType );

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_DESTROYED, entity ) );
	}

	void EntityManager::destroyAllComponents( Entity* entity )
	{
		for( unsigned int i = 0; i < COMPONENT_LAST; i++ )
		{
			std::vector< Component* >& entList = components[ i ];

			if( entity->getID() >= entList.size() )
				break;

			Component* comp = entList[ entity->getID() ];

			destroyComponent( entity, comp );
		}
	}

	Component* EntityManager::getComponent( Entity* entity, ComponentType compType )
	{
		std::vector< Component* >& entList = components[ compType ];

		// Entity not in list - doesn't contain any components of type compType...
		if( entity->getID() >= entList.size() )
		{
			return nullptr;
		}

		return entList[ entity->getID() ];
	}
}
